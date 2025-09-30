#include "settings.h"
#include "ui_settings.h"

#include <QSerialPortInfo>

Settings::Settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);

    // Adding resolution samples in a comboBox
    for (const QString &res : QStringList{"640x480","1280x720","1920x1080","2560x1440","3840x2160"})
        ui->comboResolution->addItem(res);

    // Baud rate samples
    for (int b: {9600, 19200, 38400, 57600, 115200})
        ui->comboBaud->addItem(QString::number(b));
    ui->comboBaud->setCurrentText("115200");

    populateSerialPorts();
    loadSettings();

    // Refresh button connection
    connect(ui->refreshPortsBtn, &QPushButton::clicked, this, &Settings::on_refreshPortsBtn_clicked);
}

Settings::~Settings()
{
    delete ui;
}

QSpinBox *Settings::getCamIndexSpinBox() const { return ui->spinCameraIndex; }
QComboBox *Settings::getResComboBox() const { return ui->comboResolution; }

void Settings::onRobotConnectedChanged(bool connected)
{
    connected ? emit robotStatusMessage("ON") : emit robotStatusMessage("OFF");
}

void Settings::onRobotError(QString message) { QMessageBox::warning(this, "Error!", message); onRobotConnectedChanged(false); }

// void Settings::onRobotRx(QString line) { /* optionally show somewhere */ }

// void Settings::onRobotTx(QString line) { /* optionally show somewhere */ }

void Settings::on_btnConnectRobot_clicked()
{
    saveSettings(); // persist first

    const QString port = ui->comboSerialPort->currentText().trimmed();
    const int baud = ui->comboBaud->currentText().toInt();

    if(port.isEmpty()) { QMessageBox::warning(this, "Warning!", "No serial port selected."); return; }

    emit requestConnectSerial(port, baud);
    onRobotConnectedChanged(true);
}

void Settings::on_btnSave_clicked()
{
    saveSettings();
    QMessageBox::information(this, "Saved!", "Settings saved successfully!");
}


void Settings::on_btnLoad_clicked()
{
    loadSettings();
    QMessageBox::information(this, "Loaded!", "Settings loaded successfully!");
}

void Settings::loadSettings()
{
    QSettings settings("MyCompany", "AR4_PickAndPlace");

    // Camera
    ui->spinCameraIndex->setValue(settings.value("camera/index", 0).toInt());
    const QString res = settings.value("camera/resolution","640x480").toString();
    const int rIdx = ui->comboResolution->findText(res);
    if (rIdx >= 0) ui->comboResolution->setCurrentIndex(rIdx);

    // Serial
    const QString savedPort = settings.value("robot/serialPort").toString();
    int pIdx = ui->comboSerialPort->findText(savedPort);
    if (pIdx < 0 && !savedPort.isEmpty()) { ui->comboSerialPort->addItem(savedPort); pIdx = ui->comboSerialPort->count()-1; }
    if (pIdx >= 0) ui->comboSerialPort->setCurrentIndex(pIdx);
    ui->comboBaud->setCurrentText(settings.value("robot/baud", 115200).toString());

    // App
    ui->chkAutoConnect->setChecked(settings.value("app/autoConnect", false).toBool());
    ui->chkDarkMode->setChecked(settings.value("app/darkMode", false).toBool());
}

void Settings::saveSettings()
{
    QSettings settings("MyCompany", "AR4_PickAndPlace");

    // Serial
    settings.setValue("robot/serialPort", ui->comboSerialPort->currentText());
    settings.setValue("robot/baud", ui->comboBaud->currentText().toInt());

    // Camera
    settings.setValue("camera/index", ui->spinCameraIndex->value());
    settings.setValue("camera/resolution", ui->comboResolution->currentText());

    // App
    settings.setValue("app/autoConnect", ui->chkAutoConnect->isChecked());
    settings.setValue("app/darkMode", ui->chkDarkMode->isChecked());
}

void Settings::populateSerialPorts()
{
    ui->comboSerialPort->clear();
    for (const QSerialPortInfo &info: QSerialPortInfo::availablePorts())
        ui->comboSerialPort->addItem(info.systemLocation()); // e.g. /dev/ttyUSB0
}


void Settings::on_refreshPortsBtn_clicked()
{
    populateSerialPorts();
}
