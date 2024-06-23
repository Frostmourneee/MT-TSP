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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStart1;
    QAction *actionSave_as1;
    QAction *actionLoad_from_file1;
    QAction *actionExit1;
    QAction *actionFullscreen1;
    QAction *actionRandom1;
    QAction *actionBack1;
    QAction *actionClear_2;
    QAction *actionPlay1;
    QAction *actionSpeedUp1;
    QAction *actionDefaultZoom1;
    QAction *actionOptimalZoom1;
    QAction *actionShow1;
    QAction *actionUsePlan1;
    QAction *actionUseBestPlan1;
    QAction *actionClear;
    QAction *actionLoad_from_file;
    QAction *actionSave_as;
    QAction *actionFullscreen;
    QAction *actionExit;
    QAction *actionRandom;
    QAction *actionStart;
    QAction *actionBack;
    QAction *actionShow;
    QAction *actionUsePlan;
    QAction *actionUseBestPlan;
    QAction *actionPlay;
    QAction *actionSpeedUp;
    QAction *actionOptimalZoom;
    QAction *actionDefaultZoom;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *controlPanel;
    QWidget *info;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *layoutEntities;
    QLabel *labelYerps;
    QLabel *labelPreysNum;
    QLabel *labelPreys;
    QLabel *labelYerpsNum;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QRadioButton *rBConstruction;
    QRadioButton *rBAnimation;
    QWidget *widget1;
    QHBoxLayout *layoutUsePlan;
    QLabel *labelUsePlan;
    QLineEdit *lineEditUsePlan;
    QPushButton *buttonUsePlan;
    QPushButton *buttonBestPlan;
    QWidget *randomGen;
    QVBoxLayout *vLScene;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout;
    QPushButton *playButton;
    QPushButton *speedUpButton;
    QDoubleSpinBox *dSBTime;
    QSlider *sliderTime;
    QPushButton *optionsButton;
    QPushButton *optimalZoomButton;
    QPushButton *resetZoomButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuAction;
    QMenu *menuControl_Panel_2;
    QMenu *menuAnimation_Control;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(694, 315);
        actionStart1 = new QAction(MainWindow);
        actionStart1->setObjectName(QString::fromUtf8("actionStart1"));
        actionSave_as1 = new QAction(MainWindow);
        actionSave_as1->setObjectName(QString::fromUtf8("actionSave_as1"));
        actionLoad_from_file1 = new QAction(MainWindow);
        actionLoad_from_file1->setObjectName(QString::fromUtf8("actionLoad_from_file1"));
        actionExit1 = new QAction(MainWindow);
        actionExit1->setObjectName(QString::fromUtf8("actionExit1"));
        actionFullscreen1 = new QAction(MainWindow);
        actionFullscreen1->setObjectName(QString::fromUtf8("actionFullscreen1"));
        actionRandom1 = new QAction(MainWindow);
        actionRandom1->setObjectName(QString::fromUtf8("actionRandom1"));
        actionBack1 = new QAction(MainWindow);
        actionBack1->setObjectName(QString::fromUtf8("actionBack1"));
        actionClear_2 = new QAction(MainWindow);
        actionClear_2->setObjectName(QString::fromUtf8("actionClear_2"));
        actionPlay1 = new QAction(MainWindow);
        actionPlay1->setObjectName(QString::fromUtf8("actionPlay1"));
        actionPlay1->setEnabled(false);
        actionSpeedUp1 = new QAction(MainWindow);
        actionSpeedUp1->setObjectName(QString::fromUtf8("actionSpeedUp1"));
        actionSpeedUp1->setEnabled(false);
        actionDefaultZoom1 = new QAction(MainWindow);
        actionDefaultZoom1->setObjectName(QString::fromUtf8("actionDefaultZoom1"));
        actionOptimalZoom1 = new QAction(MainWindow);
        actionOptimalZoom1->setObjectName(QString::fromUtf8("actionOptimalZoom1"));
        actionOptimalZoom1->setEnabled(false);
        actionShow1 = new QAction(MainWindow);
        actionShow1->setObjectName(QString::fromUtf8("actionShow1"));
        actionUsePlan1 = new QAction(MainWindow);
        actionUsePlan1->setObjectName(QString::fromUtf8("actionUsePlan1"));
        actionUsePlan1->setEnabled(false);
        actionUseBestPlan1 = new QAction(MainWindow);
        actionUseBestPlan1->setObjectName(QString::fromUtf8("actionUseBestPlan1"));
        actionUseBestPlan1->setEnabled(false);
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        actionLoad_from_file = new QAction(MainWindow);
        actionLoad_from_file->setObjectName(QString::fromUtf8("actionLoad_from_file"));
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionFullscreen = new QAction(MainWindow);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionRandom = new QAction(MainWindow);
        actionRandom->setObjectName(QString::fromUtf8("actionRandom"));
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        actionBack = new QAction(MainWindow);
        actionBack->setObjectName(QString::fromUtf8("actionBack"));
        actionShow = new QAction(MainWindow);
        actionShow->setObjectName(QString::fromUtf8("actionShow"));
        actionUsePlan = new QAction(MainWindow);
        actionUsePlan->setObjectName(QString::fromUtf8("actionUsePlan"));
        actionUsePlan->setEnabled(false);
        actionUseBestPlan = new QAction(MainWindow);
        actionUseBestPlan->setObjectName(QString::fromUtf8("actionUseBestPlan"));
        actionUseBestPlan->setEnabled(false);
        actionPlay = new QAction(MainWindow);
        actionPlay->setObjectName(QString::fromUtf8("actionPlay"));
        actionPlay->setEnabled(false);
        actionSpeedUp = new QAction(MainWindow);
        actionSpeedUp->setObjectName(QString::fromUtf8("actionSpeedUp"));
        actionSpeedUp->setEnabled(false);
        actionOptimalZoom = new QAction(MainWindow);
        actionOptimalZoom->setObjectName(QString::fromUtf8("actionOptimalZoom"));
        actionOptimalZoom->setEnabled(false);
        actionDefaultZoom = new QAction(MainWindow);
        actionDefaultZoom->setObjectName(QString::fromUtf8("actionDefaultZoom"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        controlPanel = new QTabWidget(centralwidget);
        controlPanel->setObjectName(QString::fromUtf8("controlPanel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(controlPanel->sizePolicy().hasHeightForWidth());
        controlPanel->setSizePolicy(sizePolicy);
        controlPanel->setMinimumSize(QSize(400, 0));
        controlPanel->setMaximumSize(QSize(400, 16777215));
        QFont font;
        font.setPointSize(10);
        controlPanel->setFont(font);
        controlPanel->setTabPosition(QTabWidget::North);
        controlPanel->setDocumentMode(false);
        controlPanel->setTabsClosable(false);
        controlPanel->setMovable(false);
        controlPanel->setTabBarAutoHide(false);
        info = new QWidget();
        info->setObjectName(QString::fromUtf8("info"));
        horizontalLayoutWidget = new QWidget(info);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(9, 9, 361, 31));
        layoutEntities = new QHBoxLayout(horizontalLayoutWidget);
        layoutEntities->setObjectName(QString::fromUtf8("layoutEntities"));
        layoutEntities->setContentsMargins(0, 0, 0, 0);
        labelYerps = new QLabel(horizontalLayoutWidget);
        labelYerps->setObjectName(QString::fromUtf8("labelYerps"));
        labelYerps->setFont(font);
        labelYerps->setLayoutDirection(Qt::LeftToRight);
        labelYerps->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        layoutEntities->addWidget(labelYerps);

        labelPreysNum = new QLabel(horizontalLayoutWidget);
        labelPreysNum->setObjectName(QString::fromUtf8("labelPreysNum"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        labelPreysNum->setFont(font1);
        labelPreysNum->setAlignment(Qt::AlignCenter);

        layoutEntities->addWidget(labelPreysNum);

        labelPreys = new QLabel(horizontalLayoutWidget);
        labelPreys->setObjectName(QString::fromUtf8("labelPreys"));
        labelPreys->setAlignment(Qt::AlignCenter);

        layoutEntities->addWidget(labelPreys);

        labelYerpsNum = new QLabel(horizontalLayoutWidget);
        labelYerpsNum->setObjectName(QString::fromUtf8("labelYerpsNum"));
        labelYerpsNum->setFont(font1);
        labelYerpsNum->setAlignment(Qt::AlignCenter);

        layoutEntities->addWidget(labelYerpsNum);

        widget = new QWidget(info);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 110, 361, 52));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        rBConstruction = new QRadioButton(widget);
        rBConstruction->setObjectName(QString::fromUtf8("rBConstruction"));
        rBConstruction->setChecked(true);

        verticalLayout->addWidget(rBConstruction);

        rBAnimation = new QRadioButton(widget);
        rBAnimation->setObjectName(QString::fromUtf8("rBAnimation"));
        rBAnimation->setEnabled(false);

        verticalLayout->addWidget(rBAnimation);

        widget1 = new QWidget(info);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(11, 61, 361, 34));
        layoutUsePlan = new QHBoxLayout(widget1);
        layoutUsePlan->setObjectName(QString::fromUtf8("layoutUsePlan"));
        layoutUsePlan->setContentsMargins(0, 0, 0, 0);
        labelUsePlan = new QLabel(widget1);
        labelUsePlan->setObjectName(QString::fromUtf8("labelUsePlan"));
        labelUsePlan->setMinimumSize(QSize(88, 0));
        labelUsePlan->setMaximumSize(QSize(88, 16777215));
        labelUsePlan->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        layoutUsePlan->addWidget(labelUsePlan);

        lineEditUsePlan = new QLineEdit(widget1);
        lineEditUsePlan->setObjectName(QString::fromUtf8("lineEditUsePlan"));
        lineEditUsePlan->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditUsePlan->sizePolicy().hasHeightForWidth());
        lineEditUsePlan->setSizePolicy(sizePolicy1);

        layoutUsePlan->addWidget(lineEditUsePlan);

        buttonUsePlan = new QPushButton(widget1);
        buttonUsePlan->setObjectName(QString::fromUtf8("buttonUsePlan"));
        buttonUsePlan->setEnabled(false);
        buttonUsePlan->setMinimumSize(QSize(32, 32));
        buttonUsePlan->setMaximumSize(QSize(32, 32));
        buttonUsePlan->setIconSize(QSize(32, 32));
        buttonUsePlan->setAutoDefault(false);
        buttonUsePlan->setFlat(true);

        layoutUsePlan->addWidget(buttonUsePlan);

        buttonBestPlan = new QPushButton(widget1);
        buttonBestPlan->setObjectName(QString::fromUtf8("buttonBestPlan"));
        buttonBestPlan->setEnabled(false);
        buttonBestPlan->setMinimumSize(QSize(32, 32));
        buttonBestPlan->setMaximumSize(QSize(32, 32));
        buttonBestPlan->setIconSize(QSize(32, 32));
        buttonBestPlan->setAutoDefault(false);
        buttonBestPlan->setFlat(true);

        layoutUsePlan->addWidget(buttonBestPlan);

        controlPanel->addTab(info, QString());
        randomGen = new QWidget();
        randomGen->setObjectName(QString::fromUtf8("randomGen"));
        controlPanel->addTab(randomGen, QString());

        horizontalLayout_2->addWidget(controlPanel);

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
        dSBTime->setEnabled(false);
        dSBTime->setMinimumSize(QSize(80, 28));
        dSBTime->setFrame(true);
        dSBTime->setAlignment(Qt::AlignCenter);
        dSBTime->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout->addWidget(dSBTime);

        sliderTime = new QSlider(centralwidget);
        sliderTime->setObjectName(QString::fromUtf8("sliderTime"));
        sliderTime->setEnabled(false);
        sliderTime->setMaximum(10000000);
        sliderTime->setPageStep(1);
        sliderTime->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(sliderTime);

        optionsButton = new QPushButton(centralwidget);
        optionsButton->setObjectName(QString::fromUtf8("optionsButton"));
        optionsButton->setEnabled(true);
        optionsButton->setMinimumSize(QSize(32, 32));
        optionsButton->setMaximumSize(QSize(32, 32));
        optionsButton->setIconSize(QSize(32, 32));
        optionsButton->setAutoDefault(false);
        optionsButton->setFlat(true);

        horizontalLayout->addWidget(optionsButton);

        optimalZoomButton = new QPushButton(centralwidget);
        optimalZoomButton->setObjectName(QString::fromUtf8("optimalZoomButton"));
        optimalZoomButton->setEnabled(false);
        optimalZoomButton->setMinimumSize(QSize(32, 32));
        optimalZoomButton->setMaximumSize(QSize(32, 32));
        optimalZoomButton->setIconSize(QSize(32, 32));
        optimalZoomButton->setAutoDefault(false);
        optimalZoomButton->setFlat(true);

        horizontalLayout->addWidget(optimalZoomButton);

        resetZoomButton = new QPushButton(centralwidget);
        resetZoomButton->setObjectName(QString::fromUtf8("resetZoomButton"));
        resetZoomButton->setEnabled(true);
        resetZoomButton->setMinimumSize(QSize(32, 32));
        resetZoomButton->setMaximumSize(QSize(32, 32));
        resetZoomButton->setIconSize(QSize(32, 32));
        resetZoomButton->setAutoDefault(false);
        resetZoomButton->setFlat(true);

        horizontalLayout->addWidget(resetZoomButton);


        vLScene->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(vLScene);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 694, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuAction = new QMenu(menubar);
        menuAction->setObjectName(QString::fromUtf8("menuAction"));
        menuControl_Panel_2 = new QMenu(menubar);
        menuControl_Panel_2->setObjectName(QString::fromUtf8("menuControl_Panel_2"));
        menuAnimation_Control = new QMenu(menubar);
        menuAnimation_Control->setObjectName(QString::fromUtf8("menuAnimation_Control"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuAction->menuAction());
        menubar->addAction(menuControl_Panel_2->menuAction());
        menubar->addAction(menuAnimation_Control->menuAction());
        menuFile->addAction(actionClear);
        menuFile->addAction(actionLoad_from_file);
        menuFile->addAction(actionSave_as);
        menuView->addAction(actionFullscreen);
        menuView->addAction(actionExit);
        menuAction->addAction(actionRandom);
        menuAction->addAction(actionStart);
        menuAction->addAction(actionBack);
        menuControl_Panel_2->addAction(actionShow);
        menuControl_Panel_2->addAction(actionUsePlan);
        menuControl_Panel_2->addAction(actionUseBestPlan);
        menuAnimation_Control->addAction(actionPlay);
        menuAnimation_Control->addAction(actionSpeedUp);
        menuAnimation_Control->addAction(actionOptimalZoom);
        menuAnimation_Control->addAction(actionDefaultZoom);

        retranslateUi(MainWindow);

        controlPanel->setCurrentIndex(0);
        buttonUsePlan->setDefault(false);
        buttonBestPlan->setDefault(false);
        playButton->setDefault(false);
        speedUpButton->setDefault(false);
        optionsButton->setDefault(false);
        optimalZoomButton->setDefault(false);
        resetZoomButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MT-TSP", nullptr));
        actionStart1->setText(QCoreApplication::translate("MainWindow", "Start Calculation", nullptr));
#if QT_CONFIG(tooltip)
        actionStart1->setToolTip(QCoreApplication::translate("MainWindow", "Start optimal plans calculation process", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSave_as1->setText(QCoreApplication::translate("MainWindow", "Save As", nullptr));
#if QT_CONFIG(tooltip)
        actionSave_as1->setToolTip(QCoreApplication::translate("MainWindow", "Choose file to save data about preys and yerps", nullptr));
#endif // QT_CONFIG(tooltip)
        actionLoad_from_file1->setText(QCoreApplication::translate("MainWindow", "Load Configuration...", nullptr));
#if QT_CONFIG(tooltip)
        actionLoad_from_file1->setToolTip(QCoreApplication::translate("MainWindow", "Choose file to load data about preys and yerps", nullptr));
#endif // QT_CONFIG(tooltip)
        actionExit1->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionFullscreen1->setText(QCoreApplication::translate("MainWindow", "Fullscreen", nullptr));
        actionRandom1->setText(QCoreApplication::translate("MainWindow", "Random Generation", nullptr));
#if QT_CONFIG(tooltip)
        actionRandom1->setToolTip(QCoreApplication::translate("MainWindow", "Generate preys and yerps randomly", nullptr));
#endif // QT_CONFIG(tooltip)
        actionBack1->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
#if QT_CONFIG(tooltip)
        actionBack1->setToolTip(QCoreApplication::translate("MainWindow", "Rollback change", nullptr));
#endif // QT_CONFIG(tooltip)
        actionClear_2->setText(QCoreApplication::translate("MainWindow", "New Configuration...", nullptr));
#if QT_CONFIG(tooltip)
        actionClear_2->setToolTip(QCoreApplication::translate("MainWindow", "Clear the scene, restarts everything", nullptr));
#endif // QT_CONFIG(tooltip)
        actionPlay1->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        actionSpeedUp1->setText(QCoreApplication::translate("MainWindow", "Speed up x1, x2, x5, x10", nullptr));
        actionDefaultZoom1->setText(QCoreApplication::translate("MainWindow", "Default Scene View", nullptr));
        actionOptimalZoom1->setText(QCoreApplication::translate("MainWindow", "Change View to Optimal", nullptr));
        actionShow1->setText(QCoreApplication::translate("MainWindow", "Show", nullptr));
        actionUsePlan1->setText(QCoreApplication::translate("MainWindow", "Use Plan", nullptr));
        actionUseBestPlan1->setText(QCoreApplication::translate("MainWindow", "Use Best Plan", nullptr));
        actionClear->setText(QCoreApplication::translate("MainWindow", "New Configuration...", nullptr));
#if QT_CONFIG(shortcut)
        actionClear->setShortcut(QCoreApplication::translate("MainWindow", "R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLoad_from_file->setText(QCoreApplication::translate("MainWindow", "Load Configuration...", nullptr));
#if QT_CONFIG(shortcut)
        actionLoad_from_file->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_as->setText(QCoreApplication::translate("MainWindow", "Save As...", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_as->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFullscreen->setText(QCoreApplication::translate("MainWindow", "Fullscreen", nullptr));
#if QT_CONFIG(shortcut)
        actionFullscreen->setShortcut(QCoreApplication::translate("MainWindow", "F11", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MainWindow", "Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRandom->setText(QCoreApplication::translate("MainWindow", "Random Generation", nullptr));
#if QT_CONFIG(shortcut)
        actionRandom->setShortcut(QCoreApplication::translate("MainWindow", "G", nullptr));
#endif // QT_CONFIG(shortcut)
        actionStart->setText(QCoreApplication::translate("MainWindow", "Start Calculation", nullptr));
#if QT_CONFIG(shortcut)
        actionStart->setShortcut(QCoreApplication::translate("MainWindow", "Shift+Return", nullptr));
#endif // QT_CONFIG(shortcut)
        actionBack->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
#if QT_CONFIG(shortcut)
        actionBack->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionShow->setText(QCoreApplication::translate("MainWindow", "Show", nullptr));
#if QT_CONFIG(shortcut)
        actionShow->setShortcut(QCoreApplication::translate("MainWindow", "I", nullptr));
#endif // QT_CONFIG(shortcut)
        actionUsePlan->setText(QCoreApplication::translate("MainWindow", "Use Plan", nullptr));
#if QT_CONFIG(shortcut)
        actionUsePlan->setShortcut(QCoreApplication::translate("MainWindow", "U", nullptr));
#endif // QT_CONFIG(shortcut)
        actionUseBestPlan->setText(QCoreApplication::translate("MainWindow", "Use Best Plan", nullptr));
#if QT_CONFIG(shortcut)
        actionUseBestPlan->setShortcut(QCoreApplication::translate("MainWindow", "B", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPlay->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
#if QT_CONFIG(shortcut)
        actionPlay->setShortcut(QCoreApplication::translate("MainWindow", "Space", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSpeedUp->setText(QCoreApplication::translate("MainWindow", "Speed up x1, x2, x5, x10", nullptr));
#if QT_CONFIG(shortcut)
        actionSpeedUp->setShortcut(QCoreApplication::translate("MainWindow", "Up", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOptimalZoom->setText(QCoreApplication::translate("MainWindow", "Change View to Optimal", nullptr));
#if QT_CONFIG(shortcut)
        actionOptimalZoom->setShortcut(QCoreApplication::translate("MainWindow", "Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDefaultZoom->setText(QCoreApplication::translate("MainWindow", "Default Scene View", nullptr));
#if QT_CONFIG(shortcut)
        actionDefaultZoom->setShortcut(QCoreApplication::translate("MainWindow", "H", nullptr));
#endif // QT_CONFIG(shortcut)
        labelYerps->setText(QCoreApplication::translate("MainWindow", "Preys:", nullptr));
        labelPreysNum->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        labelPreys->setText(QCoreApplication::translate("MainWindow", "Yerps:", nullptr));
        labelYerpsNum->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        rBConstruction->setText(QCoreApplication::translate("MainWindow", "Construction mode", nullptr));
        rBAnimation->setText(QCoreApplication::translate("MainWindow", "Animation mode", nullptr));
        labelUsePlan->setText(QCoreApplication::translate("MainWindow", "Use plan:", nullptr));
        buttonUsePlan->setText(QString());
        buttonBestPlan->setText(QString());
        controlPanel->setTabText(controlPanel->indexOf(info), QCoreApplication::translate("MainWindow", "General Info", nullptr));
        controlPanel->setTabText(controlPanel->indexOf(randomGen), QCoreApplication::translate("MainWindow", "Generation options", nullptr));
        playButton->setText(QString());
        speedUpButton->setText(QString());
        optionsButton->setText(QString());
        optimalZoomButton->setText(QString());
        resetZoomButton->setText(QString());
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        menuAction->setTitle(QCoreApplication::translate("MainWindow", "Action", nullptr));
        menuControl_Panel_2->setTitle(QCoreApplication::translate("MainWindow", "Control Panel", nullptr));
        menuAnimation_Control->setTitle(QCoreApplication::translate("MainWindow", "Animation Control", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
