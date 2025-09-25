/********************************************************************************
** Form generated from reading UI file 'objectdetectiontab.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTDETECTIONTAB_H
#define UI_OBJECTDETECTIONTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectDetectionTab
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QPushButton *startDetectionBtn;
    QPushButton *stopDetectionBtn;
    QLabel *modelLabel;
    QComboBox *modelComboBox;
    QLabel *confLabel;
    QSlider *confSlider;
    QLabel *confValueLabel;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_6;
    QLabel *detectionPreviewLabel;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_7;
    QPlainTextEdit *detLogTextEdit;

    void setupUi(QWidget *ObjectDetectionTab)
    {
        if (ObjectDetectionTab->objectName().isEmpty())
            ObjectDetectionTab->setObjectName("ObjectDetectionTab");
        ObjectDetectionTab->resize(1067, 783);
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
        ObjectDetectionTab->setPalette(palette);
        verticalLayout = new QVBoxLayout(ObjectDetectionTab);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        startDetectionBtn = new QPushButton(ObjectDetectionTab);
        startDetectionBtn->setObjectName("startDetectionBtn");

        gridLayout_2->addWidget(startDetectionBtn, 0, 0, 1, 1);

        stopDetectionBtn = new QPushButton(ObjectDetectionTab);
        stopDetectionBtn->setObjectName("stopDetectionBtn");

        gridLayout_2->addWidget(stopDetectionBtn, 0, 1, 1, 1);

        modelLabel = new QLabel(ObjectDetectionTab);
        modelLabel->setObjectName("modelLabel");
        modelLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(modelLabel, 1, 0, 1, 1);

        modelComboBox = new QComboBox(ObjectDetectionTab);
        modelComboBox->setObjectName("modelComboBox");

        gridLayout_2->addWidget(modelComboBox, 1, 1, 1, 1);

        confLabel = new QLabel(ObjectDetectionTab);
        confLabel->setObjectName("confLabel");
        confLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(confLabel, 2, 0, 1, 1);

        confSlider = new QSlider(ObjectDetectionTab);
        confSlider->setObjectName("confSlider");
        confSlider->setMaximum(100);
        confSlider->setPageStep(5);
        confSlider->setValue(50);
        confSlider->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_2->addWidget(confSlider, 2, 1, 1, 1);

        confValueLabel = new QLabel(ObjectDetectionTab);
        confValueLabel->setObjectName("confValueLabel");
        confValueLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(confValueLabel, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        groupBox_3 = new QGroupBox(ObjectDetectionTab);
        groupBox_3->setObjectName("groupBox_3");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(320, 240));
        verticalLayout_6 = new QVBoxLayout(groupBox_3);
        verticalLayout_6->setObjectName("verticalLayout_6");
        detectionPreviewLabel = new QLabel(groupBox_3);
        detectionPreviewLabel->setObjectName("detectionPreviewLabel");
        sizePolicy.setHeightForWidth(detectionPreviewLabel->sizePolicy().hasHeightForWidth());
        detectionPreviewLabel->setSizePolicy(sizePolicy);
        detectionPreviewLabel->setMinimumSize(QSize(320, 240));

        verticalLayout_6->addWidget(detectionPreviewLabel);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(ObjectDetectionTab);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setMinimumSize(QSize(0, 150));
        verticalLayout_7 = new QVBoxLayout(groupBox_4);
        verticalLayout_7->setObjectName("verticalLayout_7");
        detLogTextEdit = new QPlainTextEdit(groupBox_4);
        detLogTextEdit->setObjectName("detLogTextEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(detLogTextEdit->sizePolicy().hasHeightForWidth());
        detLogTextEdit->setSizePolicy(sizePolicy1);
        detLogTextEdit->setReadOnly(true);

        verticalLayout_7->addWidget(detLogTextEdit);


        verticalLayout->addWidget(groupBox_4);


        retranslateUi(ObjectDetectionTab);

        QMetaObject::connectSlotsByName(ObjectDetectionTab);
    } // setupUi

    void retranslateUi(QWidget *ObjectDetectionTab)
    {
        ObjectDetectionTab->setWindowTitle(QCoreApplication::translate("ObjectDetectionTab", "Form", nullptr));
        startDetectionBtn->setText(QCoreApplication::translate("ObjectDetectionTab", "Start", nullptr));
        stopDetectionBtn->setText(QCoreApplication::translate("ObjectDetectionTab", "Stop", nullptr));
        modelLabel->setText(QCoreApplication::translate("ObjectDetectionTab", "Model:", nullptr));
        confLabel->setText(QCoreApplication::translate("ObjectDetectionTab", "Conf:", nullptr));
        confValueLabel->setText(QCoreApplication::translate("ObjectDetectionTab", "0.50", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("ObjectDetectionTab", "Preview", nullptr));
        detectionPreviewLabel->setText(QCoreApplication::translate("ObjectDetectionTab", "TextLabel", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("ObjectDetectionTab", "Log", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ObjectDetectionTab: public Ui_ObjectDetectionTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTDETECTIONTAB_H
