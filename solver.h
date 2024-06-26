#ifndef SOLVER_H
#define SOLVER_H

#include <myqgraphicsview.h>

class Solver : public QObject
{
    Q_OBJECT
public:
    Solver(QObject *parent = nullptr) : QObject(parent)
    { }
    double getResT() {return resT;}

signals:
    void solvingEnded();
    void usePlanEnded();
    void changeProgressBar(long long vC, long long vAll); // Vars calculated and vars at all

private:
    double timeOneYerp(double bestT, int* realPlan, int rPSize, int yerpNum, bool shouldIgnoreOptimization);
    double planOneM(double bestT, int* plan, int rPSize, int yerpNum, bool shouldIgnoreOptimization);
    double oneIntercept(int preyNum, int yerpNum);
    void resetOne(int yerpNum);
    void fullReset();
    long long vars(int M, int N);
    long long C(int, int);
    long long fact(int);
    void swap (int *a, int *b);
    void storeInterceptionInfo(MyQGraphicsView* view, int* plan, int rPSize, int yerpNum);
    void freeMallocs();
    int M; // Yerps
    int N; // Preys
    int k1; // 1st optimal plan size
    int k2; // 2nd optimal plan size
    double resT; // Result time
    double* mx; // Current Yerp pos
    double* my;
    double* initmx; // Initial Yerp pos
    double* initmy;
    double* x; // Current Prey pos
    double* y;
    double* vx;
    double* vy;
    double* initx; // Initial Prey pos
    double* inity;
    double* initvx;
    double* initvy;
    int* curPlan; // Best plan for only 1 Yerp
    int* curPlan1; // Best plan for 1st Yerp
    int* curPlan2; // Best plan for 2nd Yerp
    int prevPercent; // For progressBar
    long long vC; // For progressBar, vars calculated
    long long vAll; // For progressBar, vars at all

private slots:
    void solve(MyQGraphicsView*);
    void usePlan(MyQGraphicsView*);
};

#endif // SOLVER_H
