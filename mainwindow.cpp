#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPortInfo>

#include "objectdetectiontab.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Add Tabs (your separate classes for each tab)
    obDetTab = new ObjectDetectionTab(this, this);
    calTab = new CalibrationTab(this);
    robotControl = new RobotControl(this);
    settings = new Settings(this);
    m_robot = new RobotControllerWorker();

    ui->tabWidget->addTab(obDetTab, "Object Detection");
    ui->tabWidget->addTab(calTab, "Calibration");
    ui->tabWidget->addTab(robotControl, "Robot Control");
    ui->tabWidget->addTab(settings, "Settings");

    init();
}

MainWindow::~MainWindow()
{
    stopCamera();       // ensures thread is stopped safely
    delete ui;
}

void MainWindow::init()
{
    // Default to first tab
    ui->tabWidget->setCurrentIndex(0);

    // --- Object Detection tab setup ---
    obDetTab->getDetectionPreviewLabel()->setScaledContents(true);
    obDetTab->getDetectionPreviewLabel()->setAlignment(Qt::AlignCenter);

    // Wire Start/Stop → camera on/off
    connect(obDetTab->getStartDetBtn(), &QPushButton::clicked,
            this, &MainWindow::startCamera);
    connect(obDetTab->getStopDetBtn(),  &QPushButton::clicked,
            this, &MainWindow::stopCamera);

    // Signal connections from RobotControl Tab

    connect(robotControl, &RobotControl::driveRequested, this,
            [this](RobotControl::Direction dir, int speed){
        // TODO: replace with AR4 SDK calls (cartesian/joint jog)
        QString d = (dir==RobotControl::Forward ? "FWD" :
                         dir==RobotControl::Backward ? "BWD" :
                         dir==RobotControl::Right ? "RIGHT" : "LEFT");
        if (auto log = robotControl->getTextRobotLog())
            log->append(QString("[CMD] Drive %1 @ %2%").arg(d).arg(speed));
    });

    connect(robotControl, &RobotControl::stopRequested, this,
            [this](){
                // TODO: AR4: stop motion / override velocity to 0
                if (auto log = robotControl->getTextRobotLog())
                    log->append("[CMD] Stop");
    });

    connect(robotControl, &RobotControl::speedChanged, this,
            [this](int sp){
                // TODO: AR4: set global speed scale / jog speed
                if (auto log = robotControl->getTextRobotLog())
                    log->append(QString("[CMD] Speed -> %1%").arg(sp));
    });

    // Connect motorEnabled & mode buttons
    connect(robotControl, &RobotControl::motorsEnabledChanged, this, [this](bool on){
        if (auto log = robotControl->getTextRobotLog())
            log->append(QString("[CMD] Motors %1").arg(on ? "Enable" : "Disable"));
        // TODO: send enable/disable command to AR4 here
    });

    connect(robotControl, &RobotControl::modeChanged, this, [this](RobotControl::Mode m){
        if (auto log = robotControl->getTextRobotLog())
            log->append(QString("[CMD] Mode -> %1").arg(m==RobotControl::Joint ? "Joint" : "Planar"));
    });

    // RobotControllerClass connections
    m_robot->moveToThread(&m_robotThread);

    connect(&m_robotThread, &QThread::finished, m_robot, &QObject::deleteLater);
    m_robotThread.start();

    // logs from worker -> RobotControl log box
    connect(m_robot, &RobotControllerWorker::info, this, [this](const QString& s){
        if (auto log = robotControl->getTextRobotLog()) log->append("[INFO] " + s);
    });
    connect(m_robot, &RobotControllerWorker::error, this, [this](const QString& s){
        if (auto log = robotControl->getTextRobotLog()) log->append("[ERR] " + s);
    });
    connect(m_robot, &RobotControllerWorker::rxLine, this, [this](const QString& s){
        if (auto log = robotControl->getTextRobotLog()) log->append("[RX] " + s);
    });

    // track connection state → enable/disable controls
    connect(m_robot, &RobotControllerWorker::connectedChanged, this, [this](bool ok){
        robotControl->setConnected(ok);
    });

    // Fill serial port list and wire Connect button
    populateSerialPorts();
    connect(robotControl->findChild<QPushButton*>("btnConnect"), &QPushButton::clicked,
            this, [this](){
                auto portBox = robotControl->findChild<QComboBox*>("comboPort");
                auto btn = robotControl->findChild<QPushButton*>("btnConnect");
                if (!portBox || !btn) return;
                if (btn->text() == "Connect") {
                    const QString port = portBox->currentText();
                    // call into worker thread
                    QMetaObject::invokeMethod(m_robot, "connectTo",
                                              Qt::QueuedConnection,
                                              Q_ARG(QString, port),
                                              Q_ARG(int, 115200));
                    btn->setText("Disconnect");
                } else {
                    QMetaObject::invokeMethod(m_robot, "disconnectFrom", Qt::QueuedConnection);
                    btn->setText("Connect");
                }
    });

    // Speed scale: your UI emits 0..100; worker applies final scaling again.
    // We just forward the percent:
    connect(robotControl, &RobotControl::speedChanged, this, [this](int sp){
        QMetaObject::invokeMethod(m_robot, "setSpeedPercent", Qt::QueuedConnection, Q_ARG(int, sp));
    });

    // Deadman toggle:
    connect(robotControl, &RobotControl::motorsEnabledChanged, this, [this](bool on){
        QMetaObject::invokeMethod(m_robot, "enableMotors", Qt::QueuedConnection, Q_ARG(bool, on));
    });

    // STOP (button/keys/releases):
    connect(robotControl, &RobotControl::stopRequested, this, [this](){
        QMetaObject::invokeMethod(m_robot, "stop", Qt::QueuedConnection);
    });

    // DRIVE (button/keys pressed):
    connect(robotControl, &RobotControl::driveRequested, this,
            [this](RobotControl::Direction dir, int /*speedPercent*/){

                // Decide velocity sign and target (joint/axis) from current mode
                const bool jointMode = (robotControl->mode() == RobotControl::Joint);

                if (jointMode) {
                    const int joint = robotControl->selectedJoint(); // 1..6
                    // simple mapping: Forward = +, Backward = -, Left/Right rotate base (J1)
                    double v = 10.0; // deg/s nominal; tweak as you like
                    if (dir == RobotControl::Backward) v = -v;
                    if (dir == RobotControl::Left || dir == RobotControl::Right) {
                        // If user pressed left/right, override to base joint (J1)
                        // Left = - , Right = +
                        int j = 1;
                        double vbase = (dir == RobotControl::Right) ? +v : -v;
                        QMetaObject::invokeMethod(m_robot, "jogJoint", Qt::QueuedConnection,
                                                  Q_ARG(int, j), Q_ARG(double, vbase));
                        return;
                    }
                    QMetaObject::invokeMethod(m_robot, "jogJoint", Qt::QueuedConnection,
                                              Q_ARG(int, joint), Q_ARG(double, v));
                } else {
                    // Planar XYZ: map Forward/Backward to +Y/-Y, Left/Right to -X/+X
                    char axis = 'Y';
                    double v = 50.0; // mm/s nominal
                    switch (dir) {
                    case RobotControl::Forward:  axis = 'Y'; v = +v; break;
                    case RobotControl::Backward: axis = 'Y'; v = -v; break;
                    case RobotControl::Left:     axis = 'X'; v = -v; break;
                    case RobotControl::Right:    axis = 'X'; v = +v; break;
                    }
                    // If user picked a specific axis in UI, use that instead:
                    axis = robotControl->selectedAxis();
                    // Flip sign based on direction if axis == X or Y; for Z, map Forward/Backward to +Z/-Z
                    if (axis == 'Z') v = (dir == RobotControl::Forward ? +v : (dir == RobotControl::Backward ? -v : 0));
                    else {
                        // already set above for X/Y
                    }
                    QMetaObject::invokeMethod(m_robot, "jogPlanar", Qt::QueuedConnection,
                                              Q_ARG(char, axis), Q_ARG(double, v));
                }
            });
}

