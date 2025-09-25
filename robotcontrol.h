#pragma once
#include <QWidget>
#include <QSet>

QT_BEGIN_NAMESPACE
class QPushButton;
class QSlider;
class QLabel;
class QTextEdit;
class QCheckBox;
class QRadioButton;
class QComboBox;
QT_END_NAMESPACE

namespace Ui { class RobotControl; }

class RobotControl : public QWidget
{
    Q_OBJECT

public:
    explicit RobotControl(QWidget *parent = nullptr);
    ~RobotControl();

    // Getters
    QTextEdit *getTextRobotLog() const;

    // New: public API for window/connection state
    void setConnected(bool ok);      // disable/enable controls when robot connects
    bool isConnected() const { return m_connected; }

    enum Direction { Forward, Backward, Right, Left };
    enum Mode { Joint, Planar };

    Mode mode() const;              // reads rbModeJoint / rbModePlanar
    bool motorsEnabled() const;     // reads chkEnableMotors
    int speedPercent() const;       // 0..100
    int selectedJoint() const;      // 1..6   (if you added comboJoint)
    char selectedAxis() const;      // 'X','Y','Z' (if you added comboAxis)

signals:
    void driveRequested(Direction dir, int speedPercent);   // 0 .. 100
    void stopRequested();
    void speedChanged(int speedPercent);    // 0 .. 100

    void motorsEnabledChanged(bool on);
    void modeChanged(RobotControl::Mode m);

protected:
    // Key controls (WASD/arrows)
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

private slots:
    // buttons
    void on_forwardBtn_pressed();
    void on_forwardBtn_released();

    void on_backwardBtn_pressed();
    void on_backwardBtn_released();

    void on_rightBtn_pressed();
    void on_rightBtn_released();

    void on_leftBtn_pressed();
    void on_leftBtn_released();

    void on_stopBtn_clicked();

    // Speed
    void on_speedSlider_valueChanged(int value);

    // CheckBoxes and RadioButtons slots
    void on_chEnableMotors_toggled(bool checked);
    void on_rbModeJoint_toggled(bool checked);
    void on_rbModePlanar_toggled(bool checked);

private:
    Ui::RobotControl *ui;
    int m_speed = 50;           // default %
    bool m_connected = false;   // set by MainWindow when robot connects
    QSet<int> m_heldKeys;       // to ignore auto-repeat in keyboard

    void log(const QString& s);
    bool canDrive(const char* reasonIfNo = nullptr) const;  // deadman + connection
    void requestDrive(Direction d);     // applies canDrive(); emits or logs why not
};
