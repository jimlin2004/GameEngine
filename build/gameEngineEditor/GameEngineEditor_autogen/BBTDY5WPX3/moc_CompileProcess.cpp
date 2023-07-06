/****************************************************************************
** Meta object code from reading C++ file 'CompileProcess.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../gameEngineEditor/include/runtime/compile/CompileProcess.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CompileProcess.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CompileProcess_t {
    uint offsetsAndSizes[18];
    char stringdata0[15];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[9];
    char stringdata5[9];
    char stringdata6[21];
    char stringdata7[11];
    char stringdata8[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CompileProcess_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CompileProcess_t qt_meta_stringdata_CompileProcess = {
    {
        QT_MOC_LITERAL(0, 14),  // "CompileProcess"
        QT_MOC_LITERAL(15, 11),  // "parseOutput"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 15),  // "parseStandError"
        QT_MOC_LITERAL(44, 8),  // "finished"
        QT_MOC_LITERAL(53, 8),  // "exitCode"
        QT_MOC_LITERAL(62, 20),  // "QProcess::ExitStatus"
        QT_MOC_LITERAL(83, 10),  // "exitStatus"
        QT_MOC_LITERAL(94, 14)   // "callRunProcess"
    },
    "CompileProcess",
    "parseOutput",
    "",
    "parseStandError",
    "finished",
    "exitCode",
    "QProcess::ExitStatus",
    "exitStatus",
    "callRunProcess"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CompileProcess[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x08,    1 /* Private */,
       3,    0,   39,    2, 0x08,    2 /* Private */,
       4,    2,   40,    2, 0x08,    3 /* Private */,
       8,    0,   45,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    5,    7,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject CompileProcess::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CompileProcess.offsetsAndSizes,
    qt_meta_data_CompileProcess,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CompileProcess_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CompileProcess, std::true_type>,
        // method 'parseOutput'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'parseStandError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'finished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QProcess::ExitStatus, std::false_type>,
        // method 'callRunProcess'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void CompileProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CompileProcess *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->parseOutput(); break;
        case 1: _t->parseStandError(); break;
        case 2: _t->finished((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QProcess::ExitStatus>>(_a[2]))); break;
        case 3: _t->callRunProcess(); break;
        default: ;
        }
    }
}

const QMetaObject *CompileProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CompileProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CompileProcess.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CompileProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
