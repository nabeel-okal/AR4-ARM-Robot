#include "objectdetectiontab.h"
#include "ui_objectdetectiontab.h"
#include "mainwindow.h"


#include <QPainter>
#include <QPen>
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
    , mainwindow(mainWindow)
{
    ui->setupUi(this);

    // --- Object Detection tab setup ---
    ui->detectionPreviewLabel->setAlignment(Qt::AlignCenter);

    connect(ui->startDetectionBtn, &QPushButton::clicked, this, &ObjectDetectionTab::on_startDetectionBtn_clicked);
    connect(ui->stopDetectionBtn,  &QPushButton::clicked, this, &ObjectDetectionTab::on_stopDetectionBtn_clicked);
    connect(ui->confSlider,        &QSlider::valueChanged, this, &ObjectDetectionTab::on_confSlider_valueChanged);
    connect(ui->modelComboBox,     QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ObjectDetectionTab::on_modelComboBox_currentIndexChanged);

    if(ui->modelComboBox->count() == 0)
        ui->modelComboBox->addItems({"Dummy (No CV)", "YOLO (later)", "Color (HSV)"});

    ui->modelComboBox->setCurrentIndex(m_modelIndex);   // 0 by default

    // Slider
    ui->confSlider->setRange(0, 100);
    ui->confSlider->setValue(static_cast<int>(m_confidence * 100.0));   // e.x: 50 -> 0.50
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
     // Connect once to the camera frames (idempotent: disconnect old first)
    if(m_frameConn)
         disconnect(m_frameConn);

    auto cam = mainwindow->getCameraWorker();

    if(!cam){
        logLine("[Detection] ERROR: Camera worker not available.");
        return;
    }

    m_frameConn = connect(cam, &CameraWorker::frameReady, this, &ObjectDetectionTab::onFrameReady, Qt::QueuedConnection);
    mainwindow->getCameraStatusLabel()->setText("ON");
    logLine("[Detection] Start.");
}

void ObjectDetectionTab::on_stopDetectionBtn_clicked()
{
    if(m_frameConn){
        disconnect(m_frameConn);
        m_frameConn = QMetaObject::Connection{};
    }

    mainwindow->getCameraStatusLabel()->setText("OFF");
    logLine("[Detection] Stop.");
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
    // Defensive: ensure we have valid pixels
    if (frame.isNull()) return;

    QImage out;

    switch (m_modelIndex) {
    case 0: // Dummy: just overlay HUD
        out = drawHUD(frame);
        break;
    case 1: // YOLO (later)
        // For now, show HUD stating YOLO stub
        out = drawHUD(frame);
        {
            QPainter p(&out);
            p.setRenderHint(QPainter::Antialiasing, true);
            p.setPen(QPen(Qt::yellow, 2));
            p.setBrush(Qt::NoBrush);
            p.drawText(12, 36, "YOLO: not implemented yet");
        }
        break;
    case 2: // Color (HSV threshold + contours)
        out = processColorModel(frame);
        break;
    default:
        out = frame;
        break;
    }

    showPixmap(out);
}

QImage ObjectDetectionTab::drawHUD(const QImage &in) const
{
    QImage out = in.convertToFormat(QImage::Format_RGB888);
    QPainter painter(&out);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Text box background (semi-transparent)
    auto drawBadge = [&](const QPoint& tl, const QString& text){
        QFont f = painter.font(); f.setPointSizeF(10.0); painter.setFont(f);
        QFontMetrics fm(f);
        const int pad = 6;
        QRect r = fm.boundingRect(text);
        r.adjust(-pad, -pad, pad, pad);
        r.moveTopLeft(tl);

        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0,0,0,128));
        painter.drawRoundedRect(r, 6, 6);

        painter.setPen(Qt::white);
        painter.drawText(r.adjusted(pad, pad, -pad, -pad), Qt::AlignLeft|Qt::AlignVCenter, text);
    };

    const QString model = ui->modelComboBox->currentText();
    drawBadge(QPoint(12, 12), QString("Model: %1 | Conf: %2")
                                  .arg(model).arg(m_confidence, 0, 'f', 2));
    return out;
}

QImage ObjectDetectionTab::processColorModel(const QImage &in) const
{
    // Convert QImage -> cv::Mat (RGB), then to HSV
    cv::Mat rgb = qimageToMatRGB(in);               // RGB888
    cv::Mat hsv; cv::cvtColor(rgb, hsv, cv::COLOR_RGB2HSV);

    // --- Simple default: detect “red-like” regions (two ranges in HSV) ---
    // You can later expose these thresholds in UI.
    cv::Mat mask1, mask2, mask;
    cv::inRange(hsv, cv::Scalar(0,   100, 80),  cv::Scalar(10,  255, 255), mask1);
    cv::inRange(hsv, cv::Scalar(170, 100, 80),  cv::Scalar(180, 255, 255), mask2);
    cv::bitwise_or(mask1, mask2, mask);

    // Morph a bit to clean noise
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3,3));
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel, cv::Point(-1,-1), 1);
    cv::morphologyEx(mask, mask, cv::MORPH_DILATE, kernel, cv::Point(-1,-1), 1);

    // Find contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Prepare drawing canvas
    QImage out = in.convertToFormat(QImage::Format_RGB888);
    QPainter p(&out);
    p.setRenderHint(QPainter::Antialiasing, true);

    // Compute per-contour "confidence": fraction of in-range pixels within the bbox (simple heuristic)
    int kept = 0;
    for (const auto& c : contours) {
        cv::Rect bbox = cv::boundingRect(c);
        if (bbox.area() < 100) continue; // ignore tiny blobs

        // clamp bbox to image
        bbox &= cv::Rect(0,0, rgb.cols, rgb.rows);
        if (bbox.area() <= 0) continue;

        cv::Mat roiMask = mask(bbox);
        double inRangeCount = static_cast<double>(cv::countNonZero(roiMask));
        double conf = inRangeCount / static_cast<double>(bbox.area()); // 0..1

        if (conf < m_confidence) continue; // gate by slider
        kept++;

        // Draw rectangle + label
        QRect r(bbox.x, bbox.y, bbox.width, bbox.height);
        p.setPen(QPen(QColor(0, 200, 0), 2));
        p.setBrush(Qt::NoBrush);
        p.drawRect(r);

        QString caption = QString("color_obj %.2f").arg(conf);
        // text background
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

    // HUD
    {
        QString hud = QString("Model: Color | Conf: %1  | kept=%2").arg(m_confidence,0,'f',2).arg(kept);
        QPainter ph(&out);
        QFont f = ph.font(); f.setPointSizeF(10.0); ph.setFont(f);
        QFontMetrics fm(f);
        int pad = 6;
        QRect r = fm.boundingRect(hud); r.adjust(-pad,-pad,pad,pad); r.moveTopLeft(QPoint(12,12));
        ph.setPen(Qt::NoPen); ph.setBrush(QColor(0,0,0,128)); ph.drawRoundedRect(r,6,6);
        ph.setPen(Qt::white); ph.drawText(r.adjusted(pad,pad,-pad,-pad), hud);
    }

    return out;
}

void ObjectDetectionTab::showPixmap(const QImage &img) const
{
    // Keep aspect ratio when fitting into the preview label
    const QSize labelSize = ui->detectionPreviewLabel->size();
    const QPixmap pix = QPixmap::fromImage(img).scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->detectionPreviewLabel->setPixmap(pix);
}

// ----------------------
// Rendering helpers
// ----------------------

void ObjectDetectionTab::logLine(const QString &s) const
{
    if(ui->detLogTextEdit) ui->detLogTextEdit->appendPlainText(s);
}
