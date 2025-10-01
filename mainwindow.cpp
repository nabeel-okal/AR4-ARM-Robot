#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPortInfo>
#include <QMetaObject>
#include <QDebug>

#include "objectdetectiontab.h"
#include "calibrationtab.h"
#include "robotcontrol.h"
#include "settings.h"
#include "cameraworker.h"
#include "robotcontrollerworker.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createTabs();
    setupRobotWorker();
    connectSignals();

    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    stopCamera();       // ensures thread is stopped safely

    // Stop robot thread safely (worker will be deleted via deleteLater)
    if (m_robot) {
        m_robotThread.quit();
        m_robotThread.wait(200);
        m_robot = nullptr;
    }

    delete ui;
}

// -----------------------------------------------------------------------------
// Organization helpers: create UI tabs & workers
// -----------------------------------------------------------------------------

void MainWindow::createTabs()
{
    // Create tabs (pass 'this' as MainWindow* where needed)
    obDetTab      = new ObjectDetectionTab(this, this);
    calTab        = new CalibrationTab(this);
    robotControl  = new RobotControl(this);
    settings      = new Settings(this);

    // Create robot worker instance (moved to thread in setupRobotWorker)
    m_robot = new RobotControllerWorker();

    // Add tabs to UI
    ui->tabWidget->addTab(obDetTab,      tr("Object Detection"));
    ui->tabWidget->addTab(calTab,        tr("Calibration"));
    ui->tabWidget->addTab(robotControl,  tr("Robot Control"));
    ui->tabWidget->addTab(settings,      tr("Settings"));
}

void MainWindow::setupRobotWorker()
{
    // Move robot worker to its own thread
    m_robot->moveToThread(&m_robotThread);

    // Delete worker when thread finishes
    connect(&m_robotThread, &QThread::finished, m_robot, &QObject::deleteLater);

    // Start the thread (you'll invoke worker slots via Qt::QueuedConnection)
    m_robotThread.start();
}

// -----------------------------------------------------------------------------
// All signal/slot wiring in one place (safer, easier to maintain)
// -----------------------------------------------------------------------------

