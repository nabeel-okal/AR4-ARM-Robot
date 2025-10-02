#include "objectdetectiontab.h"
#include "ui_objectdetectiontab.h"
#include "mainwindow.h"

#include <QPainter>
#include <QPen>
#include <QPlainTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QSlider>
#include <QBrush>
#include <QtMath>
#include <algorithm>

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>

// --- QImage <-> cv::Mat helpers (RGB888 path) ---
static cv::Mat qimageToMatRGB(const QImage& img)
{
    QImage tmp = img.convertToFormat(QImage::Format_RGB888);
    return cv::Mat(tmp.height(), tmp.width(), CV_8UC3,
                   const_cast<uchar*>(tmp.bits()), tmp.bytesPerLine()).clone();
}

static QImage matToQImageRGB(const cv::Mat& m)
{
    cv::Mat rgb;
    if (m.type() == CV_8UC3) {
        rgb = m;
    } else if (m.type() == CV_8UC1) {
        cv::cvtColor(m, rgb, cv::COLOR_GRAY2RGB);
    } else if (m.type() == CV_8UC4) {
        cv::cvtColor(m, rgb, cv::COLOR_BGRA2RGB);
    } else {
        // Fallback
        cv::Mat tmp;
        m.convertTo(tmp, CV_8UC3);
        rgb = tmp;
    }
    return QImage(rgb.data, rgb.cols, rgb.rows, static_cast<int>(rgb.step), QImage::Format_RGB888).copy();
}

ObjectDetectionTab::ObjectDetectionTab(QWidget *parent, MainWindow *mainWindow)
    : QWidget(parent)
    , ui(new Ui::ObjectDetectionTab)
    , m_mainWindow(mainWindow)
{
    ui->setupUi(this);

    // --- Object Detection tab setup ---
    ui->detectionPreviewLabel->setAlignment(Qt::AlignCenter);

    connect(ui->startDetectionBtn, &QPushButton::clicked, this, &ObjectDetectionTab::on_startDetectionBtn_clicked);
    connect(ui->stopDetectionBtn,  &QPushButton::clicked, this, &ObjectDetectionTab::on_stopDetectionBtn_clicked);
    connect(ui->confSlider,        &QSlider::valueChanged, this, &ObjectDetectionTab::on_confSlider_valueChanged);
    connect(ui->modelComboBox,     QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ObjectDetectionTab::on_modelComboBox_currentIndexChanged);

    if(ui->modelComboBox->count() == 0)
        ui->modelComboBox->addItems({"Dummy (No CV)", "YOLO (later)", "Color (HSV)"});

    ui->modelComboBox->setCurrentIndex(m_modelIndex);   // 0 by default

    // Slider
    ui->confSlider->setRange(0, 100);
    ui->confSlider->setValue(static_cast<int>(m_confidence * 100.0));   // e.g.: 50 -> 0.50
    ui->confValueLabel->setText(QString::number(m_confidence, 'f', 2));

    ui->detectionPreviewLabel->setScaledContents(false);
}

ObjectDetectionTab::~ObjectDetectionTab()
{
    if(m_frameConn)
        disconnect(m_frameConn);

    delete ui;
}

// -------------------------
// UI event handlers
// -------------------------

void ObjectDetectionTab::on_startDetectionBtn_clicked()
{
    auto mw = m_mainWindow;
    if (!mw) return;

    // If no worker yet, start the camera now
    if (!mw->getCameraWorker()) {
        mw->startCamera();  // creates m_camWorker, moves to thread, starts it
    }

    // Still nothing? Bail with a clear message
    if (!mw->getCameraWorker()) {
        if (auto log = getDetLogTextEdit())
            log->appendPlainText("[Camera] Camera Worker is not available.");
        return;
    }

    // Ensure we connect to frames exactly once — route to our processing slot
    if (!m_frameConn) {
        m_frameConn = connect(mw->getCameraWorker(), &CameraWorker::frameReady,
                              this, &ObjectDetectionTab::onFrameReady,
                              Qt::QueuedConnection);
    }

    if (auto log = getDetLogTextEdit())
        log->appendPlainText("[Camera] Start requested.");

    mw->getCameraStatusLabel()->setText("ON");
}

