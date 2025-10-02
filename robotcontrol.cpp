#include "robotcontrol.h"
#include "ui_robotcontrol.h"

#include <QTextEdit>
#include <QSlider>
#include <QLabel>
#include <QKeyEvent>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QDateTime>
#include <QFocusEvent>

RobotControl::RobotControl(QWidget *parent)
    : QWidget(parent), ui(new Ui::RobotControl)
{
    ui->setupUi(this);

    // Speed slider (0..100)
    ui->speedSlider->setRange(0,100);
    ui->speedSlider->setValue(m_speed);
    if (ui->speedValueLabel) ui->speedValueLabel->setText(QString::number(m_speed) + "%");

    // Avoid button auto-repeat; we handle press/release explicitly
    if (ui->forwardBtn)  ui->forwardBtn->setAutoRepeat(false);
    if (ui->backwardBtn) ui->backwardBtn->setAutoRepeat(false);
    if (ui->rightBtn)    ui->rightBtn->setAutoRepeat(false);
    if (ui->leftBtn)     ui->leftBtn->setAutoRepeat(false);

    // Keyboard focus so we can receive key events
    setFocusPolicy(Qt::StrongFocus);

    // Reasonable defaults
    if (ui->rbModeJoint)   ui->rbModeJoint->setChecked(true);
    if (ui->rbModePlanar)  ui->rbModePlanar->setChecked(false);
    if (ui->chEnableMotors) ui->chEnableMotors->setChecked(false);

    populateCombosOnce();

    // Initially disabled (until MainWindow sets connection)
    setConnected(false);

    log("Robot Control ready. Connect to robot to enable motion.");
}

RobotControl::~RobotControl()
{
    delete ui;
}

QTextEdit *RobotControl::getTextRobotLog() const
{
    return ui->textRobotLog;
}

void RobotControl::setConnected(bool ok)
{
    // If we're losing connection, ensure we stop
    if (m_connected && !ok) {
        ensureStopped("connection lost");
    }

    m_connected = ok;
    setDriveControlsEnabled(ok);

    // Motors checkbox always enabled (allows staging before connect)
    if (ui->chEnableMotors) ui->chEnableMotors->setEnabled(true);

    log(QString("%1 Connection: %2").arg(ts()).arg(ok ? "Connected" : "Disconnected"));
}

bool RobotControl::motorsEnabled() const
{
    return (ui->chEnableMotors && ui->chEnableMotors->isChecked());
}

int RobotControl::speedPercent() const
{
    return (ui->speedSlider ? ui->speedSlider->value() : m_speed);
}

int RobotControl::selectedJoint() const
{
    // 1..6
    return (ui->comboJoint ? ui->comboJoint->currentIndex() + 1 : 1);
}

char RobotControl::selectedAxis() const
{
    if(!ui->comboAxis)  return 'X';
    const auto t = ui->comboAxis->currentText().toUpper();
    return t.contains('Z') ? 'Z' : (t.contains('Y') ? 'Y' : 'X');
}

RobotControl::Mode RobotControl::mode() const
{
    return (ui->rbModePlanar && ui->rbModePlanar->isChecked() ? Planar : Joint);
}

// ---------------- Button handlers (press/hold jog) ----------------

void RobotControl::on_forwardBtn_pressed()  { requestDrive(Forward);  log(ts() + " Drive: FORWARD"); }
void RobotControl::on_forwardBtn_released() { ensureStopped("forward release"); }

void RobotControl::on_backwardBtn_pressed()  { requestDrive(Backward); log(ts() + " Drive: BACKWARD"); }
void RobotControl::on_backwardBtn_released() { ensureStopped("backward release"); }

void RobotControl::on_rightBtn_pressed()  { requestDrive(Right);  log(ts() + " Drive: RIGHT"); }
void RobotControl::on_rightBtn_released() { ensureStopped("right release"); }

void RobotControl::on_leftBtn_pressed()  { requestDrive(Left);  log(ts() + " Drive: LEFT"); }
void RobotControl::on_leftBtn_released() { ensureStopped("left release"); }

void RobotControl::on_stopBtn_clicked()
{
    ensureStopped("STOP button");
}

// ---------------- Speed ----------------

void RobotControl::on_speedSlider_valueChanged(int value)
{
    if(value < 0)   value = 0;
    if(value > 100) value = 100;

    m_speed = value;
    if (ui->speedValueLabel) ui->speedValueLabel->setText(QString::number(m_speed) + "%");
    emit speedChanged(m_speed);
    log(QString("%1 Speed -> %2%").arg(ts()).arg(m_speed));
}

// ---------------- Modes / Motors ----------------

void RobotControl::on_chEnableMotors_toggled(bool checked)
{
    emit motorsEnabledChanged(checked);
    log(QString("%1 Motors %2").arg(ts()).arg(checked ? "ENABLED" : "DISABLED"));
}

