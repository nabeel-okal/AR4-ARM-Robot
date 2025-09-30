#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPixmap>
#include <QTimer>
#include <QRandomGenerator>
#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QThread>

#include "calibrationtab.h"
#include "robotcontrol.h"
#include "settings.h"
#include "cameraworker.h"
#include "robotcontrollerworker.h"

class ObjectDetectionTab;
class RobotControl;
class CalibrationTab;
class Settings;
class CameraWorker;
class RobotControllerWorker;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Getters
    QLabel* getCameraStatusLabel() const;
    CameraWorker* getCameraWorker() const;

private slots:

     // timer tick to render a new "detected" frame
    void updateDetectionFrame();

private:
    Ui::MainWindow *ui;

    ObjectDetectionTab *obDetTab;
    CalibrationTab *calTab;
    RobotControl *robotControl;
    Settings *settings;
    CameraWorker *m_camWorker;
    RobotControllerWorker *m_robot = nullptr;

    void init();
    void setCameraStatus(bool connected);

    QThread m_camThread;
    QThread m_robotThread;
    bool m_cameraRunning = false;

private:
    void startCamera();
    void stopCamera();

    // (and a helper)
    void populateSerialPorts();  // fill comboPort
};
#endif // MAINWINDOW_H
