#include "solver.h"

void Solver::solve(MyQGraphicsView* view)
{
    srand(time(NULL));
    clock_t clockBegin = clock();

    resT = 0.;
    M = view->yerp.size();
    N = view->prey.size();
    vC = 0;
    vAll = vars(M, N);
    prevPercent = 0;

    curPlan = (int*)malloc(N*sizeof(int));
    mx = (double*)malloc(M*sizeof(double));
    my = (double*)malloc(M*sizeof(double));
    initmx = (double*)malloc(M*sizeof(double));
    initmy = (double*)malloc(M*sizeof(double));
    for (int i = 0; i < M; i++) // Fill Yerp info
    {
        mx[i] = view->yerp[i]->getStart().x();
        my[i] = view->yerp[i]->getStart().y();
        initmx[i] = mx[i];
        initmy[i] = my[i];
    }

    x = (double*)malloc(N*sizeof(double));
    y = (double*)malloc(N*sizeof(double));
    vx = (double*)malloc(N*sizeof(double));
    vy = (double*)malloc(N*sizeof(double));
    initx = (double*)malloc(N*sizeof(double));
    inity = (double*)malloc(N*sizeof(double));
    initvx = (double*)malloc(N*sizeof(double));
    initvy = (double*)malloc(N*sizeof(double));
    for (int i = 0; i < N; i++) // Fill Prey info
    {
        x[i] = view->prey[i]->getStart().x();
        y[i] = view->prey[i]->getStart().y();
        vx[i] = view->prey[i]->getVx();
        vy[i] = view->prey[i]->getVy();

        initx[i] = x[i];
        inity[i] = y[i];
        initvx[i] = vx[i];
        initvy[i] = vy[i];
    }

    curPlan1 = (int*)malloc(N*sizeof(int));
    curPlan2 = (int*)malloc(N*sizeof(int));
    k1 = 0;
    k2 = 0;

    if (M == 1) {
        for (int i = 0; i < N; i++) curPlan[i] = i;
        resT = timeOneYerp(resT, curPlan, N, 0, false);
        fillIMAndYerpNum(view, curPlan, N, 0); // Filling IMs and yerpNums

        view->yerp[0]->plan.clear();
        view->yerp[0]->plan4AP.clear();
        for (int i = 0; i < N; i++) {view->yerp[0]->plan.push_back(curPlan[i]); view->yerp[0]->plan4AP.push_back(curPlan[i]);}

        free(x);
        free(y);
        free(vx);
        free(vy);
        free(mx);
        free(my);
        free(initmx);
        free(initmy);
        free(initx);
        free(inity);
        free(initvx);
        free(initvy);
        free(curPlan);
        free(curPlan1);
        free(curPlan2);

        emit solvingEnded();

        clock_t clockEnd = clock();
        qDebug("Time spent: %lf\n", (double)(clockEnd-clockBegin)/CLOCKS_PER_SEC);
        return;
    } // else M == 2

    double mTourTime[M];
    int planFirst[N];
    for (int i = 0; i < N; i++) planFirst[i] = i;

    view->yerp[0]->plan4AP.clear();
    view->yerp[1]->plan4AP.clear();
    for (int i = 0; i < M; i++) { // Worth only if initial Yerps positions are not the same
        mTourTime[i] = timeOneYerp(resT, planFirst, N, i, true);
        for (int j = 0; j < N; j++) view->yerp[i]->plan4AP.push_back(planFirst[j]);
        if (resT == 0) {
            resT = mTourTime[i];
            k1 = N;
            k2 = 0;
            fillIMAndYerpNum(view, planFirst, N, 0);
            for (int j = 0; j < N; j++) {curPlan1[j] = planFirst[j]; curPlan[j] = planFirst[j];}
        } else if (resT > mTourTime[i]) {
            resT = mTourTime[i];
            k1 = 0;
            k2 = N;
            fillIMAndYerpNum(view, planFirst, N, 1);
            for (int j = 0; j < N; j++) {curPlan2[j] = planFirst[j]; curPlan[j] = planFirst[j];}
        }
        for (int i = 0; i < N; i++) {planFirst[i] = i;} // Roll back to init
    } // Catch if the optimal case is the case when 1 Yerp should intercept all Preys, another - zero

    int nums[N]; // Array 0,1,...,N-1
    for (int i = 0; i < N; i++) nums[i] = i; // Initial fill
    int planFirstSize;
    int planSecondSize;

    int n = pow(2, N);
    for (int i = 0; i < n; i++) // Generation of 2^n variants
    {
        planFirstSize = 0;
        for (int j = 0; j < N; j++)
            if (i & (1 << j)) planFirstSize++;// If j-th bit is 1

        if (planFirstSize == 0 || planFirstSize == N) continue;
        planSecondSize = N - planFirstSize;

        int planFirst[planFirstSize];
        int planSecond[planSecondSize];
        planFirstSize = 0;
        planSecondSize = 0;
        for (int j = 0; j < N; j++) if (i & (1 << j)) {
            planFirstSize++;
            planFirst[planFirstSize-1] = nums[j];
        } else {
            planSecondSize++;
            planSecond[planSecondSize-1] = nums[j];
        } // Both plans and their sizes were generated

        mTourTime[0] = timeOneYerp(resT, planFirst, planFirstSize, 0, false);
        mTourTime[1] = timeOneYerp(resT, planSecond, planSecondSize, 1, false);

        if (resT > fmax(mTourTime[0], mTourTime[1])) {
            resT = fmax(mTourTime[0], mTourTime[1]);
            k1 = planFirstSize;
            k2 = planSecondSize;
            free(curPlan1);
            free(curPlan2);
            curPlan1 = (int*)malloc(k1*sizeof(int));
            curPlan2 = (int*)malloc(k2*sizeof(int));

            for (int j = 0; j < k1; j++) curPlan1[j] = planFirst[j];
            for (int j = 0; j < k2; j++) curPlan2[j] = planSecond[j];
        }
    }

    //Block to fill IM1 & IM2 and some other interception stuff
    fillIMAndYerpNum(view, curPlan1, k1, 0);
    fillIMAndYerpNum(view, curPlan2, k2, 1);
    view->yerp[0]->plan.clear();
    view->yerp[1]->plan.clear();
    for (int i = 0; i < k1; i++) view->yerp[0]->plan.push_back(curPlan1[i]);
    for (int i = 0; i < k2; i++) view->yerp[1]->plan.push_back(curPlan2[i]);

    free(x);
    free(y);
    free(vx);
    free(vy);
    free(mx);
    free(my);
    free(initmx);
    free(initmy);
    free(initx);
    free(inity);
    free(initvx);
    free(initvy);
    free(curPlan);
    free(curPlan1);
    free(curPlan2);

    emit solvingEnded();

    clock_t clockEnd = clock();
    qDebug("Time spent: %lf\n", (double)(clockEnd-clockBegin)/CLOCKS_PER_SEC);
}

