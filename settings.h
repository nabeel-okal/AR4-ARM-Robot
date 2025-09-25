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

    QSpinBox *getCamIndexSpinBox() const;
    QComboBox *getResComboBox() const;


private slots:
    void on_btnConnectRobot_clicked();
    void on_btnSave_clicked();
    void on_btnLoad_clicked();

private:
    Ui::Settings *ui;
    void loadSettings();
    void saveSettings();

    // Maybe add resetSettings function (BELOW)
};

#endif // SETTINGS_H