void MainWindow::setCameraStatus(bool connected)
{
    if (connected) {
        ui->cameraStatusLabel->setStyleSheet("background-color: green; border-radius: 10px;");
    } else {
        ui->cameraStatusLabel->setStyleSheet("background-color: red; border-radius: 10px;");
    }
}

void MainWindow::setRobotStatus(bool connected)
{
    if (connected) {
        ui->robotStatusLabel->setStyleSheet("background-color: green; border-radius: 10px;");
    } else {
        ui->robotStatusLabel->setStyleSheet("background-color: red; border-radius: 10px;");
    }
}

void MainWindow::startCamera()
{
    if (m_cameraRunning) return;

    // Camera params from Settings tab (fallbacks if not present)
    const int camIndex = settings && settings->getCamIndexSpinBox()
                             ? settings->getCamIndexSpinBox()->value()
                             : 0;

    int w = 640, h = 480;
    if (settings && settings->getResComboBox()) {
        const QString res = settings->getResComboBox()->currentText(); // e.g. "1280x720"
        const auto parts = res.split('x');
        w = parts.value(0).toInt();
        h = parts.value(1).toInt();
    }

    // Create worker and move to thread
    m_camWorker = new CameraWorker(camIndex, w, h);
    m_camWorker->moveToThread(&m_camThread);

    // ... after cam worker is created and moved to m_camThread
    connect(calTab, &CalibrationTab::exposureNormChanged,  m_camWorker, &CameraWorker::setExposureNorm);
    connect(calTab, &CalibrationTab::brightnessNormChanged, m_camWorker, &CameraWorker::setBrightnessNorm);
    connect(calTab, &CalibrationTab::contrastNormChanged,   m_camWorker, &CameraWorker::setContrastNorm);

    // Lifetime
    connect(&m_camThread, &QThread::finished, m_camWorker, &QObject::deleteLater);

    // Frame → preview label (GUI thread)
    connect(m_camWorker, &CameraWorker::frameReady, this, [this](const QImage& img){
        if (!img.isNull())
            obDetTab->getDetectionPreviewLabel()->setPixmap(QPixmap::fromImage(img));
    });

    // Errors → log
    connect(m_camWorker, &CameraWorker::error, this, [this](const QString& msg){
        obDetTab->getDetLogTextEdit()->appendPlainText("[Camera] " + msg);
    });

    // Thread start → worker start
    connect(&m_camThread, &QThread::started, m_camWorker, &CameraWorker::start);

    // Go!
    m_camThread.start();
    m_cameraRunning = true;

    // (Optional) UI feedback
    obDetTab->getDetLogTextEdit()->appendPlainText("[Camera] Started.");
    setCameraStatus(true);
}

