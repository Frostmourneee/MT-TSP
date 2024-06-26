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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClear1;
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
    QAction *actionResetView;
    QAction *actionClear;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *controlPanel;
    QWidget *info;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *layoutEntities;
    QLabel *labelYerps;
    QLabel *labelPreysNum;
    QLabel *labelPreys;
    QLabel *labelYerpsNum;
    QTableView *tableViewYerp;
    QTableView *tableViewPrey;
    QWidget *randomGen;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *layoutGenEntities;
    QLabel *labelGenYerps;
    QSpinBox *spinBoxPreys;
    QLabel *labelGenPreys;
    QSpinBox *spinBoxYerps;
    QFrame *line;
    QCheckBox *checkBoxRandomN;
    QCheckBox *checkBoxRandomM;
    QCheckBox *checkBoxAllYerpsToZero;
    QFrame *line_2;
    QVBoxLayout *verticalLayout;
    QLabel *labelGenVelMin;
    QHBoxLayout *layoutVelocity;
    QDoubleSpinBox *dSpinBoxVelMin;
    QLabel *labelGenVelMax;
    QDoubleSpinBox *dSpinBoxVelMax;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *vLScene;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *rBConstruction;
    QRadioButton *rBAnimation;
    QHBoxLayout *layoutUsePlan;
    QLabel *labelUsePlan;
    QLineEdit *lineEditUsePlan;
    QLabel *labelResT;
    QLabel *labelT;
    QPushButton *buttonUsePlan;
    QPushButton *buttonBestPlan;
    QHBoxLayout *horizontalLayout;
    QPushButton *playButton;
    QPushButton *speedUpButton;
    QDoubleSpinBox *dSBTime;
    QSlider *sliderTime;
    QPushButton *optionsButton;
    QPushButton *optimalZoomButton;
    QPushButton *resetViewButton;
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
        MainWindow->resize(883, 566);
        actionClear1 = new QAction(MainWindow);
        actionClear1->setObjectName(QString::fromUtf8("actionClear1"));
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
        actionResetView = new QAction(MainWindow);
        actionResetView->setObjectName(QString::fromUtf8("actionResetView"));
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
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
        QPalette palette;
        QBrush brush(QColor(170, 170, 127, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::NoRole, brush);
        palette.setBrush(QPalette::Inactive, QPalette::NoRole, brush);
        palette.setBrush(QPalette::Disabled, QPalette::NoRole, brush);
        controlPanel->setPalette(palette);
        QFont font;
        font.setPointSize(12);
        controlPanel->setFont(font);
        controlPanel->setAutoFillBackground(false);
        controlPanel->setTabPosition(QTabWidget::North);
        controlPanel->setTabShape(QTabWidget::Rounded);
        controlPanel->setDocumentMode(false);
        controlPanel->setTabsClosable(false);
        controlPanel->setMovable(false);
        controlPanel->setTabBarAutoHide(false);
        info = new QWidget();
        info->setObjectName(QString::fromUtf8("info"));
        verticalLayout_3 = new QVBoxLayout(info);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        layoutEntities = new QHBoxLayout();
        layoutEntities->setObjectName(QString::fromUtf8("layoutEntities"));
        labelYerps = new QLabel(info);
        labelYerps->setObjectName(QString::fromUtf8("labelYerps"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelYerps->sizePolicy().hasHeightForWidth());
        labelYerps->setSizePolicy(sizePolicy1);
        labelYerps->setFont(font);
        labelYerps->setLayoutDirection(Qt::LeftToRight);
        labelYerps->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        layoutEntities->addWidget(labelYerps);

        labelPreysNum = new QLabel(info);
        labelPreysNum->setObjectName(QString::fromUtf8("labelPreysNum"));
        sizePolicy1.setHeightForWidth(labelPreysNum->sizePolicy().hasHeightForWidth());
        labelPreysNum->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        labelPreysNum->setFont(font1);
        labelPreysNum->setAlignment(Qt::AlignCenter);

        layoutEntities->addWidget(labelPreysNum);

        labelPreys = new QLabel(info);
        labelPreys->setObjectName(QString::fromUtf8("labelPreys"));
        sizePolicy1.setHeightForWidth(labelPreys->sizePolicy().hasHeightForWidth());
        labelPreys->setSizePolicy(sizePolicy1);
        labelPreys->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        layoutEntities->addWidget(labelPreys);

        labelYerpsNum = new QLabel(info);
        labelYerpsNum->setObjectName(QString::fromUtf8("labelYerpsNum"));
        sizePolicy1.setHeightForWidth(labelYerpsNum->sizePolicy().hasHeightForWidth());
        labelYerpsNum->setSizePolicy(sizePolicy1);
        labelYerpsNum->setFont(font1);
        labelYerpsNum->setAlignment(Qt::AlignCenter);

        layoutEntities->addWidget(labelYerpsNum);


        verticalLayout_3->addLayout(layoutEntities);

        tableViewYerp = new QTableView(info);
        tableViewYerp->setObjectName(QString::fromUtf8("tableViewYerp"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableViewYerp->sizePolicy().hasHeightForWidth());
        tableViewYerp->setSizePolicy(sizePolicy2);
        tableViewYerp->setMinimumSize(QSize(375, 220));
        tableViewYerp->setMaximumSize(QSize(375, 220));
        tableViewYerp->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableViewYerp->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

        verticalLayout_3->addWidget(tableViewYerp);

        tableViewPrey = new QTableView(info);
        tableViewPrey->setObjectName(QString::fromUtf8("tableViewPrey"));
        tableViewPrey->setEnabled(true);
        sizePolicy2.setHeightForWidth(tableViewPrey->sizePolicy().hasHeightForWidth());
        tableViewPrey->setSizePolicy(sizePolicy2);
        tableViewPrey->setMinimumSize(QSize(375, 180));
        tableViewPrey->setMaximumSize(QSize(375, 16777215));
        tableViewPrey->setFrameShape(QFrame::StyledPanel);
        tableViewPrey->setFrameShadow(QFrame::Sunken);
        tableViewPrey->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableViewPrey->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableViewPrey->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableViewPrey->setShowGrid(true);

        verticalLayout_3->addWidget(tableViewPrey);

        controlPanel->addTab(info, QString());
        randomGen = new QWidget();
        randomGen->setObjectName(QString::fromUtf8("randomGen"));
        verticalLayout_2 = new QVBoxLayout(randomGen);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        layoutGenEntities = new QHBoxLayout();
        layoutGenEntities->setObjectName(QString::fromUtf8("layoutGenEntities"));
        labelGenYerps = new QLabel(randomGen);
        labelGenYerps->setObjectName(QString::fromUtf8("labelGenYerps"));
        labelGenYerps->setFont(font);
        labelGenYerps->setLayoutDirection(Qt::LeftToRight);
        labelGenYerps->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        layoutGenEntities->addWidget(labelGenYerps);

        spinBoxPreys = new QSpinBox(randomGen);
        spinBoxPreys->setObjectName(QString::fromUtf8("spinBoxPreys"));
        spinBoxPreys->setEnabled(false);
        spinBoxPreys->setFont(font);
        spinBoxPreys->setFrame(true);
        spinBoxPreys->setAlignment(Qt::AlignCenter);
        spinBoxPreys->setReadOnly(false);
        spinBoxPreys->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBoxPreys->setMinimum(1);
        spinBoxPreys->setMaximum(11);

        layoutGenEntities->addWidget(spinBoxPreys);

        labelGenPreys = new QLabel(randomGen);
        labelGenPreys->setObjectName(QString::fromUtf8("labelGenPreys"));
        labelGenPreys->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        layoutGenEntities->addWidget(labelGenPreys);

        spinBoxYerps = new QSpinBox(randomGen);
        spinBoxYerps->setObjectName(QString::fromUtf8("spinBoxYerps"));
        spinBoxYerps->setEnabled(false);
        spinBoxYerps->setFont(font);
        spinBoxYerps->setFrame(true);
        spinBoxYerps->setAlignment(Qt::AlignCenter);
        spinBoxYerps->setReadOnly(false);
        spinBoxYerps->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBoxYerps->setMinimum(1);
        spinBoxYerps->setMaximum(2);

        layoutGenEntities->addWidget(spinBoxYerps);


        verticalLayout_2->addLayout(layoutGenEntities);

        line = new QFrame(randomGen);
        line->setObjectName(QString::fromUtf8("line"));
        line->setMinimumSize(QSize(365, 0));
        line->setMaximumSize(QSize(237, 16777215));
        line->setFrameShadow(QFrame::Plain);
        line->setFrameShape(QFrame::HLine);

        verticalLayout_2->addWidget(line);

        checkBoxRandomN = new QCheckBox(randomGen);
        checkBoxRandomN->setObjectName(QString::fromUtf8("checkBoxRandomN"));
        checkBoxRandomN->setLayoutDirection(Qt::LeftToRight);
        checkBoxRandomN->setChecked(true);

        verticalLayout_2->addWidget(checkBoxRandomN);

        checkBoxRandomM = new QCheckBox(randomGen);
        checkBoxRandomM->setObjectName(QString::fromUtf8("checkBoxRandomM"));
        checkBoxRandomM->setLayoutDirection(Qt::LeftToRight);
        checkBoxRandomM->setChecked(true);

        verticalLayout_2->addWidget(checkBoxRandomM);

        checkBoxAllYerpsToZero = new QCheckBox(randomGen);
        checkBoxAllYerpsToZero->setObjectName(QString::fromUtf8("checkBoxAllYerpsToZero"));
        checkBoxAllYerpsToZero->setLayoutDirection(Qt::LeftToRight);
        checkBoxAllYerpsToZero->setChecked(false);

        verticalLayout_2->addWidget(checkBoxAllYerpsToZero);

        line_2 = new QFrame(randomGen);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setMinimumSize(QSize(365, 0));
        line_2->setMaximumSize(QSize(237, 16777215));
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setFrameShape(QFrame::HLine);

        verticalLayout_2->addWidget(line_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelGenVelMin = new QLabel(randomGen);
        labelGenVelMin->setObjectName(QString::fromUtf8("labelGenVelMin"));
        labelGenVelMin->setFont(font);
        labelGenVelMin->setLayoutDirection(Qt::LeftToRight);
        labelGenVelMin->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(labelGenVelMin);

        layoutVelocity = new QHBoxLayout();
        layoutVelocity->setObjectName(QString::fromUtf8("layoutVelocity"));
        dSpinBoxVelMin = new QDoubleSpinBox(randomGen);
        dSpinBoxVelMin->setObjectName(QString::fromUtf8("dSpinBoxVelMin"));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        dSpinBoxVelMin->setFont(font2);
        dSpinBoxVelMin->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        dSpinBoxVelMin->setDecimals(2);
        dSpinBoxVelMin->setMinimum(0.000000000000000);
        dSpinBoxVelMin->setMaximum(0.950000000000000);
        dSpinBoxVelMin->setSingleStep(0.010000000000000);
        dSpinBoxVelMin->setValue(0.000000000000000);

        layoutVelocity->addWidget(dSpinBoxVelMin);

        labelGenVelMax = new QLabel(randomGen);
        labelGenVelMax->setObjectName(QString::fromUtf8("labelGenVelMax"));
        QFont font3;
        font3.setPointSize(10);
        labelGenVelMax->setFont(font3);
        labelGenVelMax->setLayoutDirection(Qt::LeftToRight);
        labelGenVelMax->setAlignment(Qt::AlignCenter);

        layoutVelocity->addWidget(labelGenVelMax);

        dSpinBoxVelMax = new QDoubleSpinBox(randomGen);
        dSpinBoxVelMax->setObjectName(QString::fromUtf8("dSpinBoxVelMax"));
        dSpinBoxVelMax->setFont(font2);
        dSpinBoxVelMax->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        dSpinBoxVelMax->setDecimals(2);
        dSpinBoxVelMax->setMinimum(0.010000000000000);
        dSpinBoxVelMax->setMaximum(0.950000000000000);
        dSpinBoxVelMax->setSingleStep(0.010000000000000);
        dSpinBoxVelMax->setValue(0.950000000000000);

        layoutVelocity->addWidget(dSpinBoxVelMax);


        verticalLayout->addLayout(layoutVelocity);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);

        controlPanel->addTab(randomGen, QString());

        horizontalLayout_2->addWidget(controlPanel);

        vLScene = new QVBoxLayout();
        vLScene->setObjectName(QString::fromUtf8("vLScene"));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        vLScene->addWidget(progressBar);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        rBConstruction = new QRadioButton(centralwidget);
        rBConstruction->setObjectName(QString::fromUtf8("rBConstruction"));
        rBConstruction->setFont(font);
        rBConstruction->setChecked(true);

        horizontalLayout_3->addWidget(rBConstruction);

        rBAnimation = new QRadioButton(centralwidget);
        rBAnimation->setObjectName(QString::fromUtf8("rBAnimation"));
        rBAnimation->setEnabled(false);
        rBAnimation->setFont(font);
        rBAnimation->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_3->addWidget(rBAnimation);


        vLScene->addLayout(horizontalLayout_3);

        layoutUsePlan = new QHBoxLayout();
        layoutUsePlan->setObjectName(QString::fromUtf8("layoutUsePlan"));
        labelUsePlan = new QLabel(centralwidget);
        labelUsePlan->setObjectName(QString::fromUtf8("labelUsePlan"));
        labelUsePlan->setMinimumSize(QSize(100, 0));
        labelUsePlan->setMaximumSize(QSize(100, 16777215));
        labelUsePlan->setFont(font);
        labelUsePlan->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        layoutUsePlan->addWidget(labelUsePlan);

        lineEditUsePlan = new QLineEdit(centralwidget);
        lineEditUsePlan->setObjectName(QString::fromUtf8("lineEditUsePlan"));
        lineEditUsePlan->setEnabled(false);
        sizePolicy1.setHeightForWidth(lineEditUsePlan->sizePolicy().hasHeightForWidth());
        lineEditUsePlan->setSizePolicy(sizePolicy1);
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setWeight(75);
        lineEditUsePlan->setFont(font4);
        lineEditUsePlan->setAlignment(Qt::AlignCenter);

        layoutUsePlan->addWidget(lineEditUsePlan);

        labelResT = new QLabel(centralwidget);
        labelResT->setObjectName(QString::fromUtf8("labelResT"));
        labelResT->setMinimumSize(QSize(130, 0));
        labelResT->setMaximumSize(QSize(130, 16777215));
        labelResT->setFont(font);
        labelResT->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        layoutUsePlan->addWidget(labelResT);

        labelT = new QLabel(centralwidget);
        labelT->setObjectName(QString::fromUtf8("labelT"));
        labelT->setMinimumSize(QSize(100, 0));
        labelT->setMaximumSize(QSize(100, 16777215));
        QFont font5;
        font5.setPointSize(12);
        font5.setBold(true);
        font5.setWeight(75);
        labelT->setFont(font5);
        labelT->setFrameShape(QFrame::NoFrame);
        labelT->setLineWidth(1);
        labelT->setAlignment(Qt::AlignCenter);

        layoutUsePlan->addWidget(labelT);

        buttonUsePlan = new QPushButton(centralwidget);
        buttonUsePlan->setObjectName(QString::fromUtf8("buttonUsePlan"));
        buttonUsePlan->setEnabled(false);
        buttonUsePlan->setMinimumSize(QSize(32, 32));
        buttonUsePlan->setMaximumSize(QSize(32, 32));
        buttonUsePlan->setIconSize(QSize(32, 32));
        buttonUsePlan->setAutoDefault(false);
        buttonUsePlan->setFlat(true);

        layoutUsePlan->addWidget(buttonUsePlan);

        buttonBestPlan = new QPushButton(centralwidget);
        buttonBestPlan->setObjectName(QString::fromUtf8("buttonBestPlan"));
        buttonBestPlan->setEnabled(false);
        buttonBestPlan->setMinimumSize(QSize(32, 32));
        buttonBestPlan->setMaximumSize(QSize(32, 32));
        buttonBestPlan->setIconSize(QSize(32, 32));
        buttonBestPlan->setAutoDefault(false);
        buttonBestPlan->setFlat(true);

        layoutUsePlan->addWidget(buttonBestPlan);


        vLScene->addLayout(layoutUsePlan);

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
        dSBTime->setFont(font);
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

        resetViewButton = new QPushButton(centralwidget);
        resetViewButton->setObjectName(QString::fromUtf8("resetViewButton"));
        resetViewButton->setEnabled(true);
        resetViewButton->setMinimumSize(QSize(32, 32));
        resetViewButton->setMaximumSize(QSize(32, 32));
        resetViewButton->setIconSize(QSize(32, 32));
        resetViewButton->setAutoDefault(false);
        resetViewButton->setFlat(true);

        horizontalLayout->addWidget(resetViewButton);


        vLScene->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(vLScene);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 883, 21));
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
        menuFile->addAction(actionLoad_from_file);
        menuFile->addAction(actionSave_as);
        menuView->addAction(actionFullscreen);
        menuView->addAction(actionExit);
        menuAction->addAction(actionClear);
        menuAction->addAction(actionRandom);
        menuAction->addAction(actionStart);
        menuAction->addAction(actionBack);
        menuControl_Panel_2->addAction(actionShow);
        menuControl_Panel_2->addAction(actionUsePlan);
        menuControl_Panel_2->addAction(actionUseBestPlan);
        menuAnimation_Control->addAction(actionPlay);
        menuAnimation_Control->addAction(actionSpeedUp);
        menuAnimation_Control->addAction(actionOptimalZoom);
        menuAnimation_Control->addAction(actionResetView);

        retranslateUi(MainWindow);

        controlPanel->setCurrentIndex(0);
        buttonUsePlan->setDefault(false);
        buttonBestPlan->setDefault(false);
        playButton->setDefault(false);
        speedUpButton->setDefault(false);
        optionsButton->setDefault(false);
        optimalZoomButton->setDefault(false);
        resetViewButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MT-TSP", nullptr));
        actionClear1->setText(QCoreApplication::translate("MainWindow", "Restart", nullptr));
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
        actionResetView->setText(QCoreApplication::translate("MainWindow", "Default Scene View", nullptr));
#if QT_CONFIG(shortcut)
        actionResetView->setShortcut(QCoreApplication::translate("MainWindow", "H", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClear->setText(QCoreApplication::translate("MainWindow", "Restart", nullptr));
#if QT_CONFIG(shortcut)
        actionClear->setShortcut(QCoreApplication::translate("MainWindow", "R", nullptr));
#endif // QT_CONFIG(shortcut)
        labelYerps->setText(QCoreApplication::translate("MainWindow", "Preys:", nullptr));
        labelPreysNum->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        labelPreys->setText(QCoreApplication::translate("MainWindow", "Yerps:", nullptr));
        labelYerpsNum->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        controlPanel->setTabText(controlPanel->indexOf(info), QCoreApplication::translate("MainWindow", "General Info", nullptr));
        labelGenYerps->setText(QCoreApplication::translate("MainWindow", "Preys:", nullptr));
        labelGenPreys->setText(QCoreApplication::translate("MainWindow", "Yerps:", nullptr));
        checkBoxRandomN->setText(QCoreApplication::translate("MainWindow", "Preys from 1 to 11", nullptr));
        checkBoxRandomM->setText(QCoreApplication::translate("MainWindow", "Yerps from 1 to 2", nullptr));
        checkBoxAllYerpsToZero->setText(QCoreApplication::translate("MainWindow", "Set all Yerps to (0, 0)", nullptr));
        labelGenVelMin->setText(QCoreApplication::translate("MainWindow", "Set Prey's velocity from", nullptr));
        labelGenVelMax->setText(QCoreApplication::translate("MainWindow", "To", nullptr));
        controlPanel->setTabText(controlPanel->indexOf(randomGen), QCoreApplication::translate("MainWindow", "Generation settings", nullptr));
        rBConstruction->setText(QCoreApplication::translate("MainWindow", "Construction Mode", nullptr));
        rBAnimation->setText(QCoreApplication::translate("MainWindow", "Animation Mode", nullptr));
#if QT_CONFIG(tooltip)
        labelUsePlan->setToolTip(QCoreApplication::translate("MainWindow", "Shows the control panel", nullptr));
#endif // QT_CONFIG(tooltip)
        labelUsePlan->setText(QCoreApplication::translate("MainWindow", "Use Plan:", nullptr));
        labelResT->setText(QCoreApplication::translate("MainWindow", "Result Time:", nullptr));
        labelT->setText(QString());
#if QT_CONFIG(tooltip)
        buttonUsePlan->setToolTip(QCoreApplication::translate("MainWindow", "Forces Yerps to intercept Preys in specified order", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonUsePlan->setText(QString());
#if QT_CONFIG(tooltip)
        buttonBestPlan->setToolTip(QCoreApplication::translate("MainWindow", "Sets interception order to the optimal one", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonBestPlan->setText(QString());
#if QT_CONFIG(tooltip)
        playButton->setToolTip(QCoreApplication::translate("MainWindow", "Starts the animation in Animation mode", nullptr));
#endif // QT_CONFIG(tooltip)
        playButton->setText(QString());
#if QT_CONFIG(tooltip)
        speedUpButton->setToolTip(QCoreApplication::translate("MainWindow", "Speeds up animation by x2, x5, x10, x1", nullptr));
#endif // QT_CONFIG(tooltip)
        speedUpButton->setText(QString());
#if QT_CONFIG(tooltip)
        optionsButton->setToolTip(QCoreApplication::translate("MainWindow", "Shows the control panel", nullptr));
#endif // QT_CONFIG(tooltip)
        optionsButton->setText(QString());
#if QT_CONFIG(tooltip)
        optimalZoomButton->setToolTip(QCoreApplication::translate("MainWindow", "Sets the view to have all Preys and Yerps on it", nullptr));
#endif // QT_CONFIG(tooltip)
        optimalZoomButton->setText(QString());
#if QT_CONFIG(tooltip)
        resetViewButton->setToolTip(QCoreApplication::translate("MainWindow", "Reset view to default", nullptr));
#endif // QT_CONFIG(tooltip)
        resetViewButton->setText(QString());
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
