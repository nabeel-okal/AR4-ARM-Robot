/********************************************************************************
** Form generated from reading UI file 'robotcontrol.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOTCONTROL_H
#define UI_ROBOTCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RobotControl
{
public:
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSlider *speedSlider;
    QLabel *speedValueLabel;
    QTextEdit *textRobotLog;
    QCheckBox *chEnableMotors;
    QGroupBox *groupBox;
    QRadioButton *rbModeJoint;
    QRadioButton *rbModePlanar;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_7;
    QPushButton *forwardBtn;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *leftBtn;
    QPushButton *stopBtn;
    QPushButton *rightBtn;
    QPushButton *backwardBtn;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboJoint;
    QLabel *label_3;
    QComboBox *comboAxis;

    void setupUi(QWidget *RobotControl)
    {
        if (RobotControl->objectName().isEmpty())
            RobotControl->setObjectName("RobotControl");
        RobotControl->resize(1040, 727);
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
        RobotControl->setPalette(palette);
        groupBox_4 = new QGroupBox(RobotControl);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(10, 190, 531, 263));
        verticalLayout_6 = new QVBoxLayout(groupBox_4);
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        speedSlider = new QSlider(groupBox_4);
        speedSlider->setObjectName("speedSlider");
        speedSlider->setMaximum(100);
        speedSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(speedSlider);

        speedValueLabel = new QLabel(groupBox_4);
        speedValueLabel->setObjectName("speedValueLabel");

        horizontalLayout->addWidget(speedValueLabel);


        verticalLayout_6->addLayout(horizontalLayout);

        textRobotLog = new QTextEdit(groupBox_4);
        textRobotLog->setObjectName("textRobotLog");

        verticalLayout_6->addWidget(textRobotLog);

        chEnableMotors = new QCheckBox(RobotControl);
        chEnableMotors->setObjectName("chEnableMotors");
        chEnableMotors->setGeometry(QRect(30, 480, 131, 23));
        groupBox = new QGroupBox(RobotControl);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 520, 161, 101));
        rbModeJoint = new QRadioButton(groupBox);
        rbModeJoint->setObjectName("rbModeJoint");
        rbModeJoint->setGeometry(QRect(10, 30, 110, 23));
        rbModePlanar = new QRadioButton(groupBox);
        rbModePlanar->setObjectName("rbModePlanar");
        rbModePlanar->setGeometry(QRect(20, 60, 110, 23));
        widget = new QWidget(RobotControl);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 30, 469, 139));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_7 = new QVBoxLayout(groupBox_3);
        verticalLayout_7->setObjectName("verticalLayout_7");
        forwardBtn = new QPushButton(groupBox_3);
        forwardBtn->setObjectName("forwardBtn");

        verticalLayout_7->addWidget(forwardBtn);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        leftBtn = new QPushButton(groupBox_3);
        leftBtn->setObjectName("leftBtn");

        horizontalLayout_2->addWidget(leftBtn);

        stopBtn = new QPushButton(groupBox_3);
        stopBtn->setObjectName("stopBtn");

        horizontalLayout_2->addWidget(stopBtn);

        rightBtn = new QPushButton(groupBox_3);
        rightBtn->setObjectName("rightBtn");

        horizontalLayout_2->addWidget(rightBtn);


        verticalLayout_7->addLayout(horizontalLayout_2);

        backwardBtn = new QPushButton(groupBox_3);
        backwardBtn->setObjectName("backwardBtn");

        verticalLayout_7->addWidget(backwardBtn);


        horizontalLayout_3->addWidget(groupBox_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(widget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboJoint = new QComboBox(widget);
        comboJoint->setObjectName("comboJoint");

        gridLayout->addWidget(comboJoint, 0, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        comboAxis = new QComboBox(widget);
        comboAxis->setObjectName("comboAxis");

        gridLayout->addWidget(comboAxis, 1, 1, 1, 1);


        horizontalLayout_3->addLayout(gridLayout);


        retranslateUi(RobotControl);

        QMetaObject::connectSlotsByName(RobotControl);
    } // setupUi

    void retranslateUi(QWidget *RobotControl)
    {
        RobotControl->setWindowTitle(QCoreApplication::translate("RobotControl", "Form", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("RobotControl", "Speed Control", nullptr));
        label_2->setText(QCoreApplication::translate("RobotControl", "Speed:", nullptr));
        speedValueLabel->setText(QCoreApplication::translate("RobotControl", "50", nullptr));
        chEnableMotors->setText(QCoreApplication::translate("RobotControl", "Enable Motors", nullptr));
        groupBox->setTitle(QCoreApplication::translate("RobotControl", "Mode Options", nullptr));
        rbModeJoint->setText(QCoreApplication::translate("RobotControl", "Joint Jog", nullptr));
        rbModePlanar->setText(QCoreApplication::translate("RobotControl", "Planar XYZ", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("RobotControl", "Movement Control", nullptr));
        forwardBtn->setText(QCoreApplication::translate("RobotControl", "Forward", nullptr));
        leftBtn->setText(QCoreApplication::translate("RobotControl", "Left", nullptr));
        stopBtn->setText(QCoreApplication::translate("RobotControl", "Stop", nullptr));
        rightBtn->setText(QCoreApplication::translate("RobotControl", "Right", nullptr));
        backwardBtn->setText(QCoreApplication::translate("RobotControl", "Backward", nullptr));
        label->setText(QCoreApplication::translate("RobotControl", "Joint Mode:", nullptr));
        label_3->setText(QCoreApplication::translate("RobotControl", "Planar Mode:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RobotControl: public Ui_RobotControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOTCONTROL_H
