#pragma once
#include <QObject>
#include <QSerialPort>
#include <QTimer>

class RobotControllerWorker : public QObject {
    Q_OBJECT
public:
    explicit RobotControllerWorker(QObject *parent = nullptr);
    ~RobotControllerWorker();

signals:
    void connectedChanged(bool ok);
    void info(const QString& line);
    void error(const QString line);
    void rxLine(const QString line);    // Raw feedback (If I want to show it)

public slots:
    // connection
    void connectTo(const QString& portName, int baud = 115200);
    void disconnectFrom();

    // High-level control
    void enableMotors(bool on);
    void setSpeedPercent(int percent);
    void home();
    void stop();

    // jog (continuous while button/key held; caller sends stop() on release)
    bool jogJoint(int jointIndex, double velocityDegPerSec);     // deg/s (+/-)
    bool jogPlanar(char axis, double velocityMmPerSec);         // mm/s (+/-)

private slots:
    void onReadyRead();

private:
    QSerialPort m_port;
    int m_speedPercent = 50;

    bool writeLine(const QString& line);
};