void MainWindow::connectSignals()
{
    // -------------------------
    // RobotControl -> MainWindow (UI logs and commands)
    // -------------------------
    connect(robotControl, &RobotControl::driveRequested, this,
            [this](RobotControl::Direction dir, int speed) {
                const QString d = (dir==RobotControl::Forward ? "FWD" :
                                       dir==RobotControl::Backward ? "BWD" :
                                       dir==RobotControl::Right ? "RIGHT" : "LEFT");
                if (auto log = robotControl->getTextRobotLog())
                    obDetTab->getDetLogTextEdit()->append(QString("[CMD] Drive %1 @ %2%").arg(d).arg(speed));
            });

    connect(robotControl, &RobotControl::stopRequested, this, [this](){
        if (auto log = robotControl->getTextRobotLog()) log->append("[CMD] Stop");
        QMetaObject::invokeMethod(m_robot, "stop", Qt::QueuedConnection);
    });

    connect(robotControl, &RobotControl::speedChanged, this, [this](int sp){
        if (auto log = robotControl->getTextRobotLog())
            log->append(QString("[CMD] Speed -> %1%").arg(sp));
        QMetaObject::invokeMethod(m_robot, "setSpeedPercent", Qt::QueuedConnection, Q_ARG(int, sp));
    });

    connect(robotControl, &RobotControl::motorsEnabledChanged, this, [this](bool on){
        if (auto log = robotControl->getTextRobotLog())
            log->append(QString("[CMD] Motors %1").arg(on ? "Enable" : "Disable"));
        QMetaObject::invokeMethod(m_robot, "enableMotors", Qt::QueuedConnection, Q_ARG(bool, on));
    });

    connect(robotControl, &RobotControl::modeChanged, this, [this](RobotControl::Mode m){
        if (auto log = robotControl->getTextRobotLog())
            log->append(QString("[CMD] Mode -> %1").arg(m==RobotControl::Joint ? "Joint" : "Planar"));
    });

    // Drive requested -> forward to worker
    connect(robotControl, &RobotControl::driveRequested, this,
            [this](RobotControl::Direction dir, int /*speedPercent*/){
                const bool jointMode = (robotControl->mode() == RobotControl::Joint);

                if (jointMode) {
                    const int joint = robotControl->selectedJoint(); // 1..6
                    double v = 10.0; // deg/s nominal
                    if (dir == RobotControl::Backward) v = -v;

                    if (dir == RobotControl::Left || dir == RobotControl::Right) {
                        // Use base joint (J1) for left/right
                        const int j = 1;
                        const double vbase = (dir == RobotControl::Right) ? +v : -v;
                        QMetaObject::invokeMethod(m_robot, "jogJoint", Qt::QueuedConnection,
                                                  Q_ARG(int, j), Q_ARG(double, vbase));
                        return;
                    }
                    QMetaObject::invokeMethod(m_robot, "jogJoint", Qt::QueuedConnection,
                                              Q_ARG(int, joint), Q_ARG(double, v));
                } else {
                    // Planar XYZ mode
                    char axis = robotControl->selectedAxis(); // 'X','Y','Z'
                    double v  = 50.0; // mm/s nominal
                    if (axis == 'Z') {
                        v = (dir == RobotControl::Forward ? +v : (dir == RobotControl::Backward ? -v : 0));
                    } // X/Y sign handled in worker via velocity or your own mapping
                    QMetaObject::invokeMethod(m_robot, "jogPlanar", Qt::QueuedConnection,
                                              Q_ARG(char, axis), Q_ARG(double, v));
                }
            });

    // -------------------------
    // Robot worker -> RobotControl (logs & connection state)
    // -------------------------
    connect(m_robot, &RobotControllerWorker::info, this, [this](const QString& s){
        if (auto log = robotControl->getTextRobotLog()) log->append("[INFO] " + s);
    });
    connect(m_robot, &RobotControllerWorker::error, this, [this](const QString& s){
        if (auto log = robotControl->getTextRobotLog()) log->append("[ERR] " + s);
    });
    connect(m_robot, &RobotControllerWorker::rxLine, this, [this](const QString& s){
        if (auto log = robotControl->getTextRobotLog()) log->append("[RX] " + s);
    });
    connect(m_robot, &RobotControllerWorker::connectedChanged, this, [this](bool ok){
        robotControl->setConnected(ok);
    });

    // -------------------------
    // Settings <-> Worker wiring
    // -------------------------
    connect(settings, &Settings::requestConnectSerial, m_robot, &RobotControllerWorker::connectTo, Qt::QueuedConnection);
    connect(settings, &Settings::requestDisconnect,    m_robot, &RobotControllerWorker::disconnectFrom, Qt::QueuedConnection);
    connect(settings, &Settings::requestPing,          m_robot, &RobotControllerWorker::ping, Qt::QueuedConnection);

    connect(m_robot, &RobotControllerWorker::connectedChanged,
            settings, &Settings::onRobotConnectedChanged, Qt::QueuedConnection);

    // Settings status message -> main window label (simple green/red)
    connect(settings, &Settings::robotStatusMessage, this, [this](const QString msg){
        ui->robotStatusLabel->setText(msg);
        ui->robotStatusLabel->setStyleSheet(msg == "ON" ? "background-color: green;"
                                                        : "background-color: red;");
    });

    // -------------------------
    // Initial population of serial ports in RobotControl (if it has comboPort)
    // -------------------------
    // populateSerialPorts();
}

// -----------------------------------------------------------------------------
// Camera control: start/stop / wiring to CameraWorker
// -----------------------------------------------------------------------------

