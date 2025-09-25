#include "objectdetectiontab.h"
#include "ui_objectdetectiontab.h"

#include "mainwindow.h"

ObjectDetectionTab::ObjectDetectionTab(QWidget *parent, MainWindow *mainWindow)
    : QWidget(parent)
    , ui(new Ui::ObjectDetectionTab)
    , mainwindow(mainWindow)
{
    ui->setupUi(this);

    connect(ui->startDetectionBtn, &QPushButton::clicked, this, &ObjectDetectionTab::on_startDetectionBtn_clicked);
    connect(ui->stopDetectionBtn, &QPushButton::clicked, this, &ObjectDetectionTab::on_stopDetectionBtn_clicked);
    connect(ui->confSlider, &QSlider::valueChanged, this, &ObjectDetectionTab::on_confSlider_valueChanged);
    connect(ui->modelComboBox, &QComboBox::currentIndexChanged, this, &ObjectDetectionTab::on_modelComboBox_currentIndexChanged);

    if(ui->modelComboBox->count() == 0)
        ui->modelComboBox->addItems({"Dummy (No CV)", "YOLO (later)", "Color (later)"});

    ui->modelComboBox->setCurrentIndex(m_modelIndex);   // 0 by default

    // Slider
    ui->confSlider->setRange(0, 100);
    ui->confSlider->setValue(static_cast<int>(m_confidence * 100.0));   // e.x: 50 -> 0.50
    ui->confValueLabel->setText(QString::number(m_confidence, 'f', 2));

    ui->detectionPreviewLabel->setScaledContents(true);
}

ObjectDetectionTab::~ObjectDetectionTab()
{
    delete ui;
}

// -------------------------
// UI event handlers
// -------------------------

void ObjectDetectionTab::on_startDetectionBtn_clicked()
{
    mainwindow->getCameraStatusLabel()->setText("ON");

    if (ui->detLogTextEdit)
        ui->detLogTextEdit->appendPlainText("[Detection] Start.");
}

void ObjectDetectionTab::on_stopDetectionBtn_clicked()
{
    mainwindow->getCameraStatusLabel()->setText("OFF");

    if (ui->detLogTextEdit)
        ui->detLogTextEdit->appendPlainText("[Detection] Stop.");
}

void ObjectDetectionTab::on_confSlider_valueChanged(int value)
{
    // Clamp (safety) and map to 0.00..1.00
    if (value < 0)   value = 0;
    if (value > 100) value = 100;

    m_confidence = value / 100.0;

    // Update the numeric label immediately
    ui->confValueLabel->setText(QString::number(m_confidence, 'f', 2));

    // Log feedback
    if (ui->detLogTextEdit)
        ui->detLogTextEdit->appendPlainText(
            QString("[Detection] Confidence -> %1").arg(m_confidence, 0, 'f', 2));
}

void ObjectDetectionTab::on_modelComboBox_currentIndexChanged(int index)
{
    if(index < 0 || index >= ui->modelComboBox->count())    index = 0;

    m_modelIndex = index;

    const QString name = ui->modelComboBox->itemText(m_modelIndex);

    if (ui->detLogTextEdit)
        ui->detLogTextEdit->appendPlainText("[Detection] Model -> " + name);

    // (Optional) Example UX:
    // Disable confidence when Dummy is selected (no true detections)
    // ui->confSlider->setEnabled(m_modelIndex != 0);
}

QLabel *ObjectDetectionTab::getDetectionPreviewLabel() const
{
    return ui->detectionPreviewLabel;
}

QComboBox *ObjectDetectionTab::getModelComboBox() const
{
    return ui->modelComboBox;
}

QSlider *ObjectDetectionTab::getConfSlider() const
{
    return ui->confSlider;
}

QLabel *ObjectDetectionTab::getConfValueLabel() const
{
    return ui->confValueLabel;
}

QPlainTextEdit *ObjectDetectionTab::getDetLogTextEdit() const
{
    return ui->detLogTextEdit;
}

QPushButton *ObjectDetectionTab::getStartDetBtn() const
{
    return ui->startDetectionBtn;
}

QPushButton *ObjectDetectionTab::getStopDetBtn() const
{
    return ui->stopDetectionBtn;
}
