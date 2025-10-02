#include "calibrationtab.h"
#include "ui_calibrationtab.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QLabel>
#include <QSignalBlocker>
#include <QDateTime>
#include <algorithm>

// ---------- ctor/dtor ----------

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
    connect(ui->sliderExposure,   &QSlider::valueChanged, this, &CalibrationTab::on_sliderExposure_valueChanged);
    connect(ui->sliderBrightness, &QSlider::valueChanged, this, &CalibrationTab::on_sliderBrightness_valueChanged);
    connect(ui->sliderContrast,   &QSlider::valueChanged, this, &CalibrationTab::on_sliderContrast_valueChanged);

    // Spin -> Slider handlers
    connect(ui->spinExposure,   QOverload<int>::of(&QSpinBox::valueChanged), this, &CalibrationTab::on_spinExposure_valueChanged);
    connect(ui->spinBrightness, QOverload<int>::of(&QSpinBox::valueChanged), this, &CalibrationTab::on_spinBrightness_valueChanged);
    connect(ui->spinContrast,   QOverload<int>::of(&QSpinBox::valueChanged), this, &CalibrationTab::on_spinContrast_valueChanged);

    // UI labels defaults
    if (ui->labelRMS)       ui->labelRMS->setText("RMS: —");
    if (ui->labelImageSize) ui->labelImageSize->setText("Image: —");

    logLine("Calibration tab ready.");
}

CalibrationTab::~CalibrationTab()
{
    delete ui;
}

// ---------- Buttons ----------

void CalibrationTab::on_btnStartCalibration_clicked()
{
    // Multi-select images; users can select from mixed folders
    const QString filter = "Images (*.png *.jpg *.jpeg *.bmp *.tiff *.tif)";
    QStringList paths = QFileDialog::getOpenFileNames(this, "Select chessboard images", QString(), filter);
    if (paths.isEmpty()) {
        logLine("No images selected.");
        return;
    }

    // Adjust to your checkerboard (inner corners):
    const cv::Size boardSize(9, 6); // columns x rows of INNER corners
    const float squareSize = 25.0f; // millimeters (or any consistent unit)

    double rms = 0.0;
    if (!runCalibration(paths, boardSize, squareSize, rms)) {
        QMessageBox::warning(this, "Calibration", "Calibration failed. Check images/board size.");
        return;
    }

    m_lastRMS  = rms;
    m_hasCalib = true;

    logLine(QString("Calibration done. RMS = %1").arg(rms, 0, 'f', 4));
    if (ui->labelRMS)       ui->labelRMS->setText(QString("RMS: %1").arg(rms, 0, 'f', 4));
    if (ui->labelImageSize) ui->labelImageSize->setText(QString("Image: %1 x %2").arg(m_imageSize.width).arg(m_imageSize.height));

    // Show last image undistorted for visual sanity-check
    cv::Mat input = cv::imread(paths.back().toStdString());
    if (!input.empty()) {
        cv::Mat undist;
        cv::undistort(input, undist, m_cameraMatrix, m_distCoeffs);
        showPreview(undist);
    }
}

void CalibrationTab::on_btnLoadCalibration_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Load Calibration (YAML)", QString(), "YAML Files (*.yml *.yaml)");
    if (path.isEmpty()) return;

    cv::FileStorage fs(path.toStdString(), cv::FileStorage::READ);
    if (!fs.isOpened()) { QMessageBox::warning(this, "Load", "Failed to open file."); return; }

    fs["camera_matrix"] >> m_cameraMatrix;
    fs["dist_coeffs"]   >> m_distCoeffs;
    int w=0,h=0; fs["image_width"] >> w; fs["image_height"] >> h;
    fs["rms"] >> m_lastRMS;
    fs.release();

    m_imageSize = cv::Size(w,h);
    m_hasCalib = !m_cameraMatrix.empty() && !m_distCoeffs.empty();

    if (!m_hasCalib) { QMessageBox::warning(this, "Load", "Invalid calibration data."); return; }

    if (ui->labelRMS)       ui->labelRMS->setText(QString("RMS: %1").arg(m_lastRMS, 'f', 4));
    if (ui->labelImageSize) ui->labelImageSize->setText(QString("Image: %1 x %2").arg(w).arg(h));

    logLine("Loaded calibration: " + path);
}