void RobotControl::on_rbModeJoint_toggled(bool checked)
{
    if(!checked) return;
    emit modeChanged(Joint);
    // switch visibility (no .ui change)
    if(ui->comboJoint) ui->comboJoint->setVisible(true);
    if(ui->comboAxis)  ui->comboAxis->setVisible(false);

    ensureStopped("mode -> Joint"); // safety
    log(ts() + " Mode: Joint");
}

void RobotControl::on_rbModePlanar_toggled(bool checked)
{
    if (!checked) return;
    emit modeChanged(Planar);
    if(ui->comboJoint) ui->comboJoint->setVisible(false);
    if(ui->comboAxis)  ui->comboAxis->setVisible(true);

    ensureStopped("mode -> Planar"); // safety
    log(ts() + " Mode: Planar");
}

// ---------------- Keyboard driving ----------------

void RobotControl::keyPressEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat()) { e->ignore(); return; } // ignore repeats
    m_heldKeys.insert(e->key());

    switch (e->key()) {
    case Qt::Key_W:
    case Qt::Key_Up:    requestDrive(Forward);  log(ts() + " Key: FORWARD");  break;
    case Qt::Key_S:
    case Qt::Key_Down:  requestDrive(Backward); log(ts() + " Key: BACKWARD"); break;
    case Qt::Key_A:
    case Qt::Key_Left:  requestDrive(Left);     log(ts() + " Key: LEFT");     break;
    case Qt::Key_D:
    case Qt::Key_Right: requestDrive(Right);    log(ts() + " Key: RIGHT");    break;
    default: QWidget::keyPressEvent(e); return;
    }
    e->accept();
}

void RobotControl::keyReleaseEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat()) { e->ignore(); return; }
    if (!m_heldKeys.contains(e->key())) { QWidget::keyReleaseEvent(e); return; }
    m_heldKeys.remove(e->key());

    // Stop only when the released key is one of our drive keys
    switch (e->key()) {
    case Qt::Key_W: case Qt::Key_Up:
    case Qt::Key_S: case Qt::Key_Down:
    case Qt::Key_A: case Qt::Key_Left:
    case Qt::Key_D: case Qt::Key_Right:
        ensureStopped("key release");
        e->accept();
        return;
    default:
        QWidget::keyReleaseEvent(e);
        return;
    }
}

void RobotControl::focusOutEvent(QFocusEvent *e)
{
    // Safety: if window/tab loses focus while jogging, stop the robot.
    ensureStopped("focus lost");
    QWidget::focusOutEvent(e);
}

// ---------------- Internals ----------------

void RobotControl::log(const QString &s)
{
    if (ui->textRobotLog)
        ui->textRobotLog->append(s);
}

QString RobotControl::ts() const
{
    return QDateTime::currentDateTime().toString("[hh:mm:ss]");
}

bool RobotControl::canDrive(bool logReason) const
{
    if (!m_connected) {
        if (logReason) const_cast<RobotControl*>(this)->log(ts() + " [Guard] Not connected.");
        return false;
    }
    if (!motorsEnabled()) {
        if (logReason) const_cast<RobotControl*>(this)->log(ts() + " [Guard] Motors disabled.");
        return false;
    }
    return true;
}

void RobotControl::requestDrive(Direction d)
{
    if (!canDrive(true)) return;
    emit driveRequested(d, speedPercent());
}

void RobotControl::ensureStopped(const QString& why)
{
    static bool stopping = false; // avoid duplicate stop spam in tight sequences
    if (stopping) return;
    stopping = true;
    emit stopRequested();
    if (!why.isEmpty()) log(ts() + " Stop (" + why + ")");
    stopping = false;
}

void RobotControl::setDriveControlsEnabled(bool on)
{
    const QList<QWidget*> controls = {
        ui->forwardBtn, ui->backwardBtn, ui->rightBtn, ui->leftBtn, ui->stopBtn,
        ui->speedSlider, ui->rbModeJoint, ui->rbModePlanar, ui->comboJoint, ui->comboAxis
    };
    for (QWidget* w : controls) if (w) w->setEnabled(on);
}

void RobotControl::populateCombosOnce()
{
    // Fill comboJoint (1..6) if empty
    if (ui->comboJoint && ui->comboJoint->count() == 0) {
        for (int j = 1; j <= 6; ++j)
            ui->comboJoint->addItem(QString("J%1").arg(j));
        ui->comboJoint->setCurrentIndex(0);
    }
    // Fill comboAxis (X/Y/Z) if empty
    if (ui->comboAxis && ui->comboAxis->count() == 0) {
        ui->comboAxis->addItems({"X", "Y", "Z"});
        ui->comboAxis->setCurrentIndex(0);
    }
    // Start with Joint mode visuals
    if (ui->comboJoint) ui->comboJoint->setVisible(true);
    if (ui->comboAxis)  ui->comboAxis->setVisible(false);
}
