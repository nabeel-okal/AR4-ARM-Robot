#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QMessageBox>
#include <QSettings>
#include <QSpinBox>
#include <QComboBox>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    QSpinBox  *getCamIndexSpinBox() const;
    QComboBox *getResComboBox()     const;

signals:
    void requestConnectSerial(QString host, int port);
    void requestDisconnect();
    void requestPing(QString cmd, int timeoutMs);

    // robotStatusLabel when connected (GREEN) else (RED)
    void robotStatusMessage(const QString msg);

public slots:
    void onRobotConnectedChanged(bool connected);
    void onRobotError(QString message);
    // void onRobotRx(QString line);
    // void onRobotTx(QString line);

private slots:
    void on_btnConnectRobot_clicked();
    void on_btnSave_clicked();
    void on_btnLoad_clicked();
    void on_refreshPortsBtn_clicked();

private:
    Ui::Settings *ui;
    void loadSettings();
    void saveSettings();
    void populateSerialPorts();
};

#endif // SETTINGS_H
