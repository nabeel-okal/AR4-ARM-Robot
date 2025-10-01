#pragma once

#include <QMainWindow>
#include <QThread>

class QLabel;
class ObjectDetectionTab;
class RobotControl;
class CalibrationTab;
class Settings;
class CameraWorker;
class RobotControllerWorker;

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    // Getters
    QLabel*       getCameraStatusLabel() const;
    CameraWorker* getCameraWorker()      const;

    // Non-copyable / non-movable (QObjects shouldn’t be copied)
    MainWindow(const MainWindow&)            = delete;
    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow(MainWindow&&)                 = delete;
    MainWindow& operator=(MainWindow&&)      = delete;

    void startCamera();
    void stopCamera();

private slots:

    // timer tick to render a new "detected" frame
    void updateDetectionFrame();

private:
    // ====== UI / Tabs ======
    Ui::MainWindow*        ui           = nullptr;
    ObjectDetectionTab*    obDetTab     = nullptr;
    CalibrationTab*        calTab       = nullptr;
    RobotControl*          robotControl = nullptr;
    Settings*              settings     = nullptr;


    // ====== Workers & Threads ======
    CameraWorker*          m_camWorker = nullptr;
    RobotControllerWorker* m_robot     = nullptr;
    QThread                m_camThread;
    QThread                m_robotThread;

    // ====== State ======
    bool m_cameraRunning = false;

    // ===== Setup helpers (called from ctor) =====
    void createTabs();
    void setupRobotWorker();
    void connectSignals();

    // ====== Camera control ======


    void setupCameraStatus(bool connected);

    // (and a helper)
    void populateSerialPorts();  // fill comboPort
};
