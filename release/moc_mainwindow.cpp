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
    QByteArrayData data[61];
    char stringdata0[1279];
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
QT_MOC_LITERAL(4, 35, 7), // "usePlan"
QT_MOC_LITERAL(5, 43, 12), // "solvingEnded"
QT_MOC_LITERAL(6, 56, 12), // "usePlanEnded"
QT_MOC_LITERAL(7, 69, 10), // "sliderTick"
QT_MOC_LITERAL(8, 80, 17), // "changeProgressBar"
QT_MOC_LITERAL(9, 98, 2), // "vC"
QT_MOC_LITERAL(10, 101, 4), // "vAll"
QT_MOC_LITERAL(11, 106, 14), // "preyWasCreated"
QT_MOC_LITERAL(12, 121, 14), // "yerpWasCreated"
QT_MOC_LITERAL(13, 136, 26), // "fillTableDueToPreyCreation"
QT_MOC_LITERAL(14, 163, 26), // "fillTableDueToYerpCreation"
QT_MOC_LITERAL(15, 190, 13), // "keyPressEvent"
QT_MOC_LITERAL(16, 204, 10), // "QKeyEvent*"
QT_MOC_LITERAL(17, 215, 15), // "keyReleaseEvent"
QT_MOC_LITERAL(18, 231, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(19, 246, 12), // "QMouseEvent*"
QT_MOC_LITERAL(20, 259, 24), // "on_actionStart_triggered"
QT_MOC_LITERAL(21, 284, 26), // "on_actionSave_as_triggered"
QT_MOC_LITERAL(22, 311, 33), // "on_actionLoad_from_file_trigg..."
QT_MOC_LITERAL(23, 345, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(24, 369, 29), // "on_actionFullscreen_triggered"
QT_MOC_LITERAL(25, 399, 25), // "on_actionRandom_triggered"
QT_MOC_LITERAL(26, 425, 23), // "on_actionBack_triggered"
QT_MOC_LITERAL(27, 449, 24), // "on_actionClear_triggered"
QT_MOC_LITERAL(28, 474, 25), // "on_rBConstruction_toggled"
QT_MOC_LITERAL(29, 500, 7), // "checked"
QT_MOC_LITERAL(30, 508, 23), // "on_dSBTime_valueChanged"
QT_MOC_LITERAL(31, 532, 4), // "arg1"
QT_MOC_LITERAL(32, 537, 26), // "on_sliderTime_valueChanged"
QT_MOC_LITERAL(33, 564, 5), // "value"
QT_MOC_LITERAL(34, 570, 21), // "on_playButton_clicked"
QT_MOC_LITERAL(35, 592, 26), // "on_dSBTime_editingFinished"
QT_MOC_LITERAL(36, 619, 24), // "on_speedUpButton_clicked"
QT_MOC_LITERAL(37, 644, 26), // "on_resetViewButton_clicked"
QT_MOC_LITERAL(38, 671, 23), // "on_actionPlay_triggered"
QT_MOC_LITERAL(39, 695, 26), // "on_actionSpeedUp_triggered"
QT_MOC_LITERAL(40, 722, 28), // "on_actionResetView_triggered"
QT_MOC_LITERAL(41, 751, 28), // "on_optimalZoomButton_clicked"
QT_MOC_LITERAL(42, 780, 30), // "on_actionOptimalZoom_triggered"
QT_MOC_LITERAL(43, 811, 24), // "on_optionsButton_clicked"
QT_MOC_LITERAL(44, 836, 23), // "on_actionShow_triggered"
QT_MOC_LITERAL(45, 860, 24), // "on_buttonUsePlan_clicked"
QT_MOC_LITERAL(46, 885, 25), // "on_buttonBestPlan_clicked"
QT_MOC_LITERAL(47, 911, 26), // "on_actionUsePlan_triggered"
QT_MOC_LITERAL(48, 938, 30), // "on_actionUseBestPlan_triggered"
QT_MOC_LITERAL(49, 969, 31), // "on_checkBoxRandomM_stateChanged"
QT_MOC_LITERAL(50, 1001, 31), // "on_checkBoxRandomN_stateChanged"
QT_MOC_LITERAL(51, 1033, 33), // "on_dSpinBoxVelMin_editingFini..."
QT_MOC_LITERAL(52, 1067, 33), // "on_dSpinBoxVelMax_editingFini..."
QT_MOC_LITERAL(53, 1101, 24), // "on_tableViewPrey_clicked"
QT_MOC_LITERAL(54, 1126, 11), // "QModelIndex"
QT_MOC_LITERAL(55, 1138, 5), // "index"
QT_MOC_LITERAL(56, 1144, 24), // "on_tableViewYerp_clicked"
QT_MOC_LITERAL(57, 1169, 30), // "on_tableViewYerp_doubleClicked"
QT_MOC_LITERAL(58, 1200, 30), // "on_tableViewPrey_doubleClicked"
QT_MOC_LITERAL(59, 1231, 23), // "on_modelPreyDataChanged"
QT_MOC_LITERAL(60, 1255, 23) // "on_modelYerpDataChanged"

    },
    "MainWindow\0solve\0\0MyQGraphicsView*\0"
    "usePlan\0solvingEnded\0usePlanEnded\0"
    "sliderTick\0changeProgressBar\0vC\0vAll\0"
    "preyWasCreated\0yerpWasCreated\0"
    "fillTableDueToPreyCreation\0"
    "fillTableDueToYerpCreation\0keyPressEvent\0"
    "QKeyEvent*\0keyReleaseEvent\0mouseMoveEvent\0"
    "QMouseEvent*\0on_actionStart_triggered\0"
    "on_actionSave_as_triggered\0"
    "on_actionLoad_from_file_triggered\0"
    "on_actionExit_triggered\0"
    "on_actionFullscreen_triggered\0"
    "on_actionRandom_triggered\0"
    "on_actionBack_triggered\0"
    "on_actionClear_triggered\0"
    "on_rBConstruction_toggled\0checked\0"
    "on_dSBTime_valueChanged\0arg1\0"
    "on_sliderTime_valueChanged\0value\0"
    "on_playButton_clicked\0on_dSBTime_editingFinished\0"
    "on_speedUpButton_clicked\0"
    "on_resetViewButton_clicked\0"
    "on_actionPlay_triggered\0"
    "on_actionSpeedUp_triggered\0"
    "on_actionResetView_triggered\0"
    "on_optimalZoomButton_clicked\0"
    "on_actionOptimalZoom_triggered\0"
    "on_optionsButton_clicked\0"
    "on_actionShow_triggered\0"
    "on_buttonUsePlan_clicked\0"
    "on_buttonBestPlan_clicked\0"
    "on_actionUsePlan_triggered\0"
    "on_actionUseBestPlan_triggered\0"
    "on_checkBoxRandomM_stateChanged\0"
    "on_checkBoxRandomN_stateChanged\0"
    "on_dSpinBoxVelMin_editingFinished\0"
    "on_dSpinBoxVelMax_editingFinished\0"
    "on_tableViewPrey_clicked\0QModelIndex\0"
    "index\0on_tableViewYerp_clicked\0"
    "on_tableViewYerp_doubleClicked\0"
    "on_tableViewPrey_doubleClicked\0"
    "on_modelPreyDataChanged\0on_modelYerpDataChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      49,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  259,    2, 0x06 /* Public */,
       4,    1,  262,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,  265,    2, 0x08 /* Private */,
       6,    0,  266,    2, 0x08 /* Private */,
       7,    0,  267,    2, 0x08 /* Private */,
       8,    2,  268,    2, 0x08 /* Private */,
      11,    1,  273,    2, 0x08 /* Private */,
      12,    1,  276,    2, 0x08 /* Private */,
      13,    0,  279,    2, 0x08 /* Private */,
      14,    0,  280,    2, 0x08 /* Private */,
      15,    1,  281,    2, 0x08 /* Private */,
      17,    1,  284,    2, 0x08 /* Private */,
      18,    1,  287,    2, 0x08 /* Private */,
      20,    0,  290,    2, 0x08 /* Private */,
      21,    0,  291,    2, 0x08 /* Private */,
      22,    0,  292,    2, 0x08 /* Private */,
      23,    0,  293,    2, 0x08 /* Private */,
      24,    0,  294,    2, 0x08 /* Private */,
      25,    0,  295,    2, 0x08 /* Private */,
      26,    0,  296,    2, 0x08 /* Private */,
      27,    0,  297,    2, 0x08 /* Private */,
      28,    1,  298,    2, 0x08 /* Private */,
      30,    1,  301,    2, 0x08 /* Private */,
      32,    1,  304,    2, 0x08 /* Private */,
      34,    0,  307,    2, 0x08 /* Private */,
      35,    0,  308,    2, 0x08 /* Private */,
      36,    0,  309,    2, 0x08 /* Private */,
      37,    0,  310,    2, 0x08 /* Private */,
      38,    0,  311,    2, 0x08 /* Private */,
      39,    0,  312,    2, 0x08 /* Private */,
      40,    0,  313,    2, 0x08 /* Private */,
      41,    0,  314,    2, 0x08 /* Private */,
      42,    0,  315,    2, 0x08 /* Private */,
      43,    0,  316,    2, 0x08 /* Private */,
      44,    0,  317,    2, 0x08 /* Private */,
      45,    0,  318,    2, 0x08 /* Private */,
      46,    0,  319,    2, 0x08 /* Private */,
      47,    0,  320,    2, 0x08 /* Private */,
      48,    0,  321,    2, 0x08 /* Private */,
      49,    1,  322,    2, 0x08 /* Private */,
      50,    1,  325,    2, 0x08 /* Private */,
      51,    0,  328,    2, 0x08 /* Private */,
      52,    0,  329,    2, 0x08 /* Private */,
      53,    1,  330,    2, 0x08 /* Private */,
      56,    1,  333,    2, 0x08 /* Private */,
      57,    1,  336,    2, 0x08 /* Private */,
      58,    1,  339,    2, 0x08 /* Private */,
      59,    2,  342,    2, 0x08 /* Private */,
      60,    2,  347,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    9,   10,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 19,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   29,
    QMetaType::Void, QMetaType::Double,   31,
    QMetaType::Void, QMetaType::Int,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void, 0x80000000 | 54, 0x80000000 | 54,    2,    2,
    QMetaType::Void, 0x80000000 | 54, 0x80000000 | 54,    2,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->solve((*reinterpret_cast< MyQGraphicsView*(*)>(_a[1]))); break;
        case 1: _t->usePlan((*reinterpret_cast< MyQGraphicsView*(*)>(_a[1]))); break;
        case 2: _t->solvingEnded(); break;
        case 3: _t->usePlanEnded(); break;
        case 4: _t->sliderTick(); break;
        case 5: _t->changeProgressBar((*reinterpret_cast< long long(*)>(_a[1])),(*reinterpret_cast< long long(*)>(_a[2]))); break;
        case 6: _t->preyWasCreated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->yerpWasCreated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->fillTableDueToPreyCreation(); break;
        case 9: _t->fillTableDueToYerpCreation(); break;
        case 10: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 11: _t->keyReleaseEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 12: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 13: _t->on_actionStart_triggered(); break;
        case 14: _t->on_actionSave_as_triggered(); break;
        case 15: _t->on_actionLoad_from_file_triggered(); break;
        case 16: _t->on_actionExit_triggered(); break;
        case 17: _t->on_actionFullscreen_triggered(); break;
        case 18: _t->on_actionRandom_triggered(); break;
        case 19: _t->on_actionBack_triggered(); break;
        case 20: _t->on_actionClear_triggered(); break;
        case 21: _t->on_rBConstruction_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->on_dSBTime_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 23: _t->on_sliderTime_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->on_playButton_clicked(); break;
        case 25: _t->on_dSBTime_editingFinished(); break;
        case 26: _t->on_speedUpButton_clicked(); break;
        case 27: _t->on_resetViewButton_clicked(); break;
        case 28: _t->on_actionPlay_triggered(); break;
        case 29: _t->on_actionSpeedUp_triggered(); break;
        case 30: _t->on_actionResetView_triggered(); break;
        case 31: _t->on_optimalZoomButton_clicked(); break;
        case 32: _t->on_actionOptimalZoom_triggered(); break;
        case 33: _t->on_optionsButton_clicked(); break;
        case 34: _t->on_actionShow_triggered(); break;
        case 35: _t->on_buttonUsePlan_clicked(); break;
        case 36: _t->on_buttonBestPlan_clicked(); break;
        case 37: _t->on_actionUsePlan_triggered(); break;
        case 38: _t->on_actionUseBestPlan_triggered(); break;
        case 39: _t->on_checkBoxRandomM_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->on_checkBoxRandomN_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->on_dSpinBoxVelMin_editingFinished(); break;
        case 42: _t->on_dSpinBoxVelMax_editingFinished(); break;
        case 43: _t->on_tableViewPrey_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 44: _t->on_tableViewYerp_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 45: _t->on_tableViewYerp_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 46: _t->on_tableViewPrey_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 47: _t->on_modelPreyDataChanged((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndex(*)>(_a[2]))); break;
        case 48: _t->on_modelYerpDataChanged((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndex(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MyQGraphicsView* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MyQGraphicsView* >(); break;
            }
            break;
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
        {
            using _t = void (MainWindow::*)(MyQGraphicsView * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::usePlan)) {
                *result = 1;
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
        if (_id < 49)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 49;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 49)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 49;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::solve(MyQGraphicsView * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::usePlan(MyQGraphicsView * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