void MainWindow::startCamera()
{
    if (m_cameraRunning) return;

    // Camera params derived from Settings tab (with fallbacks)
    const int camIndex = (settings && settings->getCamIndexSpinBox())
                             ? settings->getCamIndexSpinBox()->value()
                             : 0;

    int w = 640, h = 480;
    if (settings && settings->getResComboBox()) {
        const QString res = settings->getResComboBox()->currentText(); // e.g. "1280x720"
        const auto parts = res.split('x');
        w = parts.value(0).toInt();
        h = parts.value(1).toInt();
    }

    // Create camera worker and move to its thread
    m_camWorker = new CameraWorker(camIndex, w, h);
    m_camWorker->moveToThread(&m_camThread);

    // Calibration sliders -> camera worker (live tuning)
    connect(calTab, &CalibrationTab::exposureNormChanged,   m_camWorker, &CameraWorker::setExposureNorm);
    connect(calTab, &CalibrationTab::brightnessNormChanged, m_camWorker, &CameraWorker::setBrightnessNorm);
    connect(calTab, &CalibrationTab::contrastNormChanged,   m_camWorker, &CameraWorker::setContrastNorm);

    // Cleanup on thread finish
    connect(&m_camThread, &QThread::finished, m_camWorker, &QObject::deleteLater);

    // Frame -> ObjectDetectionTab preview label
    connect(m_camWorker, &CameraWorker::frameReady,
            obDetTab,     &ObjectDetectionTab::onFrameReady,
            Qt::QueuedConnection);

    // Errors -> ObjectDetectionTab log
    connect(m_camWorker, &CameraWorker::error, this, [this](const QString& msg){
        if (obDetTab && obDetTab->getDetLogTextEdit())
            obDetTab->getDetLogTextEdit()->appendPlainText("[Camera] " + msg);
    });

    // Start the worker when the thread starts
    connect(&m_camThread, &QThread::started, m_camWorker, &CameraWorker::start);

    // Go!
    m_camThread.start();
    m_cameraRunning = true;

    if (obDetTab && obDetTab->getDetLogTextEdit())
        obDetTab->getDetLogTextEdit()->appendPlainText("[Camera] Started.");
    setupCameraStatus(true);
}

void MainWindow::stopCamera()
{
    if (!m_cameraRunning) return;

    if (m_camWorker) m_camWorker->stop();
    m_camThread.quit();
    m_camThread.wait();

    m_cameraRunning = false;
    m_camWorker = nullptr;

    // Clear preview (optional)
    if (obDetTab && obDetTab->getDetectionPreviewLabel()) {
        QPixmap blank(obDetTab->getDetectionPreviewLabel()->size());
        blank.fill(Qt::black);
        obDetTab->getDetectionPreviewLabel()->setPixmap(blank);
    }

    if (obDetTab && obDetTab->getDetLogTextEdit())
        obDetTab->getDetLogTextEdit()->appendPlainText("[Camera] Stopped.");
    setupCameraStatus(false);
}

// -----------------------------------------------------------------------------
// Misc helpers
// -----------------------------------------------------------------------------

// void MainWindow::populateSerialPorts()
// {
//     auto portBox = robotControl->findChild<QComboBox*>("comboPort");
//     if (!portBox) return;
//     portBox->clear();
//     for (const QSerialPortInfo& info : QSerialPortInfo::availablePorts()) {
//         portBox->addItem(info.systemLocation()); // e.g., /dev/ttyUSB0
//     }
// }

void MainWindow::updateDetectionFrame()
{
    // Legacy helper (kept): render a blank canvas
    if (!obDetTab || !obDetTab->getDetectionPreviewLabel()) return;

    const QSize canvasSize =
        obDetTab->getDetectionPreviewLabel()->size().boundedTo(QSize(1280, 720));
    if (canvasSize.isEmpty()) return;

    QPixmap canvas(canvasSize);
    canvas.fill(Qt::black);
    obDetTab->getDetectionPreviewLabel()->setPixmap(canvas);
}

void MainWindow::setupCameraStatus(bool connected)
{
    ui->cameraStatusLabel->setStyleSheet(
        connected
            ? "background-color: green; border-radius: 10px;"
            : "background-color: red; border-radius: 10px;");
}

void MainWindow::populateSerialPorts()
{
    // Prefer: robotControl->getPortCombo()
    auto portBox = robotControl->findChild<QComboBox*>("comboPort");
    if (!portBox) {
        qDebug() << "RobotControl UI has no 'comboPort'; skipping populateSerialPorts().";
        return;
    }
    portBox->clear();
    for (const QSerialPortInfo& info : QSerialPortInfo::availablePorts()) {
        portBox->addItem(info.systemLocation()); // e.g., /dev/ttyUSB0
    }
}

// -----------------------------------------------------------------------------
// Public getters (used by tabs)
// -----------------------------------------------------------------------------

QLabel *MainWindow::getCameraStatusLabel() const { return ui->cameraStatusLabel; }
CameraWorker *MainWindow::getCameraWorker() const { return m_camWorker; }
