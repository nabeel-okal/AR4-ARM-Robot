#ifndef OBJECTDETECTIONTAB_H
#define OBJECTDETECTIONTAB_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QComboBox>
#include <QSlider>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QMetaObject>
#include <QImage>

#include "cameraworker.h"

class MainWindow;

namespace Ui {
class ObjectDetectionTab;
}

class ObjectDetectionTab : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectDetectionTab(QWidget *parent, MainWindow *mainWindow);
    ~ObjectDetectionTab();

    // UI handlers
    void on_startDetectionBtn_clicked();
    void on_stopDetectionBtn_clicked();
    void on_confSlider_valueChanged(int value);
    void on_modelComboBox_currentIndexChanged(int index);

    // Getters
    QLabel         *getDetectionPreviewLabel() const;
    QComboBox      *getModelComboBox() const;
    QSlider        *getConfSlider() const;
    QLabel         *getConfValueLabel() const;
    QPlainTextEdit *getDetLogTextEdit() const;
    QPushButton    *getStartDetBtn() const;
    QPushButton    *getStopDetBtn() const;

    // Variables
    QTimer m_detectionTimer;       // Unused now: we're frame-driven
    double m_confidence = 0.50;    // 0.0–1.0
    int    m_modelIndex = 0;       // 0=Dummy, 1=YOLO(stub), 2=Color(HSV)

public slots:
    void onFrameReady(const QImage& frame);

private:
    Ui::ObjectDetectionTab *ui;
    MainWindow *m_mainWindow;

    // Manage connect/disconnect to camera frames
    QMetaObject::Connection m_frameConn {};

    // Rendering helpers
    QImage drawHUD(QImage img, const QString& modelName) const;

    // Model processors
    QImage runDummy(const QImage& in) const;
    QImage runYoloStub(const QImage& in) const;
    QImage runColorHSV(const QImage& in) const;

    // Small utilities
    void showPixmap(const QImage& img) const;
    void logLine(const QString& s) const;
};

#endif // OBJECTDETECTIONTAB_H
