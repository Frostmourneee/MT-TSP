/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStart;
    QAction *actionSave_as;
    QAction *actionLoad_from_file;
    QAction *actionExit;
    QAction *actionFullscreen;
    QAction *actionRandom;
    QAction *actionBack;
    QAction *actionClear;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rBConstruction;
    QRadioButton *rBAnimation;
    QVBoxLayout *vLScene;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout;
    QPushButton *playButton;
    QPushButton *speedUpButton;
    QDoubleSpinBox *dSBTime;
    QSlider *sliderTime;
    QMenuBar *menubar;
    QMenu *menuOptions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(639, 420);
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionLoad_from_file = new QAction(MainWindow);
        actionLoad_from_file->setObjectName(QString::fromUtf8("actionLoad_from_file"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionFullscreen = new QAction(MainWindow);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        actionRandom = new QAction(MainWindow);
        actionRandom->setObjectName(QString::fromUtf8("actionRandom"));
        actionBack = new QAction(MainWindow);
        actionBack->setObjectName(QString::fromUtf8("actionBack"));
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        rBConstruction = new QRadioButton(centralwidget);
        rBConstruction->setObjectName(QString::fromUtf8("rBConstruction"));
        rBConstruction->setChecked(true);

        verticalLayout_2->addWidget(rBConstruction);

        rBAnimation = new QRadioButton(centralwidget);
        rBAnimation->setObjectName(QString::fromUtf8("rBAnimation"));
        rBAnimation->setEnabled(false);

        verticalLayout_2->addWidget(rBAnimation);


        horizontalLayout_2->addLayout(verticalLayout_2);

        vLScene = new QVBoxLayout();
        vLScene->setObjectName(QString::fromUtf8("vLScene"));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        vLScene->addWidget(progressBar);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        playButton = new QPushButton(centralwidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setEnabled(false);
        playButton->setMinimumSize(QSize(32, 32));
        playButton->setMaximumSize(QSize(32, 32));
        playButton->setIconSize(QSize(32, 32));
        playButton->setAutoDefault(false);
        playButton->setFlat(true);

        horizontalLayout->addWidget(playButton);

        speedUpButton = new QPushButton(centralwidget);
        speedUpButton->setObjectName(QString::fromUtf8("speedUpButton"));
        speedUpButton->setEnabled(false);
        speedUpButton->setMinimumSize(QSize(32, 32));
        speedUpButton->setMaximumSize(QSize(32, 32));
        speedUpButton->setIconSize(QSize(32, 32));
        speedUpButton->setAutoDefault(false);
        speedUpButton->setFlat(true);

        horizontalLayout->addWidget(speedUpButton);

        dSBTime = new QDoubleSpinBox(centralwidget);
        dSBTime->setObjectName(QString::fromUtf8("dSBTime"));
        dSBTime->setMinimumSize(QSize(80, 28));
        dSBTime->setFrame(true);
        dSBTime->setAlignment(Qt::AlignCenter);
        dSBTime->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout->addWidget(dSBTime);

        sliderTime = new QSlider(centralwidget);
        sliderTime->setObjectName(QString::fromUtf8("sliderTime"));
        sliderTime->setMaximum(10000000);
        sliderTime->setPageStep(1);
        sliderTime->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(sliderTime);


        vLScene->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(vLScene);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 639, 21));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuOptions->menuAction());
        menuOptions->addAction(actionRandom);
        menuOptions->addAction(actionStart);
        menuOptions->addAction(actionBack);
        menuOptions->addAction(actionClear);
        menuOptions->addAction(actionFullscreen);
        menuOptions->addAction(actionExit);
        menuOptions->addSeparator();
        menuOptions->addAction(actionSave_as);
        menuOptions->addAction(actionLoad_from_file);

        retranslateUi(MainWindow);

        playButton->setDefault(false);
        speedUpButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MT-TSP", nullptr));
        actionStart->setText(QCoreApplication::translate("MainWindow", "Start calculation", nullptr));
#if QT_CONFIG(tooltip)
        actionStart->setToolTip(QCoreApplication::translate("MainWindow", "Start optimal plans calculation process", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionStart->setShortcut(QCoreApplication::translate("MainWindow", "Shift+Return", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_as->setText(QCoreApplication::translate("MainWindow", "Save as", nullptr));
#if QT_CONFIG(tooltip)
        actionSave_as->setToolTip(QCoreApplication::translate("MainWindow", "Choose file to save data about preys and yerps", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave_as->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLoad_from_file->setText(QCoreApplication::translate("MainWindow", "Load from file", nullptr));
#if QT_CONFIG(tooltip)
        actionLoad_from_file->setToolTip(QCoreApplication::translate("MainWindow", "Choose file to load data about preys and yerps", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionLoad_from_file->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MainWindow", "Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFullscreen->setText(QCoreApplication::translate("MainWindow", "Fullscreen", nullptr));
#if QT_CONFIG(shortcut)
        actionFullscreen->setShortcut(QCoreApplication::translate("MainWindow", "F11", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRandom->setText(QCoreApplication::translate("MainWindow", "Generate randomly", nullptr));
#if QT_CONFIG(tooltip)
        actionRandom->setToolTip(QCoreApplication::translate("MainWindow", "Generate preys and yerps randomly", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionRandom->setShortcut(QCoreApplication::translate("MainWindow", "G", nullptr));
#endif // QT_CONFIG(shortcut)
        actionBack->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
#if QT_CONFIG(tooltip)
        actionBack->setToolTip(QCoreApplication::translate("MainWindow", "Rollback change", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionBack->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
#if QT_CONFIG(tooltip)
        actionClear->setToolTip(QCoreApplication::translate("MainWindow", "Clear the scene, restarts everything", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionClear->setShortcut(QCoreApplication::translate("MainWindow", "R", nullptr));
#endif // QT_CONFIG(shortcut)
        rBConstruction->setText(QCoreApplication::translate("MainWindow", "Construction mode", nullptr));
        rBAnimation->setText(QCoreApplication::translate("MainWindow", "Animation mode", nullptr));
        playButton->setText(QString());
#if QT_CONFIG(shortcut)
        playButton->setShortcut(QCoreApplication::translate("MainWindow", "Space", nullptr));
#endif // QT_CONFIG(shortcut)
        speedUpButton->setText(QString());
#if QT_CONFIG(shortcut)
        speedUpButton->setShortcut(QCoreApplication::translate("MainWindow", "Up", nullptr));
#endif // QT_CONFIG(shortcut)
        menuOptions->setTitle(QCoreApplication::translate("MainWindow", "Actions", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
