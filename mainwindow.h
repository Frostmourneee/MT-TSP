#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QFileDialog>
#include <solver.h>
#include <QStandardItemModel>
#include <QScrollBar>
#include <QDialogButtonBox>
#include <QFormLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString preyDataStrSave(double, double, double, double, double, double, int, int, int, int, int, int);
    QString yerpDataStrSave(double, double, int, int);
    QString planToRowsRearrangementByYerp();
    QString planToRowsRearrangementByDieTime();
    int signs(double);
    int preyRowWithNum(int);
    bool isDataReadyToUsePlan();
    void saveDataToFile(FILE*);
    void saveTestDataToFile(FILE*);
    void setBestPlanToLineEditUsePlan();
    void initTables();
    void fillFullYerpTable();
    void fillFullPreyTableAfter();
    void preyRowsRearrangement(QString);
    void preyRowsToInit();
    void yerpRowsToInit();
    void createPreyTableItem(Prey*);
    void createYerpTableItem(Yerp*);
    void afterPlanFillTable();
    void enableUIAfterUsePlan();
    void oneTest();
    Ui::MainWindow *ui;
    QThread* thread;
    MyQGraphicsView* view;
    Solver* solver;
    QStandardItemModel* modelPrey;
    QStandardItemModel* modelYerp;
    int testFileNum = -1;
    int testAmount = 0;
    bool userHasntSeenOnlyLatinLettersWarning = true;
    bool sliderVsDSBTime = true; // Technical bool which needs to prevent the recursion in changing values of sliderTime and dSBTime
    bool isWPressed = false;
    bool isAPressed = false;
    bool isSPressed = false;
    bool isDPressed = false;
    bool isTableViewPreyDataChangedByHand = false;
    bool isTableViewYerpDataChangedByHand = false;
    bool addTest = false;


signals:
    void solve(MyQGraphicsView*);
    void usePlan(MyQGraphicsView*);

private slots:
    void solvingEnded();
    void usePlanEnded();
    void sliderTick();
    void changeProgressBar(long long vC, long long vAll);
    void preyWasCreated(bool);
    void yerpWasCreated(bool);
    void fillTableDueToPreyCreation();
    void fillTableDueToYerpCreation();
    void keyPressEvent(QKeyEvent *) override;
    void keyReleaseEvent(QKeyEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void on_actionStart_triggered();
    void on_actionSave_as_triggered();
    void on_actionLoad_from_file_triggered();
    void on_actionExit_triggered();
    void on_actionFullscreen_triggered();
    void on_actionRandom_triggered();
    void on_actionBack_triggered();
    void on_actionClear_triggered();
    void on_rBConstruction_toggled(bool checked);
    void on_dSBTime_valueChanged(double arg1);
    void on_sliderTime_valueChanged(int value);
    void on_playButton_clicked();
    void on_dSBTime_editingFinished() {setFocus();}
    void on_speedUpButton_clicked();
    void on_resetViewButton_clicked();
    void on_actionPlay_triggered();
    void on_actionSpeedUp_triggered();
    void on_actionResetView_triggered();
    void on_optimalZoomButton_clicked();
    void on_actionOptimalZoom_triggered();
    void on_optionsButton_clicked();
    void on_actionShow_triggered();
    void on_buttonUsePlan_clicked();
    void on_buttonBestPlan_clicked();
    void on_actionUsePlan_triggered();
    void on_actionUseBestPlan_triggered();
    void on_checkBoxRandomM_stateChanged(int);
    void on_checkBoxRandomN_stateChanged(int);
    void on_dSpinBoxVelMin_editingFinished();
    void on_dSpinBoxVelMax_editingFinished();
    void on_tableViewPrey_clicked(const QModelIndex &index);
    void on_tableViewYerp_clicked(const QModelIndex &index);
    void on_tableViewYerp_doubleClicked(const QModelIndex &index);
    void on_tableViewPrey_doubleClicked(const QModelIndex &index);
    void on_modelPreyDataChanged(QModelIndex, QModelIndex);
    void on_modelYerpDataChanged(QModelIndex, QModelIndex);
};
#endif // MAINWINDOW_H
