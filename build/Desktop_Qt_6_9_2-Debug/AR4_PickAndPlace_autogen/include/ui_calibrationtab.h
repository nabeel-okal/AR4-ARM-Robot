/********************************************************************************
** Form generated from reading UI file 'calibrationtab.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATIONTAB_H
#define UI_CALIBRATIONTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalibrationTab
{
public:
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupCameraCalibration;
    QVBoxLayout *verticalLayout_8;
    QPushButton *btnStartCalibration;
    QPushButton *btnLoadCalibration;
    QPushButton *btnSaveCalibration;
    QGroupBox *groupParameters;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_9;
    QSlider *sliderExposure;
    QSlider *sliderBrightness;
    QSlider *sliderContrast;
    QVBoxLayout *verticalLayout_11;
    QSpinBox *spinExposure;
    QSpinBox *spinBrightness;
    QSpinBox *spinContrast;
    QGroupBox *groupTestPreview;
    QVBoxLayout *verticalLayout_10;
    QPushButton *btnTestCalibration;
    QLabel *lblPreview;
    QTextEdit *calibLogTextEdit;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelRMS;
    QLabel *labelImageSize;

    void setupUi(QWidget *CalibrationTab)
    {
        if (CalibrationTab->objectName().isEmpty())
            CalibrationTab->setObjectName("CalibrationTab");
        CalibrationTab->resize(897, 705);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        QBrush brush1(QColor(246, 245, 244, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Light, brush2);
        QBrush brush3(QColor(250, 250, 249, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush3);
        QBrush brush4(QColor(123, 122, 122, 255));
        brush4.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Dark, brush4);
        QBrush brush5(QColor(164, 163, 163, 255));
        brush5.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Mid, brush5);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::BrightText, brush2);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Shadow, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::AlternateBase, brush3);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipBase, brush6);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipText, brush);
        QBrush brush7(QColor(0, 0, 0, 127));
        brush7.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush7);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Accent, brush2);
#endif
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Light, brush2);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush3);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Dark, brush4);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Mid, brush5);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::BrightText, brush2);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Shadow, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::AlternateBase, brush3);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipBase, brush6);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush7);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Accent, brush2);
#endif
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Light, brush2);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush3);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Dark, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Mid, brush5);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::BrightText, brush2);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Shadow, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::AlternateBase, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipBase, brush6);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipText, brush);
        QBrush brush8(QColor(123, 122, 122, 127));
        brush8.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush8);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Accent, brush2);
#endif
        CalibrationTab->setPalette(palette);
        verticalLayout_2 = new QVBoxLayout(CalibrationTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        splitter = new QSplitter(CalibrationTab);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        widget = new QWidget(splitter);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        groupCameraCalibration = new QGroupBox(widget);
        groupCameraCalibration->setObjectName("groupCameraCalibration");
        verticalLayout_8 = new QVBoxLayout(groupCameraCalibration);
        verticalLayout_8->setObjectName("verticalLayout_8");
        btnStartCalibration = new QPushButton(groupCameraCalibration);
        btnStartCalibration->setObjectName("btnStartCalibration");

        verticalLayout_8->addWidget(btnStartCalibration);

        btnLoadCalibration = new QPushButton(groupCameraCalibration);
        btnLoadCalibration->setObjectName("btnLoadCalibration");

        verticalLayout_8->addWidget(btnLoadCalibration);

        btnSaveCalibration = new QPushButton(groupCameraCalibration);
        btnSaveCalibration->setObjectName("btnSaveCalibration");

        verticalLayout_8->addWidget(btnSaveCalibration);


        horizontalLayout->addWidget(groupCameraCalibration);

        groupParameters = new QGroupBox(widget);
        groupParameters->setObjectName("groupParameters");
        horizontalLayout_3 = new QHBoxLayout(groupParameters);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        sliderExposure = new QSlider(groupParameters);
        sliderExposure->setObjectName("sliderExposure");
        sliderExposure->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout_9->addWidget(sliderExposure);

        sliderBrightness = new QSlider(groupParameters);
        sliderBrightness->setObjectName("sliderBrightness");
        sliderBrightness->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout_9->addWidget(sliderBrightness);

        sliderContrast = new QSlider(groupParameters);
        sliderContrast->setObjectName("sliderContrast");
        sliderContrast->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout_9->addWidget(sliderContrast);


        horizontalLayout_3->addLayout(verticalLayout_9);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName("verticalLayout_11");
        spinExposure = new QSpinBox(groupParameters);
        spinExposure->setObjectName("spinExposure");

        verticalLayout_11->addWidget(spinExposure);

        spinBrightness = new QSpinBox(groupParameters);
        spinBrightness->setObjectName("spinBrightness");

        verticalLayout_11->addWidget(spinBrightness);

        spinContrast = new QSpinBox(groupParameters);
        spinContrast->setObjectName("spinContrast");

        verticalLayout_11->addWidget(spinContrast);


        horizontalLayout_3->addLayout(verticalLayout_11);


        horizontalLayout->addWidget(groupParameters);


        verticalLayout->addLayout(horizontalLayout);

        groupTestPreview = new QGroupBox(widget);
        groupTestPreview->setObjectName("groupTestPreview");
        verticalLayout_10 = new QVBoxLayout(groupTestPreview);
        verticalLayout_10->setObjectName("verticalLayout_10");
        btnTestCalibration = new QPushButton(groupTestPreview);
        btnTestCalibration->setObjectName("btnTestCalibration");

        verticalLayout_10->addWidget(btnTestCalibration);

        lblPreview = new QLabel(groupTestPreview);
        lblPreview->setObjectName("lblPreview");
        lblPreview->setMinimumSize(QSize(0, 0));

        verticalLayout_10->addWidget(lblPreview);


        verticalLayout->addWidget(groupTestPreview);

        calibLogTextEdit = new QTextEdit(widget);
        calibLogTextEdit->setObjectName("calibLogTextEdit");
        calibLogTextEdit->setReadOnly(true);

        verticalLayout->addWidget(calibLogTextEdit);

        splitter->addWidget(widget);
        widget_2 = new QWidget(splitter);
        widget_2->setObjectName("widget_2");
        verticalLayout_3 = new QVBoxLayout(widget_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        labelRMS = new QLabel(widget_2);
        labelRMS->setObjectName("labelRMS");

        verticalLayout_3->addWidget(labelRMS);

        labelImageSize = new QLabel(widget_2);
        labelImageSize->setObjectName("labelImageSize");

        verticalLayout_3->addWidget(labelImageSize);

        splitter->addWidget(widget_2);

        verticalLayout_2->addWidget(splitter);


        retranslateUi(CalibrationTab);

        QMetaObject::connectSlotsByName(CalibrationTab);
    } // setupUi

    void retranslateUi(QWidget *CalibrationTab)
    {
        CalibrationTab->setWindowTitle(QCoreApplication::translate("CalibrationTab", "Form", nullptr));
        groupCameraCalibration->setTitle(QCoreApplication::translate("CalibrationTab", "Camera Calibration", nullptr));
        btnStartCalibration->setText(QCoreApplication::translate("CalibrationTab", "Start", nullptr));
        btnLoadCalibration->setText(QCoreApplication::translate("CalibrationTab", "Load", nullptr));
        btnSaveCalibration->setText(QCoreApplication::translate("CalibrationTab", "Save", nullptr));
        groupParameters->setTitle(QCoreApplication::translate("CalibrationTab", "Parameters", nullptr));
        groupTestPreview->setTitle(QCoreApplication::translate("CalibrationTab", "Test & Preview", nullptr));
        btnTestCalibration->setText(QCoreApplication::translate("CalibrationTab", "Test", nullptr));
        lblPreview->setText(QCoreApplication::translate("CalibrationTab", "TextLabel", nullptr));
        labelRMS->setText(QCoreApplication::translate("CalibrationTab", "TextLabel", nullptr));
        labelImageSize->setText(QCoreApplication::translate("CalibrationTab", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CalibrationTab: public Ui_CalibrationTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONTAB_H
