#include "cameraworker.h"
#include <QThread>
#include <QDebug>

CameraWorker::CameraWorker(int camIndex, int width, int height)
    : m_index(camIndex), m_width(width), m_height(height) {}

CameraWorker::~CameraWorker() {stop();}

void CameraWorker::start()
{
    if (m_running.loadAcquire()) return;
    // Open default backend; you can force V4L2/MSMF/DSHOW later if needed
    if (!m_cap.open(m_index)) {
        emit error("Failed to open camera index " + QString::number(m_index));
        return;
    }
    if (m_width > 0 && m_height > 0) {
        m_cap.set(cv::CAP_PROP_FRAME_WIDTH,  m_width);
        m_cap.set(cv::CAP_PROP_FRAME_HEIGHT, m_height);
    }
    m_running.storeRelease(true);

    cv::Mat frameBGR;
    while (m_running.loadAcquire()) {
        if (!m_cap.read(frameBGR) || frameBGR.empty()) continue;
        // Convert BGR → RGB for Qt, then emit as QImage
        QImage qimg = matToQImage(frameBGR);
        emit frameReady(qimg);
        // ~30 fps pacing
        QThread::msleep(30);
    }
    m_cap.release();
}

void CameraWorker::stop()
{
    m_running.storeRelease(false);
}

static inline double clamp01(double x){ return x < 0 ? 0 : (x > 1 ? 1 : x); }

void CameraWorker::setExposureNorm(double x)
{
    x = clamp01(x);
    if (!m_cap.isOpened()) return;

    // Try to disable auto exposure and set manual value where possible
#if defined(_WIN32)
    // MSMF often expects 0.25 for manual, 0.75 for auto
    m_cap.set(cv::CAP_PROP_AUTO_EXPOSURE, 0.25);
#else
    // On some backends 1=auto, 0=manual (varies!)
    // Many V4L2 drivers use the same 0.25/0.75 convention:
    if (!m_cap.set(cv::CAP_PROP_AUTO_EXPOSURE, 0.25)) {
        // Some drivers use 0 = manual, 1 = auto
        m_cap.set(cv::CAP_PROP_AUTO_EXPOSURE, 0.0);
    }
#endif

    // Map 0..1 -> a plausible exposure range; backends vary wildly.
    // Many webcams accept negative log2 values; try a mid-range mapping:
    // [-10 .. -1] where lower is darker/shorter exposure.
    double expVal = -10.0 + x * 9.0; // -10 (dark) to -1 (bright)
    bool ok = m_cap.set(cv::CAP_PROP_EXPOSURE, expVal);

    if(!ok) ok = m_cap.set(cv::CAP_PROP_EXPOSURE, 1.0 + x * 99.0);

    // 3) If still failing, try [0 .. 1]
    if (!ok) ok = m_cap.set(cv::CAP_PROP_EXPOSURE, x);

}

void CameraWorker::setBrightnessNorm(double x)
{
    x = clamp01(x);
    if (!m_cap.isOpened()) return;
    // Typical range 0..1 or 0..255 depending on backend
    if (!m_cap.set(cv::CAP_PROP_BRIGHTNESS, x)) {
        m_cap.set(cv::CAP_PROP_BRIGHTNESS, x * 255.0);
    }
}

void CameraWorker::setContrastNorm(double x)
{
    x = clamp01(x);
    if (!m_cap.isOpened()) return;
    if (!m_cap.set(cv::CAP_PROP_CONTRAST, x)) {
        m_cap.set(cv::CAP_PROP_CONTRAST, x * 255.0);
    }
}

QImage CameraWorker::matToQImage(const cv::Mat &bgr)
{
    cv::Mat rgb;
    cv::cvtColor(bgr, rgb, cv::COLOR_BGR2RGB);  // BGR→RGB for Qt display
    // Wrap RGB data without extra copy where possible
    return QImage(rgb.data, rgb.cols, rgb.rows, static_cast<int>(rgb.step),
    QImage::Format_RGB888).copy(); // .copy() to own the data
}