void ObjectDetectionTab::on_stopDetectionBtn_clicked()
{
    auto mw = m_mainWindow;
    if (!mw) return;

    // Disconnect frame updates from the (possibly soon-to-be-deleted) worker
    if (m_frameConn) {
        disconnect(m_frameConn);
        m_frameConn = {};
    }

    mw->stopCamera();

    if (auto log = getDetLogTextEdit())
        log->appendPlainText("[Camera] Stop requested.");

    mw->getCameraStatusLabel()->setText("OFF");
}

void ObjectDetectionTab::on_confSlider_valueChanged(int value)
{
    value = std::clamp(value, 0, 100);
    m_confidence = value / 100.0;
    ui->confValueLabel->setText(QString::number(m_confidence, 'f', 2));
    logLine(QString("[Detection] Confidence -> %1").arg(m_confidence));
}

void ObjectDetectionTab::on_modelComboBox_currentIndexChanged(int index)
{
    if(index < 0 || index >= ui->modelComboBox->count()) index = 0;

    m_modelIndex = index;

    const QString name = ui->modelComboBox->itemText(m_modelIndex);
    logLine("[Detection] Model -> " + name);

    // (Optional) Example UX:
    // Disable confidence when Dummy is selected (no true detections)
    ui->confSlider->setEnabled(m_modelIndex != 0);
}

QLabel *ObjectDetectionTab::getDetectionPreviewLabel() const { return ui->detectionPreviewLabel; }
QComboBox *ObjectDetectionTab::getModelComboBox() const { return ui->modelComboBox; }
QSlider *ObjectDetectionTab::getConfSlider() const { return ui->confSlider; }
QLabel *ObjectDetectionTab::getConfValueLabel() const { return ui->confValueLabel; }
QPlainTextEdit *ObjectDetectionTab::getDetLogTextEdit() const { return ui->detLogTextEdit; }
QPushButton *ObjectDetectionTab::getStartDetBtn() const { return ui->startDetectionBtn; }
QPushButton *ObjectDetectionTab::getStopDetBtn() const { return ui->stopDetectionBtn; }

// -------------------
// Frame handler
// -------------------

void ObjectDetectionTab::onFrameReady(const QImage &frame)
{
    if (frame.isNull()) return;

    QImage out;
    switch (m_modelIndex) {
    case 0: out = runDummy(frame);    break;  // Dummy
    case 1: out = runYoloStub(frame); break;  // YOLO stub
    case 2: out = runColorHSV(frame); break;  // Color(HSV)
    default: out = frame;             break;
    }

    showPixmap(out);
}

// ----------------------
// Model processors
// ----------------------

QImage ObjectDetectionTab::runDummy(const QImage& in) const
{
    QImage out = in.convertToFormat(QImage::Format_RGB888).copy();
    return drawHUD(out, "Dummy");
}

QImage ObjectDetectionTab::runYoloStub(const QImage& in) const
{
    QImage out = in.convertToFormat(QImage::Format_RGB888).copy();

    // Bottom banner so the user sees the mode changed
    {
        QPainter p(&out);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.fillRect(QRect(0, out.height()-36, out.width(), 36), QColor(0,0,0,140));
        p.setPen(Qt::yellow);
        QFont f = p.font(); f.setBold(true); p.setFont(f);
        p.drawText(QRect(10, out.height()-34, out.width()-20, 30),
                   Qt::AlignVCenter|Qt::AlignLeft,
                   "YOLO: not implemented yet");
    }

    return drawHUD(out, "YOLO");
}

