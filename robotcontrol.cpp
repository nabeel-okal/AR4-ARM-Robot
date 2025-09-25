#include "robotcontrol.h"
#include "ui_robotcontrol.h"

#include <QTextEdit>
#include <QSlider>
#include <QLabel>
#include <QKeyEvent>

RobotControl::RobotControl(QWidget *parent)
    : QWidget(parent), ui(new Ui::RobotControl)
{
    ui->setupUi(this);

    // Speed slider setup (0..100)
    ui->speedSlider->setRange(0,100);
    ui->speedSlider->setValue(m_speed);
    ui->speedValueLabel->setText(QString::number(m_speed) + "%");

    // (Optional) avoid button auto-repeat; we handle press/release explicitly
    ui->forwardBtn->setAutoRepeat(false);
    ui->backwardBtn->setAutoRepeat(false);
    ui->rightBtn->setAutoRepeat(false);
    ui->leftBtn->setAutoRepeat(false);


    // Keyboard focus so we can receive key events
    setFocusPolicy(Qt::StrongFocus);

    // Reasonable Defaults
    if(auto rb = ui->rbModeJoint)      rb->setCheckable(true);
    if(auto cb = ui->chEnableMotors)   cb->setChecked(false);

    log("Robot Control ready. Connect to robot to enable motion.");
}

RobotControl::~RobotControl() { delete ui; }

QTextEdit *RobotControl::getTextRobotLog() const
{
    return ui->textRobotLog;
}

void RobotControl::setConnected(bool ok)
{
    m_connected = ok;

    const bool enable = ok; // buttons enabled only when connected
    const QList<QWidget*> controls = {
        ui->forwardBtn, ui->backwardBtn, ui->rightBtn, ui->leftBtn, ui->stopBtn,
        ui->speedSlider, ui->rbModeJoint, ui->rbModePlanar, ui->comboJoint, ui->comboAxis
    };

    for(QWidget* w : controls) if(w) w->setEnabled(enable);

    if(ui->chEnableMotors)  ui->chEnableMotors->setEnabled(true);

    log(QString("Connection: %1").arg(ok ? "Connected" : "Disconnected"));
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
    return (ui->comboJoint ? ui->comboJoint->currentIndex() + 1 : 1);
}

char RobotControl::selectedAxis() const
{
    if(!ui->comboAxis)  return 'X';
    const auto axis_value = ui->comboAxis->currentText().toUpper();
    return axis_value.contains('Z') ? 'Z' : (axis_value.contains('Y') ? 'Y' : 'X');
}

RobotControl::Mode RobotControl::mode() const
{
    return (ui->rbModePlanar && ui->rbModePlanar->isChecked() ? Planar : Joint);
}

void RobotControl::on_forwardBtn_pressed()
{
    emit driveRequested(Forward, m_speed);
    log("Drive FORWARD");
}

void RobotControl::on_forwardBtn_released()
{
    emit stopRequested();
    log("Stop");
}

void RobotControl::on_backwardBtn_pressed()
{
    emit driveRequested(Backward, m_speed);
    log("Drive: BACKWARD");
}

void RobotControl::on_backwardBtn_released()
{
    emit stopRequested();
    log("Stop");
}

void RobotControl::on_rightBtn_pressed()
{
    emit driveRequested(Right, m_speed);
    log("Drive: RIGHT");
}

void RobotControl::on_rightBtn_released()
{
    emit stopRequested();
    log("Stop");
}

void RobotControl::on_leftBtn_pressed()
{
    emit driveRequested(Left, m_speed);
    log("Drive: LEFT");
}

void RobotControl::on_leftBtn_released()
{
    emit stopRequested();
    log("Stop");
}

void RobotControl::on_stopBtn_clicked()
{
    emit stopRequested();
    log("Stop");
}

void RobotControl::on_speedSlider_valueChanged(int value)
{
    if(value < 0)   value = 0;
    if(value > 100) value = 100;

    m_speed = value;
    ui->speedValueLabel->setText(QString::number(m_speed) + "%");
    emit speedChanged(m_speed);
}

void RobotControl::log(const QString &s)
{
    if (ui->textRobotLog)
        ui->textRobotLog->append(s);
}

bool RobotControl::canDrive(const char *reasonIfNo) const
{
    if (!m_connected) {
        if (reasonIfNo) const_cast<RobotControl*>(this)->log("[Guard] Not connected.");
        return false;
    }
    if (!motorsEnabled()) {
        if (reasonIfNo) const_cast<RobotControl*>(this)->log("[Guard] Motors disabled.");
        return false;
    }
    return true;
}

void RobotControl::requestDrive(Direction d)
{
    if (!canDrive("reason")) return;
    emit driveRequested(d, speedPercent());
}
void RobotControl::on_chEnableMotors_toggled(bool checked)
{
    emit motorsEnabledChanged(checked);
    log(QString("Motors %1").arg(checked ? "ENABLED" : "DISABLED"));
}


void RobotControl::on_rbModeJoint_toggled(bool checked)
{
    if(!checked) return;
    emit modeChanged(Joint);
    log("Mode: Joint");

    // (OPTIONAL) show/hide the relevant selectors
    if(ui->comboJoint) ui->comboJoint->setVisible(true);
    if (ui->comboAxis)  ui->comboAxis->setVisible(false);
}


void RobotControl::on_rbModePlanar_toggled(bool checked)
{
    if (!checked) return;
    emit modeChanged(Planar);
    log("Mode: Planar");
    // (optional) show/hide the relevant selectors
    if (ui->comboJoint) ui->comboJoint->setVisible(false);
    if (ui->comboAxis)  ui->comboAxis->setVisible(true);
}

void RobotControl::keyPressEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat()) { e->ignore(); return; } // ignore repeats
    m_heldKeys.insert(e->key());

    switch (e->key()) {
    case Qt::Key_W:
    case Qt::Key_Up:    requestDrive(Forward);  log("Key: FORWARD");  break;
    case Qt::Key_S:
    case Qt::Key_Down:  requestDrive(Backward); log("Key: BACKWARD"); break;
    case Qt::Key_A:
    case Qt::Key_Left:  requestDrive(Left);     log("Key: LEFT");     break;
    case Qt::Key_D:
    case Qt::Key_Right: requestDrive(Right);    log("Key: RIGHT");    break;
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
        emit stopRequested(); log("Key: Stop"); e->accept(); return;
    default:
        QWidget::keyReleaseEvent(e); return;
    }

}
