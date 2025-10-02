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
class QKeyEvent;
class QFocusEvent;
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

    // Public API for window/connection state
    void setConnected(bool ok);                        // enable/disable controls when robot connects
    bool isConnected() const { return m_connected; }

    enum Direction { Forward, Backward, Right, Left };
    enum Mode { Joint, Planar };

    Mode mode() const;              // reads rbModeJoint / rbModePlanar
    bool motorsEnabled() const;     // reads chEnableMotors
    int  speedPercent() const;      // 0..100
    int  selectedJoint() const;     // 1..6
    char selectedAxis() const;      // 'X','Y','Z'

signals:
    void driveRequested(Direction dir, int speedPercent);   // 0..100
    void stopRequested();
    void speedChanged(int speedPercent);                    // 0..100
    void motorsEnabledChanged(bool on);
    void modeChanged(RobotControl::Mode m);

protected:
    // Keyboard driving (W/A/S/D and arrow keys)
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void focusOutEvent(QFocusEvent *e) override;

private slots:
    // Buttons (press/hold to jog, release to stop)
    void on_forwardBtn_pressed();
    void on_forwardBtn_released();
    void on_backwardBtn_pressed();
    void on_backwardBtn_released();
    void on_rightBtn_pressed();
    void on_rightBtn_released();
    void on_leftBtn_pressed();
    void on_leftBtn_released();
    void on_stopBtn_clicked();

    // Speed slider
    void on_speedSlider_valueChanged(int value);

    // CheckBoxes / RadioButtons
    void on_chEnableMotors_toggled(bool checked);
    void on_rbModeJoint_toggled(bool checked);
    void on_rbModePlanar_toggled(bool checked);

private:
    Ui::RobotControl *ui;

    int  m_speed      = 50;           // default %
    bool m_connected  = false;        // set by MainWindow when robot connects
    QSet<int> m_heldKeys;             // to ignore auto-repeat in keyboard

    // helpers
    void log(const QString& s);
    QString ts() const;               // timestamp string
    bool canDrive(bool logReason) const;   // connection + motors guard
    void requestDrive(Direction d);        // applies canDrive(); emits or logs why not
    void ensureStopped(const QString& why = QString()); // emit stopRequested once (with log)
    void setDriveControlsEnabled(bool on); // enable/disable driving widgets
    void populateCombosOnce();             // joint/axis combos
};
