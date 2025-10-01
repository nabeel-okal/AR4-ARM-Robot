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

ObjectDetectionTab::ObjectDetectionTab(QWidget *parent, MainWindow *mw)
    : QWidget(parent)
    , ui(new Ui::ObjectDetectionTab)
    , m_mainWindow(mw)
{
    ui->setupUi(this);

    // --- Object Detection tab setup ---
    ui->detectionPreviewLabel->setAlignment(Qt::AlignCenter);

    connect(ui->startDetectionBtn, &QPushButton::clicked, this, &ObjectDetectionTab::on_startDetectionBtn_clicked);
    connect(ui->stopDetectionBtn,  &QPushButton::clicked, this, &ObjectDetectionTab::on_stopDetectionBtn_clicked);

    auto ui = this->findChild<Ui::ObjectDetectionTab*>("ui"); // if you keep ui pointer locally, use it instead
    // Wire UI signals (adjust to your object names)
    if (auto combo = findChild<QComboBox*>("modelComboBox")) {
        connect(combo, qOverload<int>(&QComboBox::currentIndexChanged),
                this, &ObjectDetectionTab::onModelChanged);
    }
    if (auto slider = findChild<QSlider*>("confSlider")) {
        connect(slider, &QSlider::valueChanged, this, &ObjectDetectionTab::onConfidenceChanged);
    }

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

void ObjectDetectionTab::onModelChanged(int idx) {
    m_model = static_cast<Model>(idx);
    if (auto log = getDetLogTextEdit())
        log->appendPlainText(QString("[Det] Model -> %1")
                                 .arg(idx==0? "Dummy" : idx==1? "YOLO" : "Color(HSV)"));
}

void ObjectDetectionTab::onConfidenceChanged(int v) {
    m_confidence = qBound(0, v, 100)/100.0;
    if (auto log = getDetLogTextEdit())
        log->appendPlainText(QString("[Det] Confidence -> %1%").arg(int(m_confidence*100)));
}

void ObjectDetectionTab::onCameraFrame(const QImage& frame) {
    if (frame.isNull()) return;
    QImage out;

    switch (m_model) {
    case Model::Dummy: out = runDummy(frame); break;
    case Model::Yolo:  out = runYoloStub(frame); break;   // replace later with real YOLO
    case Model::Color: out = runColorHSV(frame); break;
    }

    if (auto lbl = getDetectionPreviewLabel())
        lbl->setPixmap(QPixmap::fromImage(out));
}

// -------------------------
// UI event handlers
// -------------------------

void ObjectDetectionTab::on_startDetectionBtn_clicked()
{
    auto mw = mainwindow;                         // you already pass MainWindow* in ctor
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

    // Ensure we connect to frames exactly once
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
    auto mw = mainwindow;
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
    {
        if (frame.isNull()) return;

        QImage out;

        switch (m_modelIndex) {
        case 0: // Dummy: just overlay HUD
            out = runDummy(frame);
            break;
        case 1: // YOLO (later)
            out = runYoloStub(frame);
            break;
        case 2: // Color (HSV threshold + contours)
            out = runColorHSV(frame);
            break;
        default:
            out = frame;
            break;
        }

        showPixmap(out);
}

// --- Simple HUD (model + confidence) ---
QImage ObjectDetectionTab::drawHUD(QImage& img, const QString& modelName, double conf) const {
    QPainter p(&img);
    p.setRenderHint(QPainter::Antialiasing);
    const QString text = QString("%1 | conf: %2%").arg(modelName).arg(int(conf*100));
    QFont f = p.font(); f.setPointSizeF(f.pointSizeF() + 2); f.setBold(true); p.setFont(f);
    QRect r(10, 10, img.width()*0.6, 28);
    p.fillRect(r, QColor(0,0,0,120));
    p.setPen(Qt::white);
    p.drawText(r.adjusted(6,0,0,0), Qt::AlignVCenter|Qt::AlignLeft, text);
}

// --- Dummy: just draw HUD ---
QImage ObjectDetectionTab::runDummy(const QImage& in) const {
    QImage out = in.convertToFormat(QImage::Format_RGB888).copy();
    drawHUD(out, "Dummy", m_confidence);
    return out;
}

// --- YOLO stub: draw banner (so user sees model switched) ---
QImage ObjectDetectionTab::runYoloStub(const QImage& in) const {
    QImage out = in.convertToFormat(QImage::Format_RGB888).copy();
    QPainter p(&out);
    p.fillRect(QRect(0, out.height()-36, out.width(), 36), QColor(0,0,0,140));
    p.setPen(Qt::yellow);
    QFont f = p.font(); f.setBold(true); p.setFont(f);
    p.drawText(QRect(10, out.height()-34, out.width()-20, 30),
               Qt::AlignVCenter|Qt::AlignLeft,
               "YOLO: not implemented yet");
    drawHUD(out, "YOLO", m_confidence);
    return out;
}

// --- Color(HSV): red detection w/ contours ---
QImage ObjectDetectionTab::runColorHSV(const QImage& in) const {
    cv::Mat rgb = qimageToMatRGB(in);              // RGB
    cv::Mat hsv; cv::cvtColor(rgb, hsv, cv::COLOR_RGB2HSV);

    // Two red ranges in HSV (wrap-around). Tune with m_conf if you like:
    int sat = 100; int val = 80; // basic floor
    cv::Mat m1, m2, mask;
    cv::inRange(hsv, cv::Scalar(0, sat, val),   cv::Scalar(10, 255, 255), m1);
    cv::inRange(hsv, cv::Scalar(170, sat, val), cv::Scalar(180, 255, 255), m2);
    cv::bitwise_or(m1, m2, mask);

    // Morphology to clean noise
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, {5,5});
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);

    // Contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Draw on RGB image
    for (auto& c : contours) {
        if (cv::contourArea(c) < 200.0) continue; // ignore tiny blobs
        cv::Rect box = cv::boundingRect(c);
        cv::rectangle(rgb, box, cv::Scalar(0,255,0), 2);
        cv::putText(rgb, "RED", {box.x, std::max(0, box.y-5)},
                    cv::FONT_HERSHEY_SIMPLEX, 0.6, {0,255,0}, 2);
    }

    QImage out = matToQImageRGB(rgb);
    drawHUD(out, "Color(HSV)", m_confidence);
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
