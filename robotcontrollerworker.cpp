#include "robotcontrollerworker.h"

#include <cctype>

RobotControllerWorker::RobotControllerWorker(QObject *parent)
    : QObject{parent} {}

RobotControllerWorker::~RobotControllerWorker() {
    if(m_port.isOpen()) m_port.close();
}

void RobotControllerWorker::connectTo(const QString &portName, int baud)
{
    if(m_port.isOpen()) m_port.close();

    m_port.setPortName(portName);
    m_port.setBaudRate(baud);
    m_port.setDataBits(QSerialPort::Data8);
    m_port.setParity(QSerialPort::NoParity);
    m_port.setStopBits(QSerialPort::OneStop);
    m_port.setFlowControl(QSerialPort::NoFlowControl);

    if(!m_port.open(QIODevice::ReadWrite)){
        emit error(QString("Failed to open %1: %2").arg(portName).arg(m_port.errorString()));
        emit connectedChanged(false);
        return;
    }

    connect(&m_port, &QSerialPort::readyRead, this, &RobotControllerWorker::onReadyRead);
    emit info(QString("Opened %1 @ %2").arg(portName).arg(baud));
    emit connectedChanged(true);

    // TODO (optional): send any init/handshake here for AR4
}

void RobotControllerWorker::disconnectFrom()
{
    if(m_port.isOpen()) {
        m_port.close();
        emit info("Port closed.");
    }
    emit connectedChanged(false);
}

bool RobotControllerWorker::writeLine(const QString &line)
{
    if(!m_port.isOpen()) {
        emit error("Port not open.");
        return false;
    }

    const QByteArray bytes = (line + "\r\n").toUtf8();
    const qint64 n = m_port.write(bytes);

    if(n != bytes.size()) {
        emit error(QString("Write failed: &1").arg(m_port.errorString()));
        return false;
    }
    m_port.flush();
    emit info("TX: " + line);
    return true;
}


void RobotControllerWorker::enableMotors(bool on)
{
    // TODO: AR4 protocol
    // Example placeholders:
    // writeLine(on ? "MOTORS ON" : "MOTORS OFF");
    writeLine(on ? "ENABLE" : "DISABLE");
}

void RobotControllerWorker::setSpeedPercent(int percent)
{
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;

    m_speedPercent = percent;
    // TODO: AR4 protocol
    // Example: writeLine(QString("SPEED %1").arg(m_speedPercent));
    writeLine(QString("SPEED %1").arg(m_speedPercent));
}

void RobotControllerWorker::home()
{
    // TODO: AR4 protocol
    writeLine("HOME");
}

void RobotControllerWorker::stop()
{
    // TODO: AR4 protocol
    writeLine("STOP");
}

bool RobotControllerWorker::jogJoint(int jointIndex, double velocityDegPerSec)
{
    if (!m_port.isOpen()) {
        emit error("Port not open.");
        return false;
    }
    // 1) validate inputs
    if (jointIndex < 1 || jointIndex > 6) {
        emit error("Invalid joint index (must be 1..6).");
        return false;
    }

    // 2) apply speed scaling (UI slider)
    const double scale = qBound(0, m_speedPercent, 100) / 100.0;
    const double v = velocityDegPerSec * scale; // final velocity

    // 3) format the controller command
    // TODO: replace with AR4’s real string. Example placeholders:
    // "JOGJ <joint> <vel_deg_s>"
    const QString cmd = QString("JOGJ %1 %2").arg(jointIndex).arg(v, 0, 'f', 3);

    // 4) send it as a line (adds \r\n, flushes, logs)
    return writeLine(cmd);
}

bool RobotControllerWorker::jogPlanar(char axis, double velocityMmPerSec)
{
    if (!m_port.isOpen()) {
        emit error("Port not open.");
        return false;
    }
    // 1) validate inputs
    axis = toupper(axis);
    if (!(axis == 'X' || axis == 'Y' || axis == 'Z')) {
        emit error("Axis must be X, Y, or Z.");
        return false;
    }

    // 2) apply speed scaling
    const double scale = qBound(0, m_speedPercent, 100) / 100.0;
    const double v = velocityMmPerSec * scale;

    // 3) format the controller command
    // TODO: replace with AR4’s real string. Example placeholders:
    // "JOGC <axis> <vel_mm_s>"
    const QString cmd = QString("JOGC %1 %2").arg(axis).arg(v, 0, 'f', 3);

    // 4) send
    return writeLine(cmd);
}

void RobotControllerWorker::onReadyRead()
{
    while (m_port.canReadLine()) {
        const QByteArray line = m_port.readLine();
        const QString s = QString::fromUtf8(line).trimmed();
        emit rxLine(s);
        // TODO (optional): parse feedback/state here and emit typed signals
    }
}
