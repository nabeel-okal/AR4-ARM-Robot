/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineRobotIP;
    QLabel *label_2;
    QSpinBox *spinRobotPort;
    QPushButton *btnConnectRobot;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QSpinBox *spinCameraIndex;
    QLabel *label_4;
    QComboBox *comboResolution;
    QCheckBox *chkAutoConnect;
    QCheckBox *chkDarkMode;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnSave;
    QPushButton *btnLoad;

    void setupUi(QWidget *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName("Settings");
        Settings->resize(676, 397);
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
        Settings->setPalette(palette);
        verticalLayout_3 = new QVBoxLayout(Settings);
        verticalLayout_3->setObjectName("verticalLayout_3");
        groupBox = new QGroupBox(Settings);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineRobotIP = new QLineEdit(groupBox);
        lineRobotIP->setObjectName("lineRobotIP");

        gridLayout->addWidget(lineRobotIP, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        spinRobotPort = new QSpinBox(groupBox);
        spinRobotPort->setObjectName("spinRobotPort");
        spinRobotPort->setMaximum(10000);
        spinRobotPort->setValue(5000);

        gridLayout->addWidget(spinRobotPort, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        btnConnectRobot = new QPushButton(groupBox);
        btnConnectRobot->setObjectName("btnConnectRobot");

        verticalLayout->addWidget(btnConnectRobot);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Settings);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        spinCameraIndex = new QSpinBox(groupBox_2);
        spinCameraIndex->setObjectName("spinCameraIndex");

        gridLayout_2->addWidget(spinCameraIndex, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignHCenter);

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        comboResolution = new QComboBox(groupBox_2);
        comboResolution->setObjectName("comboResolution");

        gridLayout_2->addWidget(comboResolution, 1, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        verticalLayout_3->addWidget(groupBox_2);

        chkAutoConnect = new QCheckBox(Settings);
        chkAutoConnect->setObjectName("chkAutoConnect");

        verticalLayout_3->addWidget(chkAutoConnect);

        chkDarkMode = new QCheckBox(Settings);
        chkDarkMode->setObjectName("chkDarkMode");

        verticalLayout_3->addWidget(chkDarkMode);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnSave = new QPushButton(Settings);
        btnSave->setObjectName("btnSave");

        horizontalLayout->addWidget(btnSave);

        btnLoad = new QPushButton(Settings);
        btnLoad->setObjectName("btnLoad");

        horizontalLayout->addWidget(btnLoad);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(Settings);

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QWidget *Settings)
    {
        Settings->setWindowTitle(QCoreApplication::translate("Settings", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Settings", "Robot Connection", nullptr));
        label->setText(QCoreApplication::translate("Settings", "Robot IP:", nullptr));
        lineRobotIP->setText(QString());
        label_2->setText(QCoreApplication::translate("Settings", "Port:", nullptr));
        btnConnectRobot->setText(QCoreApplication::translate("Settings", "Connect", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Settings", "Camera Settings", nullptr));
        label_3->setText(QCoreApplication::translate("Settings", "Camera Index:", nullptr));
        label_4->setText(QCoreApplication::translate("Settings", "Resolution:", nullptr));
        chkAutoConnect->setText(QCoreApplication::translate("Settings", "Connect to Robot on Startup", nullptr));
        chkDarkMode->setText(QCoreApplication::translate("Settings", "Enable Dark Mode", nullptr));
        btnSave->setText(QCoreApplication::translate("Settings", "Save", nullptr));
        btnLoad->setText(QCoreApplication::translate("Settings", "Load", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
