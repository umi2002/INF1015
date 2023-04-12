/****************************************************************************
** Meta object code from reading C++ file 'maingui.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../maingui.hpp"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maingui.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainGui_t {
    uint offsetsAndSizes[22];
    char stringdata0[8];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[12];
    char stringdata5[12];
    char stringdata6[19];
    char stringdata7[17];
    char stringdata8[16];
    char stringdata9[20];
    char stringdata10[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainGui_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainGui_t qt_meta_stringdata_MainGui = {
    {
        QT_MOC_LITERAL(0, 7),  // "MainGui"
        QT_MOC_LITERAL(8, 14),  // "squareSelected"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 18),  // "std::pair<int,int>"
        QT_MOC_LITERAL(43, 11),  // "coordinates"
        QT_MOC_LITERAL(55, 11),  // "invalidMove"
        QT_MOC_LITERAL(67, 18),  // "unHighlightSquares"
        QT_MOC_LITERAL(86, 16),  // "movePieceIfValid"
        QT_MOC_LITERAL(103, 15),  // "highlightSquare"
        QT_MOC_LITERAL(119, 19),  // "highlightValidMoves"
        QT_MOC_LITERAL(139, 19)   // "indicateInvalidMove"
    },
    "MainGui",
    "squareSelected",
    "",
    "std::pair<int,int>",
    "coordinates",
    "invalidMove",
    "unHighlightSquares",
    "movePieceIfValid",
    "highlightSquare",
    "highlightValidMoves",
    "indicateInvalidMove"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainGui[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,
       5,    0,   59,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   60,    2, 0x08,    4 /* Private */,
       7,    1,   61,    2, 0x08,    5 /* Private */,
       8,    1,   64,    2, 0x08,    7 /* Private */,
       9,    1,   67,    2, 0x08,    9 /* Private */,
      10,    0,   70,    2, 0x08,   11 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainGui::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainGui.offsetsAndSizes,
    qt_meta_data_MainGui,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainGui_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainGui, std::true_type>,
        // method 'squareSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::pair<int,int>, std::false_type>,
        // method 'invalidMove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'unHighlightSquares'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'movePieceIfValid'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::pair<int,int>, std::false_type>,
        // method 'highlightSquare'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::pair<int,int>, std::false_type>,
        // method 'highlightValidMoves'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::pair<int,int>, std::false_type>,
        // method 'indicateInvalidMove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainGui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainGui *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->squareSelected((*reinterpret_cast< std::add_pointer_t<std::pair<int,int>>>(_a[1]))); break;
        case 1: _t->invalidMove(); break;
        case 2: _t->unHighlightSquares(); break;
        case 3: _t->movePieceIfValid((*reinterpret_cast< std::add_pointer_t<std::pair<int,int>>>(_a[1]))); break;
        case 4: _t->highlightSquare((*reinterpret_cast< std::add_pointer_t<std::pair<int,int>>>(_a[1]))); break;
        case 5: _t->highlightValidMoves((*reinterpret_cast< std::add_pointer_t<std::pair<int,int>>>(_a[1]))); break;
        case 6: _t->indicateInvalidMove(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainGui::*)(std::pair<int,int> );
            if (_t _q_method = &MainGui::squareSelected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainGui::*)();
            if (_t _q_method = &MainGui::invalidMove; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *MainGui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainGui::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainGui.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void MainGui::squareSelected(std::pair<int,int> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainGui::invalidMove()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
