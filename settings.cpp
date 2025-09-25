#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);

    // Adding resolution samples in a comboBox

    QStringList res_coll;
    res_coll << "640x480" << "1280x720" << "1920x1080" << "2560x1440" << "3840x2160";

    for(QString res: res_coll)
        ui->comboResolution->addItem(res);

}

Settings::~Settings()
{
    delete ui;
}

QSpinBox *Settings::getCamIndexSpinBox() const
{
    return ui->spinCameraIndex;
}

QComboBox *Settings::getResComboBox() const
{
    return ui->comboResolution;
}

void Settings::on_btnConnectRobot_clicked()
{
    QString IP = ui->lineRobotIP->text();
    int PORT = ui->spinRobotPort->value();

    QMessageBox::information(this, "Robot Connection", QString("Connecting to robot at %1 %2").arg(IP).arg(PORT));
    // TODO: replace with actual robot communication code
}


void Settings::on_btnSave_clicked()
{
    saveSettings();
    QMessageBox::information(this, "Settings", "Settings saved successfully!");
}


void Settings::on_btnLoad_clicked()
{
    loadSettings();
    QMessageBox::information(this, "Settings", "Settings loaded successfully!");
}

void Settings::loadSettings()
{
    QSettings settings("MyCompany", "AR4_PickAndPlace");

    ui->lineRobotIP->setText(settings.value("robot/ip", "192.168.0.100").toString());
    ui->spinRobotPort->setValue(settings.value("robot/port", 5000).toInt());
    ui->spinCameraIndex->setValue(settings.value("camera/index", 0).toInt());

    QString res = settings.value("camera/resolution", "640x480").toString();
    int index = ui->comboResolution->findText(res);
    if (index >= 0) ui->comboResolution->setCurrentIndex(index);

    ui->chkAutoConnect->setChecked(settings.value("app/autoConnect", false).toBool());
    ui->chkDarkMode->setChecked(settings.value("app/darkMode", false).toBool());
}

void Settings::saveSettings()
{
    QSettings settings("MyCompany", "AR4_PickAndPlace");

    settings.setValue("robot/ip", ui->lineRobotIP->text());
    settings.setValue("robot/port", ui->spinRobotPort->value());
    settings.setValue("camera/index", ui->spinCameraIndex->value());
    settings.setValue("camera/resolution", ui->comboResolution->currentText());
    settings.setValue("app/autoConnect", ui->chkAutoConnect->isChecked());
    settings.setValue("app/darkMode", ui->chkDarkMode->isChecked());
}