QImage ObjectDetectionTab::runColorHSV(const QImage& in) const
{
    cv::Mat rgb = qimageToMatRGB(in);              // RGB
    cv::Mat hsv; cv::cvtColor(rgb, hsv, cv::COLOR_RGB2HSV);

    // Two red ranges in HSV (wrap-around). Tune if needed.
    int sat = 100;
    int val = 80;
    cv::Mat m1, m2, mask;
    cv::inRange(hsv, cv::Scalar(0,   sat, val), cv::Scalar(10,  255, 255), m1);
    cv::inRange(hsv, cv::Scalar(170, sat, val), cv::Scalar(180, 255, 255), m2);
    cv::bitwise_or(m1, m2, mask);

    // Morphology to clean noise
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, {5,5});
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN,  kernel);
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);

    // Contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Draw on RGB image with a simple confidence heuristic
    QImage out = in.convertToFormat(QImage::Format_RGB888).copy();
    QPainter p(&out);
    p.setRenderHint(QPainter::Antialiasing, true);

    int kept = 0;
    for (auto& c : contours) {
        if (cv::contourArea(c) < 200.0) continue;
        cv::Rect box = cv::boundingRect(c);
        box &= cv::Rect(0,0, rgb.cols, rgb.rows);
        if (box.area() <= 0) continue;

        cv::Mat roiMask = mask(box);
        double inRangeCount = static_cast<double>(cv::countNonZero(roiMask));
        double conf = inRangeCount / static_cast<double>(box.area()); // 0..1

        if (conf < m_confidence) continue;
        kept++;

        QRect r(box.x, box.y, box.width, box.height);
        p.setPen(QPen(QColor(0,255,0), 2));
        p.setBrush(Qt::NoBrush);
        p.drawRect(r);

        QString caption = QString("RED %.2f").arg(conf);
        QFont f = p.font(); f.setPointSizeF(10.0); p.setFont(f);
        QFontMetrics fm(f);
        int pad = 4;
        QRect tr = fm.boundingRect(caption);
        tr.adjust(-pad, -pad, pad, pad);
        tr.moveTopLeft(QPoint(r.left(), std::max(0, r.top()-tr.height()-2)));

        p.setPen(Qt::NoPen);
        p.setBrush(QColor(0,0,0,150));
        p.drawRoundedRect(tr, 4, 4);

        p.setPen(Qt::white);
        p.drawText(tr.adjusted(pad, pad, -pad, -pad), caption);
    }

    // HUD with kept count
    out = drawHUD(out, QString("Color | kept=%1").arg(kept));
    return out;
}

// ----------------------
// Rendering helpers
// ----------------------

QImage ObjectDetectionTab::drawHUD(QImage img, const QString& modelName) const
{
    QPainter painter(&img);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const QString text = QString("Model: %1 | Conf: %2")
                             .arg(modelName)
                             .arg(m_confidence, 0, 'f', 2);

    // Badge
    QFont f = painter.font();
    f.setPointSizeF(10.0);
    painter.setFont(f);

    QFontMetrics fm(f);
    const int pad = 6;
    QRect r = fm.boundingRect(text);
    r.adjust(-pad, -pad, pad, pad);
    r.moveTopLeft(QPoint(12, 12));

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0,0,0,128));
    painter.drawRoundedRect(r, 6, 6);

    painter.setPen(Qt::white);
    painter.drawText(r.adjusted(pad, pad, -pad, -pad),
                     Qt::AlignLeft|Qt::AlignVCenter, text);

    return img;
}

void ObjectDetectionTab::showPixmap(const QImage &img) const
{
    const QSize labelSize = ui->detectionPreviewLabel->size();
    const QPixmap pix = QPixmap::fromImage(img)
                            .scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->detectionPreviewLabel->setPixmap(pix);
}

void ObjectDetectionTab::logLine(const QString &s) const
{
    if(ui->detLogTextEdit) ui->detLogTextEdit->appendPlainText(s);
}