void MainWindow::stopCamera()
{
    if (!m_cameraRunning) return;

    // Ask worker to stop, then stop the thread
    if (m_camWorker) m_camWorker->stop();
    m_camThread.quit();
    m_camThread.wait();

    m_cameraRunning = false;
    m_camWorker = nullptr;

    // Clear preview (optional)
    QPixmap blank(obDetTab->getDetectionPreviewLabel()->size());
    blank.fill(Qt::black);
    obDetTab->getDetectionPreviewLabel()->setPixmap(blank);

    obDetTab->getDetLogTextEdit()->appendPlainText("[Camera] Stopped.");
    setCameraStatus(false);
}

void MainWindow::populateSerialPorts()
{
    auto portBox = robotControl->findChild<QComboBox*>("comboPort");
    if (!portBox) return;
    portBox->clear();
    for (const QSerialPortInfo& info : QSerialPortInfo::availablePorts()) {
        portBox->addItem(info.systemLocation()); // e.g., /dev/ttyUSB0
    }
}

void MainWindow::updateDetectionFrame()
{
    // Create a blank canvas for testing layout until real camera is wired
    const QSize canvasSize = obDetTab->getDetectionPreviewLabel()->size().boundedTo(QSize(1280, 720));
    if (canvasSize.isEmpty()) return;

    QPixmap canvas(canvasSize);
    canvas.fill(Qt::black);

    obDetTab->getDetectionPreviewLabel()->setPixmap(canvas);
}

QLabel *MainWindow::getCameraStatusLabel() const { return ui->cameraStatusLabel; }
