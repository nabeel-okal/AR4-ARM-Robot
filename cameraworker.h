#pragma once

#include <QObject>
#include <QImage>
#include <QAtomicInt>
#include <opencv2/opencv.hpp>


class CameraWorker : public QObject
{
    Q_OBJECT
public:
    explicit CameraWorker(int camIndex = 0, int width = 640, int height = 480);
    ~CameraWorker();

public slots:
    void start();       // open camera & begin the loop
    void stop();        // request stop

    void setExposureNorm(double x);   // 0..1
    void setBrightnessNorm(double x); // 0..1
    void setContrastNorm(double x);   // 0..1

signals:
    void frameReady(const QImage &img);
    void error(const QString &msg);

private:
    QImage matToQImage(const cv::Mat &bgr);
    int m_index;
    int m_width, m_height;
    QAtomicInt m_running { false };
    cv::VideoCapture m_cap;
};
