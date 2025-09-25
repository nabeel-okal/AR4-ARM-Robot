/****************************************************************************
** Meta object code from reading C++ file 'robotcontrol.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../robotcontrol.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'robotcontrol.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12RobotControlE_t {};
} // unnamed namespace

template <> constexpr inline auto RobotControl::qt_create_metaobjectdata<qt_meta_tag_ZN12RobotControlE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "RobotControl",
        "driveRequested",
        "",
        "Direction",
        "dir",
        "speedPercent",
        "stopRequested",
        "speedChanged",
        "motorsEnabledChanged",
        "on",
        "modeChanged",
        "RobotControl::Mode",
        "m",
        "on_forwardBtn_pressed",
        "on_forwardBtn_released",
        "on_backwardBtn_pressed",
        "on_backwardBtn_released",
        "on_rightBtn_pressed",
        "on_rightBtn_released",
        "on_leftBtn_pressed",
        "on_leftBtn_released",
        "on_stopBtn_clicked",
        "on_speedSlider_valueChanged",
        "value",
        "on_chEnableMotors_toggled",
        "checked",
        "on_rbModeJoint_toggled",
        "on_rbModePlanar_toggled"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'driveRequested'
        QtMocHelpers::SignalData<void(enum Direction, int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::Int, 5 },
        }}),
        // Signal 'stopRequested'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'speedChanged'
        QtMocHelpers::SignalData<void(int)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Signal 'motorsEnabledChanged'
        QtMocHelpers::SignalData<void(bool)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 },
        }}),
        // Signal 'modeChanged'
        QtMocHelpers::SignalData<void(RobotControl::Mode)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Slot 'on_forwardBtn_pressed'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_forwardBtn_released'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_backwardBtn_pressed'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_backwardBtn_released'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_rightBtn_pressed'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_rightBtn_released'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_leftBtn_pressed'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_leftBtn_released'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_stopBtn_clicked'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_speedSlider_valueChanged'
        QtMocHelpers::SlotData<void(int)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 23 },
        }}),
        // Slot 'on_chEnableMotors_toggled'
        QtMocHelpers::SlotData<void(bool)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 25 },
        }}),
        // Slot 'on_rbModeJoint_toggled'
        QtMocHelpers::SlotData<void(bool)>(26, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 25 },
        }}),
        // Slot 'on_rbModePlanar_toggled'
        QtMocHelpers::SlotData<void(bool)>(27, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 25 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<RobotControl, qt_meta_tag_ZN12RobotControlE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject RobotControl::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12RobotControlE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12RobotControlE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12RobotControlE_t>.metaTypes,
    nullptr
} };

void RobotControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<RobotControl *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->driveRequested((*reinterpret_cast< std::add_pointer_t<enum Direction>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->stopRequested(); break;
        case 2: _t->speedChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->motorsEnabledChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->modeChanged((*reinterpret_cast< std::add_pointer_t<RobotControl::Mode>>(_a[1]))); break;
        case 5: _t->on_forwardBtn_pressed(); break;
        case 6: _t->on_forwardBtn_released(); break;
        case 7: _t->on_backwardBtn_pressed(); break;
        case 8: _t->on_backwardBtn_released(); break;
        case 9: _t->on_rightBtn_pressed(); break;
        case 10: _t->on_rightBtn_released(); break;
        case 11: _t->on_leftBtn_pressed(); break;
        case 12: _t->on_leftBtn_released(); break;
        case 13: _t->on_stopBtn_clicked(); break;
        case 14: _t->on_speedSlider_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->on_chEnableMotors_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 16: _t->on_rbModeJoint_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 17: _t->on_rbModePlanar_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (RobotControl::*)(Direction , int )>(_a, &RobotControl::driveRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (RobotControl::*)()>(_a, &RobotControl::stopRequested, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (RobotControl::*)(int )>(_a, &RobotControl::speedChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (RobotControl::*)(bool )>(_a, &RobotControl::motorsEnabledChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (RobotControl::*)(RobotControl::Mode )>(_a, &RobotControl::modeChanged, 4))
            return;
    }
}

const QMetaObject *RobotControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RobotControl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12RobotControlE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RobotControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void RobotControl::driveRequested(Direction _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void RobotControl::stopRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void RobotControl::speedChanged(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void RobotControl::motorsEnabledChanged(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void RobotControl::modeChanged(RobotControl::Mode _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}
QT_WARNING_POP
