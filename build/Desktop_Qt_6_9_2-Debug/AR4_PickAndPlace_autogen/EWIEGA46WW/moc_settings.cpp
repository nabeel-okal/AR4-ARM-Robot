/****************************************************************************
** Meta object code from reading C++ file 'settings.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../settings.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN8SettingsE_t {};
} // unnamed namespace

template <> constexpr inline auto Settings::qt_create_metaobjectdata<qt_meta_tag_ZN8SettingsE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Settings",
        "requestConnectSerial",
        "",
        "host",
        "port",
        "requestDisconnect",
        "requestPing",
        "cmd",
        "timeoutMs",
        "robotStatusMessage",
        "msg",
        "onRobotConnectedChanged",
        "connected",
        "onRobotError",
        "message",
        "on_btnConnectRobot_clicked",
        "on_btnSave_clicked",
        "on_btnLoad_clicked",
        "on_refreshPortsBtn_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'requestConnectSerial'
        QtMocHelpers::SignalData<void(QString, int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::Int, 4 },
        }}),
        // Signal 'requestDisconnect'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'requestPing'
        QtMocHelpers::SignalData<void(QString, int)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 }, { QMetaType::Int, 8 },
        }}),
        // Signal 'robotStatusMessage'
        QtMocHelpers::SignalData<void(const QString)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 10 },
        }}),
        // Slot 'onRobotConnectedChanged'
        QtMocHelpers::SlotData<void(bool)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 12 },
        }}),
        // Slot 'onRobotError'
        QtMocHelpers::SlotData<void(QString)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 14 },
        }}),
        // Slot 'on_btnConnectRobot_clicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnSave_clicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnLoad_clicked'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_refreshPortsBtn_clicked'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Settings, qt_meta_tag_ZN8SettingsE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Settings::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8SettingsE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8SettingsE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8SettingsE_t>.metaTypes,
    nullptr
} };

void Settings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Settings *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->requestConnectSerial((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->requestDisconnect(); break;
        case 2: _t->requestPing((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 3: _t->robotStatusMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->onRobotConnectedChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->onRobotError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->on_btnConnectRobot_clicked(); break;
        case 7: _t->on_btnSave_clicked(); break;
        case 8: _t->on_btnLoad_clicked(); break;
        case 9: _t->on_refreshPortsBtn_clicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Settings::*)(QString , int )>(_a, &Settings::requestConnectSerial, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::requestDisconnect, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)(QString , int )>(_a, &Settings::requestPing, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)(const QString )>(_a, &Settings::robotStatusMessage, 3))
            return;
    }
}

const QMetaObject *Settings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Settings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8SettingsE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Settings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Settings::requestConnectSerial(QString _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void Settings::requestDisconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Settings::requestPing(QString _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}

// SIGNAL 3
void Settings::robotStatusMessage(const QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}
QT_WARNING_POP
