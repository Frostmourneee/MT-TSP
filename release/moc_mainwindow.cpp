/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[347];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 5), // "solve"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 16), // "MyQGraphicsView*"
QT_MOC_LITERAL(4, 35, 4), // "view"
QT_MOC_LITERAL(5, 40, 13), // "keyPressEvent"
QT_MOC_LITERAL(6, 54, 10), // "QKeyEvent*"
QT_MOC_LITERAL(7, 65, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(8, 80, 12), // "QMouseEvent*"
QT_MOC_LITERAL(9, 93, 24), // "on_actionStart_triggered"
QT_MOC_LITERAL(10, 118, 26), // "on_actionSave_as_triggered"
QT_MOC_LITERAL(11, 145, 33), // "on_actionLoad_from_file_trigg..."
QT_MOC_LITERAL(12, 179, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(13, 203, 29), // "on_actionFullscreen_triggered"
QT_MOC_LITERAL(14, 233, 25), // "on_actionRandom_triggered"
QT_MOC_LITERAL(15, 259, 23), // "on_actionBack_triggered"
QT_MOC_LITERAL(16, 283, 24), // "on_actionClear_triggered"
QT_MOC_LITERAL(17, 308, 12), // "solvingEnded"
QT_MOC_LITERAL(18, 321, 17), // "changeProgressBar"
QT_MOC_LITERAL(19, 339, 2), // "vC"
QT_MOC_LITERAL(20, 342, 4) // "vAll"

    },
    "MainWindow\0solve\0\0MyQGraphicsView*\0"
    "view\0keyPressEvent\0QKeyEvent*\0"
    "mouseMoveEvent\0QMouseEvent*\0"
    "on_actionStart_triggered\0"
    "on_actionSave_as_triggered\0"
    "on_actionLoad_from_file_triggered\0"
    "on_actionExit_triggered\0"
    "on_actionFullscreen_triggered\0"
    "on_actionRandom_triggered\0"
    "on_actionBack_triggered\0"
    "on_actionClear_triggered\0solvingEnded\0"
    "changeProgressBar\0vC\0vAll"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   82,    2, 0x08 /* Private */,
       7,    1,   85,    2, 0x08 /* Private */,
       9,    0,   88,    2, 0x08 /* Private */,
      10,    0,   89,    2, 0x08 /* Private */,
      11,    0,   90,    2, 0x08 /* Private */,
      12,    0,   91,    2, 0x08 /* Private */,
      13,    0,   92,    2, 0x08 /* Private */,
      14,    0,   93,    2, 0x08 /* Private */,
      15,    0,   94,    2, 0x08 /* Private */,
      16,    0,   95,    2, 0x08 /* Private */,
      17,    0,   96,    2, 0x08 /* Private */,
      18,    2,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   19,   20,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->solve((*reinterpret_cast< MyQGraphicsView*(*)>(_a[1]))); break;
        case 1: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 2: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->on_actionStart_triggered(); break;
        case 4: _t->on_actionSave_as_triggered(); break;
        case 5: _t->on_actionLoad_from_file_triggered(); break;
        case 6: _t->on_actionExit_triggered(); break;
        case 7: _t->on_actionFullscreen_triggered(); break;
        case 8: _t->on_actionRandom_triggered(); break;
        case 9: _t->on_actionBack_triggered(); break;
        case 10: _t->on_actionClear_triggered(); break;
        case 11: _t->solvingEnded(); break;
        case 12: _t->changeProgressBar((*reinterpret_cast< long long(*)>(_a[1])),(*reinterpret_cast< long long(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(MyQGraphicsView * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::solve)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::solve(MyQGraphicsView * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
