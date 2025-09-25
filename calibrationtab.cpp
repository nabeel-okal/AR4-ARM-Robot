#include "calibrationtab.h"
#include "ui_calibrationtab.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QLabel>
#include <QSignalBlocker>

CalibrationTab::CalibrationTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CalibrationTab)
{
    ui->setupUi(this);

    // Preview
    ui->lblPreview->setMinimumSize(320, 240);
    ui->lblPreview->setScaledContents(true);

    // ---- Sliders/Spins wiring & ranges (0..100 UI range -> 0..1 normalized) ----
    auto setupPair = [](QSlider* s, QSpinBox* sp, int def){
        s->setRange(0, 100);
        sp->setRange(0, 100);
        s->setValue(def);
        sp->setValue(def);
    };

    setupPair(ui->sliderExposure,   ui->spinExposure,   50);
    setupPair(ui->sliderBrightness, ui->spinBrightness, 50);
    setupPair(ui->sliderContrast,   ui->spinContrast,   50);

    // Slider -> Spin handlers
    connect(ui->sliderExposure, &QSlider::valueChanged, this, &CalibrationTab::on_sliderExposure_valueChanged);
    connect(ui->sliderBrightness, &QSlider::valueChanged, this, &CalibrationTab::on_sliderBrightness_valueChanged);
    connect(ui->sliderContrast, &QSlider::valueChanged, this, &CalibrationTab::on_sliderContrast_valueChanged);

    // Spin -> Slider handlers
    connect(ui->spinExposure,   QOverload<int>::of(&QSpinBox::valueChanged), this, &CalibrationTab::on_spinExposure_valueChanged);
    connect(ui->spinBrightness, QOverload<int>::of(&QSpinBox::valueChanged), this, &CalibrationTab::on_spinBrightness_valueChanged);
    connect(ui->spinContrast,   QOverload<int>::of(&QSpinBox::valueChanged), this, &CalibrationTab::on_spinContrast_valueChanged);

    logLine("Calibration tab ready.");
}

CalibrationTab::~CalibrationTab()
{
    delete ui;
}

// ========== Buttons ============

void CalibrationTab::on_btnStartCalibration_clicked()
{
    QStringList paths = QFileDialog::getOpenFileNames(this, "Select Chessboard images", QString(), "Images (*.png *.jpg *.jpeg *.bmp)");
    if(paths.isEmpty()) {
        logLine("No images selected.");
        return;
    }

    // Adjust to your checkerboard:
    const cv::Size boardSize(9, 6); // inner corners (columns x rows)
    const float squareSize = 25.0f; // mm

    double rms = 0.0;
    if (!runCalibration(paths, boardSize, squareSize, rms)) {
        QMessageBox::warning(this, "Calibration", "Calibration failed. Check images/board size.");
        return;
    }

    m_lastRMS  = rms;
    m_hasCalib = true;

    logLine(QString("Calibration done. RMS = %1").arg(rms, 0, 'f', 4));
    if (ui->labelRMS)       ui->labelRMS->setText(QString::number(rms, 'f', 4));
    if (ui->labelImageSize) ui->labelImageSize->setText(QString("%1 x %2").arg(m_imageSize.width).arg(m_imageSize.height));

    cv::Mat preview = cv::imread(paths.back().toStdString());
    showPreview(preview);
}


void CalibrationTab::on_btnLoadCalibration_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Load Calibration (YAML)", QString(), "YAML Files (*.yml *.yaml)");
    if (path.isEmpty()) return;

    cv::FileStorage fs(path.toStdString(), cv::FileStorage::READ);
    if (!fs.isOpened()) { QMessageBox::warning(this, "Load", "Failed to open file."); return; }

    fs["camera_matrix"] >> m_cameraMatrix;
    fs["dist_coeffs"]   >> m_distCoeffs;
    int w=0,h=0;
    fs["image_width"] >> w;
    fs["image_height"] >> h;
    fs["rms"] >> m_lastRMS; fs.release();

    m_imageSize = cv::Size(w,h);
    m_hasCalib = !m_cameraMatrix.empty() && !m_distCoeffs.empty();
    if (!m_hasCalib) { QMessageBox::warning(this, "Load", "Invalid calibration data."); return; }

    if (ui->labelRMS)       ui->labelRMS->setText(QString::number(m_lastRMS, 'f', 4));
    if (ui->labelImageSize) ui->labelImageSize->setText(QString("%1 x %2").arg(w).arg(h));

    logLine("Loaded calibration: " + path);
}


void CalibrationTab::on_btnSaveCalibration_clicked()
{
    if (!m_hasCalib) { QMessageBox::information(this, "Save", "Run or load calibration first."); return; }

    QString path = QFileDialog::getSaveFileName(this, "Save Calibration (YAML)", QString(), "YAML Files (*.yml *.yaml)");
    if (path.isEmpty()) return;

    cv::FileStorage fs(path.toStdString(), cv::FileStorage::WRITE);
    if (!fs.isOpened()) { QMessageBox::warning(this, "Save", "Failed to open file."); return; }

    fs << "camera_matrix" << m_cameraMatrix;
    fs << "dist_coeffs"   << m_distCoeffs;
    fs << "image_width"   << m_imageSize.width;
    fs << "image_height"  << m_imageSize.height;
    fs << "rms"           << m_lastRMS;
    fs.release();
    logLine("Saved calibration: " + path);
}

