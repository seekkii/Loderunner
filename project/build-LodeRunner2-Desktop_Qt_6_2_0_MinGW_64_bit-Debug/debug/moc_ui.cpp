/****************************************************************************
** Meta object code from reading C++ file 'ui.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../LodeRunner2/ui.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui_t {
    const uint offsetsAndSize[30];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ui_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ui_t qt_meta_stringdata_ui = {
    {
QT_MOC_LITERAL(0, 2), // "ui"
QT_MOC_LITERAL(3, 4), // "fall"
QT_MOC_LITERAL(8, 0), // ""
QT_MOC_LITERAL(9, 10), // "Character&"
QT_MOC_LITERAL(20, 3), // "cha"
QT_MOC_LITERAL(24, 7), // "mobfall"
QT_MOC_LITERAL(32, 5), // "mobs&"
QT_MOC_LITERAL(38, 3), // "mob"
QT_MOC_LITERAL(42, 14), // "mobs_go_around"
QT_MOC_LITERAL(57, 5), // "reset"
QT_MOC_LITERAL(63, 7), // "next_lv"
QT_MOC_LITERAL(71, 8), // "inactive"
QT_MOC_LITERAL(80, 7), // "respawn"
QT_MOC_LITERAL(88, 1), // "i"
QT_MOC_LITERAL(90, 1) // "j"

    },
    "ui\0fall\0\0Character&\0cha\0mobfall\0mobs&\0"
    "mob\0mobs_go_around\0reset\0next_lv\0"
    "inactive\0respawn\0i\0j"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x0a,    1 /* Public */,
       5,    1,   59,    2, 0x0a,    3 /* Public */,
       8,    1,   62,    2, 0x0a,    5 /* Public */,
       9,    0,   65,    2, 0x0a,    7 /* Public */,
      10,    0,   66,    2, 0x0a,    8 /* Public */,
      11,    1,   67,    2, 0x0a,    9 /* Public */,
      12,    2,   70,    2, 0x0a,   11 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   13,   14,

       0        // eod
};

void ui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ui *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fall((*reinterpret_cast< Character(*)>(_a[1]))); break;
        case 1: _t->mobfall((*reinterpret_cast< mobs(*)>(_a[1]))); break;
        case 2: _t->mobs_go_around((*reinterpret_cast< mobs(*)>(_a[1]))); break;
        case 3: _t->reset(); break;
        case 4: _t->next_lv(); break;
        case 5: _t->inactive((*reinterpret_cast< mobs(*)>(_a[1]))); break;
        case 6: _t->respawn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject ui::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ui.offsetsAndSize,
    qt_meta_data_ui,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ui_t
, QtPrivate::TypeAndForceComplete<ui, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Character &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<mobs &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<mobs &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<mobs &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *ui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
