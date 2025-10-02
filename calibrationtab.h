#pragma once
#include <QWidget>
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
class QLabel;
class QPlainTextEdit;
class QSlider;
class QSpinBox;
class QPushButton;
QT_END_NAMESPACE

namespace Ui { class CalibrationTab; }

class CalibrationTab : public QWidget
{
    Q_OBJECT

public:
    explicit CalibrationTab(QWidget *parent = nullptr);
    ~CalibrationTab();

signals:
    // 0..1 normalized values for camera tuning (UI-agnostic)
    void exposureNormChanged(double x);
    void brightnessNormChanged(double x);
    void contrastNormChanged(double x);

private slots:
    // Buttons
    void on_btnStartCalibration_clicked();
    void on_btnLoadCalibration_clicked();
    void on_btnSaveCalibration_clicked();
    void on_btnTestCalibration_clicked();

    // Sliders/Spins
    void on_sliderExposure_valueChanged(int value);
    void on_sliderBrightness_valueChanged(int value);
    void on_sliderContrast_valueChanged(int value);

    void on_spinExposure_valueChanged(int arg1);
    void on_spinBrightness_valueChanged(int arg1);
    void on_spinContrast_valueChanged(int arg1);

private:
    // helpers
    void logLine(const QString& s);
    static QImage matToQImage(const cv::Mat& m, bool alreadyRGB = false);
    void showPreview(const cv::Mat& bgr);
    bool runCalibration(const QStringList& imagePaths,
                        const cv::Size& boardSize, float squareSize,
                        double& outRMS);

    // compute and log detailed reprojection error
    double computeReprojErrors(const std::vector<std::vector<cv::Point3f>>& objectPoints,
                               const std::vector<std::vector<cv::Point2f>>& imagePoints,
                               const std::vector<cv::Mat>& rvecs,
                               const std::vector<cv::Mat>& tvecs,
                               const cv::Mat& cameraMatrix,
                               const cv::Mat& distCoeffs,
                               std::vector<double>& perViewErrors);

    // map 0..100 UI to 0..1
    static inline double norm01(int v) { if (v < 0) v = 0; if (v > 100) v = 100; return v / 100.0; }

private:
    Ui::CalibrationTab *ui;

    // calibration results in memory
    bool     m_hasCalib = false;
    cv::Mat  m_cameraMatrix;
    cv::Mat  m_distCoeffs;
    cv::Size m_imageSize;
    double   m_lastRMS = 0.0;
};