void CalibrationTab::on_btnTestCalibration_clicked()
{
    if (!m_hasCalib) { QMessageBox::information(this, "Test", "Load or compute calibration first."); return; }

    QString imgPath = QFileDialog::getOpenFileName(this, "Select Image", QString(), "Images (*.png *.jpg *.jpeg *.bmp)");
    if (imgPath.isEmpty()) return;

    cv::Mat input = cv::imread(imgPath.toStdString());
    if (input.empty()) { QMessageBox::warning(this, "Test", "Failed to read image."); return; }

    cv::Mat undist;
    cv::undistort(input, undist, m_cameraMatrix, m_distCoeffs);
    showPreview(undist);
    logLine("Undistorted preview shown.");
}

/* ========== Sliders and SpinBoxes ========== */

static inline double norm01(int v) {
    if (v < 0) v = 0; if (v > 100) v = 100;
    return static_cast<double>(v) / 100.0;
}

void CalibrationTab::on_sliderExposure_valueChanged(int value)
{
    QSignalBlocker block(ui->spinExposure);
    ui->spinExposure->setValue(value);
    // emit exposureNormChanged(norm01(value));
}


void CalibrationTab::on_sliderBrightness_valueChanged(int value)
{
    QSignalBlocker block(ui->spinBrightness);
    ui->spinBrightness->setValue(value);
    // emit brightnessNormChanged(norm01(value));
}


void CalibrationTab::on_sliderContrast_valueChanged(int value)
{
    QSignalBlocker block(ui->spinContrast);
    ui->spinContrast->setValue(value);
    // emit contrastNormChanged(norm01(value));
}

void CalibrationTab::on_spinExposure_valueChanged(int arg1)
{
    QSignalBlocker block(ui->sliderExposure);
    ui->sliderExposure->setValue(arg1);
}


void CalibrationTab::on_spinBrightness_valueChanged(int arg1)
{
    QSignalBlocker block(ui->sliderBrightness);
    ui->sliderBrightness->setValue(arg1);
}


void CalibrationTab::on_spinContrast_valueChanged(int arg1)
{
    QSignalBlocker block(ui->sliderContrast);
    ui->sliderContrast->setValue(arg1);
}

void CalibrationTab::logLine(const QString &s)
{
    if(ui->calibLogTextEdit)
        ui->calibLogTextEdit->append(s);
}

QImage CalibrationTab::matToQImage(const cv::Mat &m, bool alreadyRGB)
{
    if(m.empty()) return {};

    if(m.type() == CV_8UC3) {
        if(alreadyRGB)
            return QImage(m.data, m.cols, m.rows, static_cast<int>(m.step), QImage::Format_RGB888).copy();
     else {
            cv::Mat rgb; cv::cvtColor(m, rgb, cv::COLOR_BGR2RGB);
            return QImage(rgb.data, rgb.cols, rgb.rows, static_cast<int>(rgb.step), QImage::Format_RGB888).copy();
        }
    } else if(m.type() == CV_8UC1) {
        return QImage(m.data, m.cols, m.rows, static_cast<int>(m.step), QImage::Format_Grayscale8).copy();
    } else {
        cv::Mat bgr8; m.convertTo(bgr8, CV_8UC3);
        return matToQImage(bgr8, false);
    }
}

void CalibrationTab::showPreview(const cv::Mat &bgr)
{
    if(bgr.empty()) return;
    ui->lblPreview->setPixmap(QPixmap::fromImage(matToQImage(bgr, false)));
}

bool CalibrationTab::runCalibration(const QStringList &imagePaths,
                                    const cv::Size &boardSize,
                                    float squareSize,
                                    double &outRMS)
{
    if (imagePaths.size() < 5) {
        logLine("Need at least 5 images for a stable calibration.");
        return false;
    }

    std::vector<std::vector<cv::Point2f>> imgPoints; // 2D corners in images
    std::vector<std::vector<cv::Point3f>> objPoints; // 3D points in board space
    cv::Size imageSize;

    // Prepare a single board pattern in 3D (Z=0)
    std::vector<cv::Point3f> objp;
    objp.reserve(boardSize.width * boardSize.height);
    for (int r = 0; r < boardSize.height; ++r)
        for (int c = 0; c < boardSize.width; ++c)
            objp.emplace_back(c * squareSize, r * squareSize, 0.0f);

    int successes = 0;

    for (const QString& p : imagePaths) {
        cv::Mat img = cv::imread(p.toStdString()); // BGR
        if (img.empty()) {
            logLine("Skipped unreadable image: " + p);
            continue;
        }

        if (imageSize.width == 0 && imageSize.height == 0)
            imageSize = img.size();

        std::vector<cv::Point2f> corners;
        bool found = cv::findChessboardCorners(img, boardSize, corners,
                                               cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);

        if (!found) {
            logLine("Chessboard NOT found in: " + p);
            continue;
        }

        // refine corner positions
        cv::Mat gray;
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
        cv::cornerSubPix(gray, corners, cv::Size(11,11), cv::Size(-1,-1),
                         cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.001));

        imgPoints.push_back(corners);
        objPoints.push_back(objp);
        successes++;
        logLine("Chessboard found: " + p);
    }

    if (successes < 5) {
        logLine("Not enough successful detections for calibration.");
        return false;
    }

    m_cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    m_distCoeffs   = cv::Mat::zeros(8, 1, CV_64F);

    std::vector<cv::Mat> rvecs, tvecs;
    double rms = cv::calibrateCamera(objPoints, imgPoints, imageSize,
                                     m_cameraMatrix, m_distCoeffs,
                                     rvecs, tvecs,
                                     cv::CALIB_RATIONAL_MODEL);

    m_imageSize = imageSize;
    outRMS = rms;
    return true;
}

