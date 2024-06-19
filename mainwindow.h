#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QFileDialog>
#include <solver.h>

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
    int signs(double);
    bool isDataReadyToStartProcess();
    void saveDataToFile(FILE*);
    Ui::MainWindow *ui;
    QThread* thread;
    MyQGraphicsView* view;
    Solver* solver;
    bool userHasntSeenOnlyLatinLettersWarning = true;
    bool sliderVsDSBTime = true; // Technical bool which needs to prevent the recursion in changing values of sliderTime and dSBTime

signals:
    void solve(MyQGraphicsView* view);

private slots:
    void solvingEnded();
    void sliderTick();
    void changeProgressBar(long long vC, long long vAll);
    void keyPressEvent(QKeyEvent *) override;
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
    void on_resetZoomButton_clicked();
};
#endif // MAINWINDOW_H