void CalibrationTab::on_btnSaveCalibration_clicked()
{
    if (!m_hasCalib) { QMessageBox::information(this, "Save", "Run or load calibration first."); return; }

    QString path = QFileDialog::getSaveFileName(this, "Save Calibration (YAML)", QString(),
                                                "YAML Files (*.yml *.yaml)");
    if (path.isEmpty()) return;

    cv::FileStorage fs(path.toStdString(), cv::FileStorage::WRITE);
    if (!fs.isOpened()) { QMessageBox::warning(this, "Save", "Failed to open file."); return; }

    const auto now = QDateTime::currentDateTime().toString(Qt::ISODate);

    fs << "camera_matrix" << m_cameraMatrix;
    fs << "dist_coeffs"   << m_distCoeffs;
    fs << "image_width"   << m_imageSize.width;
    fs << "image_height"  << m_imageSize.height;
    fs << "rms"           << m_lastRMS;
    fs << "timestamp"     << now.toStdString();
    fs.release();

    logLine("Saved calibration: " + path);
}

void CalibrationTab::on_btnTestCalibration_clicked()
{
    if (!m_hasCalib) { QMessageBox::information(this, "Test", "Load or compute calibration first."); return; }

    QString imgPath = QFileDialog::getOpenFileName(this, "Select Image", QString(),
                                                   "Images (*.png *.jpg *.jpeg *.bmp *.tif *.tiff)");
    if (imgPath.isEmpty()) return;

    cv::Mat input = cv::imread(imgPath.toStdString());
    if (input.empty()) { QMessageBox::warning(this, "Test", "Failed to read image."); return; }

    cv::Mat undist;
    // Alpha=0 => crop black borders, Alpha=1 keeps all; choose 0.0 for tighter view
    cv::undistort(input, undist, m_cameraMatrix, m_distCoeffs);
    showPreview(undist);
    logLine("Undistorted preview shown: " + imgPath);
}

// ---------- Sliders & Spinners ----------

void CalibrationTab::on_sliderExposure_valueChanged(int value)
{
    QSignalBlocker block(ui->spinExposure);
    ui->spinExposure->setValue(value);
    emit exposureNormChanged(norm01(value));
}

void CalibrationTab::on_sliderBrightness_valueChanged(int value)
{
    QSignalBlocker block(ui->spinBrightness);
    ui->spinBrightness->setValue(value);
    emit brightnessNormChanged(norm01(value));
}

void CalibrationTab::on_sliderContrast_valueChanged(int value)
{
    QSignalBlocker block(ui->spinContrast);
    ui->spinContrast->setValue(value);
    emit contrastNormChanged(norm01(value));
}

void CalibrationTab::on_spinExposure_valueChanged(int arg1)
{
    QSignalBlocker block(ui->sliderExposure);
    ui->sliderExposure->setValue(arg1);
    emit exposureNormChanged(norm01(arg1));
}

void CalibrationTab::on_spinBrightness_valueChanged(int arg1)
{
    QSignalBlocker block(ui->sliderBrightness);
    ui->sliderBrightness->setValue(arg1);
    emit brightnessNormChanged(norm01(arg1));
}

void CalibrationTab::on_spinContrast_valueChanged(int arg1)
{
    QSignalBlocker block(ui->sliderContrast);
    ui->sliderContrast->setValue(arg1);
    emit contrastNormChanged(norm01(arg1));
}

// ---------- Utilities ----------

void CalibrationTab::logLine(const QString &s)
{
    if (ui->calibLogTextEdit)
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
    const QPixmap pix = QPixmap::fromImage(matToQImage(bgr, false))
                            .scaled(ui->lblPreview->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);
    ui->lblPreview->setPixmap(pix);
}

