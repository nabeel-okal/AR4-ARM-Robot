#ifndef OBJECTDETECTIONTAB_H
#define OBJECTDETECTIONTAB_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QComboBox>
#include <QSlider>
#include <QPlainTextEdit>
#include <QPushButton>

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

    void on_startDetectionBtn_clicked();
    void on_stopDetectionBtn_clicked();
    void on_confSlider_valueChanged(int value);
    void on_modelComboBox_currentIndexChanged(int index);

    // Getters and Setters
    QLabel *getDetectionPreviewLabel() const;
    QComboBox *getModelComboBox() const;
    QSlider *getConfSlider() const;
    QLabel *getConfValueLabel() const;
    QPlainTextEdit *getDetLogTextEdit() const;
    QPushButton *getStartDetBtn() const;
    QPushButton *getStopDetBtn() const;


    // Variables
    QTimer m_detectionTimer;
    double m_confidence = 0.50;   // 0.0–1.0
    int    m_modelIndex = 0;      // which model (for later)

private:
    Ui::ObjectDetectionTab *ui;

    MainWindow *mainwindow;
};

#endif // OBJECTDETECTIONTAB_H
