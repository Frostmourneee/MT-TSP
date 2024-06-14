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
    Ui::MainWindow *ui;
    QThread* thread;
    MyQGraphicsView* view;
    Solver* solver;
    QString preyDataStrSave(double, double, double, double, double, double, int, int, int, int, int, int);
    QString yerpDataStrSave(double, double, int, int);
    int signs(double);
    bool isDataReadyToStartProcess();
    bool userHasntSeenOnlyLatinLettersWarning = true;
    void saveDataToFile(FILE*);
    void disableUIDueToCalcProcess();
    void enableUIAfterCalcProcess();

signals:
    void solve(MyQGraphicsView* view);

private slots:
    void on_actionStart_triggered();
    void keyPressEvent(QKeyEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void on_actionSave_as_triggered();
    void on_actionLoad_from_file_triggered();
    void on_actionClear_triggered();
    void on_actionExit_triggered();
    void on_actionFullscreen_triggered();
    void on_actionRandom_triggered();
    void on_actionBack_triggered();
    void solvingEnded();
};
#endif // MAINWINDOW_H
