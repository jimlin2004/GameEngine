/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../gameEngineEditor/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[28];
    char stringdata0[11];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[22];
    char stringdata5[21];
    char stringdata6[12];
    char stringdata7[23];
    char stringdata8[21];
    char stringdata9[17];
    char stringdata10[5];
    char stringdata11[7];
    char stringdata12[16];
    char stringdata13[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 11),  // "openProject"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 9),  // "saveScene"
        QT_MOC_LITERAL(34, 21),  // "filesystemPanel_click"
        QT_MOC_LITERAL(56, 20),  // "clearFileSystemPanel"
        QT_MOC_LITERAL(77, 11),  // "parseOutput"
        QT_MOC_LITERAL(89, 22),  // "resetGameObjectOutline"
        QT_MOC_LITERAL(112, 20),  // "getTreeWigetItemInfo"
        QT_MOC_LITERAL(133, 16),  // "QTreeWidgetItem*"
        QT_MOC_LITERAL(150, 4),  // "item"
        QT_MOC_LITERAL(155, 6),  // "column"
        QT_MOC_LITERAL(162, 15),  // "openColorDialog"
        QT_MOC_LITERAL(178, 14)   // "compileProject"
    },
    "MainWindow",
    "openProject",
    "",
    "saveScene",
    "filesystemPanel_click",
    "clearFileSystemPanel",
    "parseOutput",
    "resetGameObjectOutline",
    "getTreeWigetItemInfo",
    "QTreeWidgetItem*",
    "item",
    "column",
    "openColorDialog",
    "compileProject"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x08,    1 /* Private */,
       3,    0,   69,    2, 0x08,    2 /* Private */,
       4,    0,   70,    2, 0x08,    3 /* Private */,
       5,    0,   71,    2, 0x08,    4 /* Private */,
       6,    0,   72,    2, 0x08,    5 /* Private */,
       7,    0,   73,    2, 0x08,    6 /* Private */,
       8,    2,   74,    2, 0x08,    7 /* Private */,
      12,    0,   79,    2, 0x08,   10 /* Private */,
      13,    0,   80,    2, 0x08,   11 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,   10,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'openProject'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveScene'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'filesystemPanel_click'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearFileSystemPanel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'parseOutput'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resetGameObjectOutline'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getTreeWigetItemInfo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTreeWidgetItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'openColorDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'compileProject'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->openProject(); break;
        case 1: _t->saveScene(); break;
        case 2: _t->filesystemPanel_click(); break;
        case 3: _t->clearFileSystemPanel(); break;
        case 4: _t->parseOutput(); break;
        case 5: _t->resetGameObjectOutline(); break;
        case 6: _t->getTreeWigetItemInfo((*reinterpret_cast< std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 7: _t->openColorDialog(); break;
        case 8: _t->compileProject(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