double Solver::timeOneYerp(double bestT, int *realPlan, int rPSize, int yerpNum, bool shouldIgnoreOptimization)
{
    double T = 0.; // Result time

    //Поиск всех перестановок начинается
    int initRealPlan[rPSize];
    int planIndex[rPSize];
    int plan[rPSize];
    int it1, it2;
    for (it1 = 0; it1 < rPSize; it1++) {
        planIndex[it1] = it1;
        plan[it1] = realPlan[it1];
        initRealPlan[it1] = realPlan[it1];
    } // Initial filling

    while (1) { // Complete search - every plan trying
        for (int i = 0; i < rPSize; i++) plan[i] = initRealPlan[planIndex[i]];

        double tmpT = planOneM(bestT, plan, rPSize, yerpNum, shouldIgnoreOptimization);
        if (T == 0. || tmpT < T) {
            T = tmpT;
            bestT = T;
            for (int i = 0; i < rPSize; i++) realPlan[i] = plan[i];
        }
        resetOne(yerpNum);

        // Generates all the permutations
        for (it1=rPSize-2; it1>=0 && planIndex[it1] > planIndex[it1+1]; it1--) ;
        if (it1<0) break;
        for (it2=rPSize-1; planIndex[it1] > planIndex[it2]; it2--) ;
        swap(&planIndex[it1], &planIndex[it2]);
        for (int it4=it1+1, it3=rPSize-1; it3 > it4; it4++, it3--) swap(&planIndex[it3], &planIndex[it4]);
    }

    return T;
}
double Solver::planOneM(double bestT, int *plan, int rPSize, int yerpNum, bool shouldIgnoreOptimization)
{
    vC++;
    if ((int) ((double)vC / vAll * 100) != prevPercent) emit changeProgressBar(vC, vAll);
    prevPercent = (int) ((double)vC / vAll * 100);

    double T = 0.;

    for(int i = 0; i < rPSize; i++) {
        T += oneIntercept(plan[i], yerpNum);
        if (bestT != 0. && T > bestT && !shouldIgnoreOptimization) {
            fullReset();
            return bestT + 1; // Because found T comes greater than bestT
        }
    }

    fullReset();
    return T;
}
double Solver::oneIntercept(int preyNum, int yerpNum)
{
    double deltaX = x[preyNum] - mx[yerpNum];
    double deltaY = y[preyNum]- my[yerpNum];
    double r0sqr = pow(deltaX, 2) + pow(deltaY, 2);
    double v0sqr = pow(vx[preyNum], 2) + pow(vy[preyNum], 2);
    double dotprodr0v0 = vx[preyNum]*deltaX + vy[preyNum]*deltaY;

    double t = (dotprodr0v0 + sqrt(dotprodr0v0*dotprodr0v0 - r0sqr*(v0sqr-1)))/(1-v0sqr);
    mx[yerpNum] += deltaX + vx[preyNum]*t;
    my[yerpNum] += deltaY + vy[preyNum]*t;
    x[preyNum] = mx[yerpNum];
    y[preyNum] = my[yerpNum];
    vx[preyNum] = 0.;
    vy[preyNum] = 0.;

    for (int i = 0; i < N; i++) {
        if (i != preyNum) {
            x[i] += vx[i]*t;
            y[i] += vy[i]*t;
        }
    }

    return t;
}
void Solver::resetOne(int yerpNum)
{
    mx[yerpNum] = initmx[yerpNum];
    my[yerpNum] = initmy[yerpNum];

    for (int i = 0; i < N; i++) {x[i] = initx[i]; y[i] = inity[i]; vx[i] = initvx[i]; vy[i] = initvy[i];}
}
void Solver::fullReset()
{
    for (int i = 0; i < M; i++) {mx[i] = initmx[i]; my[i] = initmy[i];}
    for (int i = 0; i < N; i++) {x[i] = initx[i]; y[i] = inity[i]; vx[i] = initvx[i]; vy[i] = initvy[i];}
}
void Solver::fillIMAndYerpNum(MyQGraphicsView* view, int *plan, int rPSize, int yerpNum)
{
    double T = 0.;

    for(int i = 0; i < rPSize; i++) {
        T += oneIntercept(plan[i], yerpNum);
        view->prey[plan[i]]->setDieTime(QString::number(T, 'f', 2).toDouble());
        view->prey[plan[i]]->setYerpNum(yerpNum);
    }

    fullReset();
}

long long Solver::vars(int M, int N)
{
    long long res = 0;

    if (M == 1) res = fact(N);
    else if (M == 2) {
        for (int i = 0; i <= N; i++) res += C(N, i)*(fact(i)+fact(N-i));
    }

    return res;
}
long long Solver::C(int n, int k)
{
    if (k > n - k) k = n - k;

    long long tmpProd = 1;
    for (int i = 0; i < k; i++) tmpProd *= (n-i);

    return tmpProd / fact(k);
}
long long Solver::fact(int N)
{
    long long res = 1;
    for (int i = 2; i <= N; i++) res *= i;

    return res;
}
void Solver::swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