// ---------- Core calibration ----------

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
    int idx = 0;

    for (const QString& p : imagePaths) {
        ++idx;
        cv::Mat img = cv::imread(p.toStdString()); // BGR
        if (img.empty()) {
            logLine(QString("[%1] Skipped unreadable image: %2").arg(idx).arg(p));
            continue;
        }

        if (imageSize.width == 0 && imageSize.height == 0) {
            imageSize = img.size();
        } else if (img.size() != imageSize) {
            logLine(QString("[%1] Skipped image with different size: %2").arg(idx).arg(p));
            continue;
        }

        std::vector<cv::Point2f> corners;
        bool found = false;

        // Prefer the more robust SB detector when available
#if (CV_VERSION_MAJOR >= 4)
        try {
            found = cv::findChessboardCornersSB(img, boardSize, corners,
                                                cv::CALIB_CB_EXHAUSTIVE | cv::CALIB_CB_ACCURACY);
        } catch (...) {
            found = false;
        }
#endif
        if (!found) {
            found = cv::findChessboardCorners(img, boardSize, corners,
                                              cv::CALIB_CB_ADAPTIVE_THRESH |
                                                  cv::CALIB_CB_NORMALIZE_IMAGE);
        }

        if (!found) {
            logLine(QString("[%1] Chessboard NOT found: %2").arg(idx).arg(p));
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
        logLine(QString("[%1] Chessboard found: %2").arg(idx).arg(p));
    }

    if (successes < 5) {
        logLine("Not enough successful detections for calibration.");
        return false;
    }

    // Initialize intrinsics
    m_cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    m_distCoeffs   = cv::Mat::zeros(8, 1, CV_64F);

    std::vector<cv::Mat> rvecs, tvecs;

    // Flags: include rational model for better accuracy; zero tangential optional
    int flags = 0;
    flags |= cv::CALIB_RATIONAL_MODEL;
    // flags |= cv::CALIB_ZERO_TANGENT_DIST;

    double rms = cv::calibrateCamera(objPoints, imgPoints, imageSize,
                                     m_cameraMatrix, m_distCoeffs,
                                     rvecs, tvecs, flags);

    m_imageSize = imageSize;
    outRMS = rms;

    // Detailed reprojection errors
    std::vector<double> perViewErrors;
    const double meanErr = computeReprojErrors(objPoints, imgPoints, rvecs, tvecs,
                                               m_cameraMatrix, m_distCoeffs, perViewErrors);

    logLine(QString("Reprojection mean error: %1").arg(meanErr, 0, 'f', 5));
    for (size_t i = 0; i < perViewErrors.size(); ++i) {
        logLine(QString("  View %1 error: %2").arg(i+1).arg(perViewErrors[i], 0, 'f', 5));
    }

    return true;
}

double CalibrationTab::computeReprojErrors(const std::vector<std::vector<cv::Point3f>>& objectPoints,
                                           const std::vector<std::vector<cv::Point2f>>& imagePoints,
                                           const std::vector<cv::Mat>& rvecs,
                                           const std::vector<cv::Mat>& tvecs,
                                           const cv::Mat& cameraMatrix,
                                           const cv::Mat& distCoeffs,
                                           std::vector<double>& perViewErrors)
{
    double totalErr = 0;
    size_t totalPoints = 0;
    perViewErrors.resize(objectPoints.size());

    for (size_t i = 0; i < objectPoints.size(); ++i) {
        std::vector<cv::Point2f> imagePoints2;
        cv::projectPoints(objectPoints[i], rvecs[i], tvecs[i],
                          cameraMatrix, distCoeffs, imagePoints2);

        double err = cv::norm(cv::Mat(imagePoints[i]), cv::Mat(imagePoints2), cv::NORM_L2);
        size_t n = objectPoints[i].size();
        perViewErrors[i] = std::sqrt(err*err / n);
        totalErr        += err*err;
        totalPoints     += n;
    }

    return std::sqrt(totalErr / totalPoints);
}
