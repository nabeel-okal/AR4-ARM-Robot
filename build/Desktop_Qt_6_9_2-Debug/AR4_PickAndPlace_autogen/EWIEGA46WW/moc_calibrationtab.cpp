/****************************************************************************
** Meta object code from reading C++ file 'calibrationtab.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../calibrationtab.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calibrationtab.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14CalibrationTabE_t {};
} // unnamed namespace

template <> constexpr inline auto CalibrationTab::qt_create_metaobjectdata<qt_meta_tag_ZN14CalibrationTabE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CalibrationTab",
        "exposureNormChanged",
        "",
        "x",
        "brightnessNormChanged",
        "contrastNormChanged",
        "on_btnStartCalibration_clicked",
        "on_btnLoadCalibration_clicked",
        "on_btnSaveCalibration_clicked",
        "on_btnTestCalibration_clicked",
        "on_sliderExposure_valueChanged",
        "value",
        "on_sliderBrightness_valueChanged",
        "on_sliderContrast_valueChanged",
        "on_spinExposure_valueChanged",
        "arg1",
        "on_spinBrightness_valueChanged",
        "on_spinContrast_valueChanged"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'exposureNormChanged'
        QtMocHelpers::SignalData<void(double)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 3 },
        }}),
        // Signal 'brightnessNormChanged'
        QtMocHelpers::SignalData<void(double)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 3 },
        }}),
        // Signal 'contrastNormChanged'
        QtMocHelpers::SignalData<void(double)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 3 },
        }}),
        // Slot 'on_btnStartCalibration_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnLoadCalibration_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnSaveCalibration_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnTestCalibration_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_sliderExposure_valueChanged'
        QtMocHelpers::SlotData<void(int)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 11 },
        }}),
        // Slot 'on_sliderBrightness_valueChanged'
        QtMocHelpers::SlotData<void(int)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 11 },
        }}),
        // Slot 'on_sliderContrast_valueChanged'
        QtMocHelpers::SlotData<void(int)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 11 },
        }}),
        // Slot 'on_spinExposure_valueChanged'
        QtMocHelpers::SlotData<void(int)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'on_spinBrightness_valueChanged'
        QtMocHelpers::SlotData<void(int)>(16, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'on_spinContrast_valueChanged'
        QtMocHelpers::SlotData<void(int)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CalibrationTab, qt_meta_tag_ZN14CalibrationTabE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CalibrationTab::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14CalibrationTabE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14CalibrationTabE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14CalibrationTabE_t>.metaTypes,
    nullptr
} };

void CalibrationTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CalibrationTab *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->exposureNormChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 1: _t->brightnessNormChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->contrastNormChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 3: _t->on_btnStartCalibration_clicked(); break;
        case 4: _t->on_btnLoadCalibration_clicked(); break;
        case 5: _t->on_btnSaveCalibration_clicked(); break;
        case 6: _t->on_btnTestCalibration_clicked(); break;
        case 7: _t->on_sliderExposure_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->on_sliderBrightness_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->on_sliderContrast_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->on_spinExposure_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->on_spinBrightness_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->on_spinContrast_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CalibrationTab::*)(double )>(_a, &CalibrationTab::exposureNormChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CalibrationTab::*)(double )>(_a, &CalibrationTab::brightnessNormChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (CalibrationTab::*)(double )>(_a, &CalibrationTab::contrastNormChanged, 2))
            return;
    }
}

const QMetaObject *CalibrationTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalibrationTab::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14CalibrationTabE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CalibrationTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CalibrationTab::exposureNormChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void CalibrationTab::brightnessNormChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void CalibrationTab::contrastNormChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
