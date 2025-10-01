#pragma once

#include <QWidget>
#include <QMetaObject>
#include <QImage>

#include "cameraworker.h"

class MainWindow;
class QLabel;
class QPlainTextEdit;
class QComboBox;
class QSlider;
class QPushButton;

namespace Ui {
class ObjectDetectionTab;
}

class ObjectDetectionTab : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectDetectionTab(QWidget *parent, MainWindow *mw);
    ~ObjectDetectionTab();

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
    double m_confidence = 0.50;   // 0.0–1.0
    int    m_modelIndex = 0;      // which model (for later)

public slots:
    void onFrameReady(const QImage& frame);

    void onCameraFrame(const QImage& frame);
    void onModelChanged(int index);
    void onConfidenceChanged(int v);


private:
    Ui::ObjectDetectionTab *ui;
    MainWindow *mainwindow;

    enum class Model { Dummy = 0, Yolo = 1, Color = 2 };

    QImage runDummy(const QImage& in) const;
    QImage runYoloStub(const QImage& in) const;
    QImage runColorHSV(const QImage& in) const;


    // Manage connect/disconnect to camera frames
    QMetaObject::Connection m_frameConn {};

    // Rendering helpers
    QImage drawHUD(QImage& img, const QString& modelName, double conf) const;
    QImage processColorModel(const QImage& in) const;

    // Small utilities
    void showPixmap(const QImage& img) const;
    void logLine(const QString& s) const;

    MainWindow* m_mainWindow = nullptr;
    Model m_model = Model::Dummy;
};
