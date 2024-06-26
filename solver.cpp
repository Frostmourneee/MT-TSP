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

    Yerp* y1 = view->yerp[0];
    if (M == 1) {
        for (int i = 0; i < N; i++) curPlan[i] = i;
        resT = N <= 3 ? timeOneYerpBase(N, curPlan, 0) : timeOneYerp(N, curPlan, 0);
        storeInterceptionInfo(view, curPlan, N, 0); // Filling IMs and yerpNums

        y1->bestPlan.clear();
        y1->plan4AP.clear();
        y1->curPlan.clear();
        for (int i = 0; i < N; i++) {y1->bestPlan.push_back(curPlan[i]); y1->plan4AP.push_back(curPlan[i]); y1->curPlan.push_back(curPlan[i]);}
        y1->setPlan4APTime(resT);

        freeMallocs();
        emit solvingEnded();

        clock_t clockEnd = clock();
        qDebug("Time spent: %lf\n", (double)(clockEnd-clockBegin)/CLOCKS_PER_SEC);
        return;
    } // else M == 2

    int nums[N];
    for (int i = 0; i < N; i++) nums[i] = i;
    int p1S, p2S, bestP1S, bestP2S;
    int bestP1[N];
    int bestP2[N];
    double tmpT1, tmpT2, tmpT;

    Yerp* y2 = view->yerp[1];
    y1->plan4AP.clear();
    y2->plan4AP.clear();

    long int n = pow(2, N);
    for (int i = 0; i < n; i++)
    {
        p1S = 0;
        for (int j = 0; j < N; j++)
            if (i & (1 << j)) p1S++;

        p2S = N - p1S;

        int p1[p1S];
        int p2[p2S];
        p1S = 0;
        p2S = 0;
        for (int j = 0; j < N; j++) {
            if (i & (1 << j)) {
                p1[p1S] = nums[j];
                p1S++;
            } else {
                p2[p2S] = nums[j];
                p2S++;
            }
        }

        tmpT1 = p1S <= 3 ? timeOneYerpBase(p1S, p1, 0) : timeOneYerp(p1S, p1, 0);
        tmpT2 = p2S <= 3 ? timeOneYerpBase(p2S, p2, 1) : timeOneYerp(p2S, p2, 1);
        tmpT = fmax(tmpT1, tmpT2);

        if (resT > tmpT || resT == 0.)
        {
            resT = tmpT;
            bestP1S = p1S;
            bestP2S = p2S;

            for (int j = 0; j < bestP1S; j++) bestP1[j] = p1[j];
            for (int j = 0; j < bestP2S; j++) bestP2[j] = p2[j];
        }

        if (p2S == N) {
            tmpT1 = N <= 3 ? timeOneYerpBase(N, p2, 0) : timeOneYerp(N, p2, 0);
            y1->setPlan4APTime(tmpT1);
            for (int j = 0; j < N; j++) y1->plan4AP.push_back(p2[j]);
            tmpT2 = N <= 3 ? timeOneYerpBase(N, p2, 1) : timeOneYerp(N, p2, 1);
            y2->setPlan4APTime(tmpT2);
            for (int j = 0; j < N; j++) y2->plan4AP.push_back(p2[j]);
        }
    }

    k1 = bestP1S;
    k2 = bestP2S;
    for (int j = 0; j < k1; j++) curPlan1[j] = bestP1[j];
    for (int j = 0; j < k2; j++) curPlan2[j] = bestP2[j];

    //Block to fill IM1 & IM2 and some other interception stuff
    storeInterceptionInfo(view, curPlan1, k1, 0);
    storeInterceptionInfo(view, curPlan2, k2, 1);
    y1->bestPlan.clear();
    y2->bestPlan.clear();
    y1->curPlan.clear();
    y2->curPlan.clear();
    for (int i = 0; i < k1; i++) {y1->bestPlan.push_back(curPlan1[i]); y1->curPlan.push_back(curPlan1[i]);}
    for (int i = 0; i < k2; i++) {y2->bestPlan.push_back(curPlan2[i]); y2->curPlan.push_back(curPlan2[i]);}

    freeMallocs();
    emit solvingEnded();

    clock_t clockEnd = clock();
    qDebug("Time spent: %lf\n", (double)(clockEnd-clockBegin)/CLOCKS_PER_SEC);
}
void Solver::usePlan(MyQGraphicsView *view)
{
    M = view->yerp.size();
    N = view->prey.size();

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

    int k1 = view->yerp[0]->curPlan.size();
    int k2 = 0;
    if (M == 2) k2 = view->yerp[1]->curPlan.size();
    int p1[k1];
    int p2[k2];
    for (int i = 0; i < k1; i++) p1[i] = view->yerp[0]->curPlan[i];
    for (int i = 0; i < k2; i++) p2[i] = view->yerp[1]->curPlan[i];

    storeInterceptionInfo(view, p1, k1, 0);
    if (M == 2) storeInterceptionInfo(view, p2, k2, 1);

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
    emit usePlanEnded();
}

double Solver::timeOneYerp(int N, int *realPlan, int yerpNum)
{
    double T = 0.; //Суммарное время

    long int prevDiffCombs = C(N, 3);
    long int prevAHeight = prevDiffCombs*3;

    double* prevMx = (double*)malloc(prevAHeight*sizeof(double));
    double* prevMy = (double*)malloc(prevAHeight*sizeof(double));
    double* prevT = (double*)malloc(prevAHeight*sizeof(double));

    int** prevLA = (int**)malloc(prevAHeight*sizeof(int*));
    for (int i = 0; i < prevAHeight; i++) prevLA[i] = (int*)malloc(3*sizeof(int));

    int** prevRA = (int**)malloc(prevAHeight*sizeof(int*));
    for (int i = 0; i < prevAHeight; i++) prevRA[i] = (int*)malloc((N-3)*sizeof(int));

    int subset;
    int initComb[3];
    int cs = 0; //actual combAHeight

    int comb[N];
    for (int i = 0; i < N; i++) comb[i] = realPlan[i];
    prevAHeight = 0;
    prevDiffCombs = 0;
    for (subset = (1 << 3) - 1; subset < (1 << N); subset = next_combination(subset))
    {
      int bit, i;
      cs = 0;

      for (bit = 1, i = 0; bit < (1 << N); bit <<= 1, ++i)
        if ((subset & bit) != 0) {
            initComb[cs] = realPlan[i];
            int num = 0;
            while (comb[num] != initComb[cs]) num++;
            swapp(&comb[num], &comb[cs]);
            cs++;
        }

      for (int i = 0; i < 3; i++) {
          prevT[prevAHeight] = timeOnePredWFixedEnd(3, comb, yerpNum, initComb[i]);
          prevMx[prevAHeight] = initx[comb[2]] + initvx[comb[2]]*prevT[prevAHeight];
          prevMy[prevAHeight] = inity[comb[2]] + initvy[comb[2]]*prevT[prevAHeight];
          for (int j = 0; j < 3; j++) prevLA[prevAHeight][j] = comb[j];
          for (int j = 0; j < (N-3); j++) prevRA[prevAHeight][j] = comb[3 + j];
          prevAHeight++;
      }
      prevDiffCombs++;
    }

    for (int n = 3; n < N; n++)
    {
        long int AHeight = C(N, n+1)*(n+1);

        double* mx = (double*)malloc(AHeight*sizeof(double));
        double* my = (double*)malloc(AHeight*sizeof(double));
        double* t = (double*)malloc(AHeight*sizeof(double));

        int** lA = (int**)malloc(AHeight*sizeof(int*));
        for (int i = 0; i < AHeight; i++) lA[i] = (int*)malloc((n+1)*sizeof(int));

        int** rA = (int**)malloc(AHeight*sizeof(int*));
        for (int i = 0; i < AHeight; i++) rA[i] = (int*)malloc((N-(n+1))*sizeof(int));

        long int clusters = prevAHeight/n;
        for (int i = 0; i < clusters; i++) { //По кластеру из n штук-строк
            for (int j = 0; j < N-n; j++) { //По каждой новой цифре
                double goodT = 0.;
                double tmpT = 0.;
                int goodK = 0;
                for (int k = 0; k < n; k++) {//По каждой из этих n строк
                    tmpT = prevT[n*i+k] + shiftTime(prevRA[n*i+k][j], prevMx[n*i+k], prevMy[n*i+k], prevT[n*i+k]);

                    if (tmpT < goodT || goodT == 0.) {
                        goodT = tmpT;
                        goodK = k;
                    }
                }

                t[(N-n)*i + j] = goodT;
                mx[(N-n)*i + j] = initx[prevRA[n*i][j]] + initvx[prevRA[n*i][j]]*goodT;
                my[(N-n)*i + j] = inity[prevRA[n*i][j]] + initvy[prevRA[n*i][j]]*goodT;
                for (int k = 0; k < n; k++) lA[(N-n)*i + j][k] = prevLA[n*i + goodK][k];
                lA[(N-n)*i + j][n] = prevRA[n*i + goodK][j];
                for (int k = 0; k < N-(n+1); k++) rA[(N-n)*i + j][k] = prevRA[n*i + goodK][k < j ? k : k+1];
            }
        }
        if (N-n-1 > 0) rearrange(AHeight, N, realPlan, &lA, &rA, n+1, &t, &mx, &my);

        if (N-n-1 > 1) { //Копирование набора после разделителя
            for (int i = 0; i < AHeight/(n+1); i++) {
                for (int j = 1; j < n+1; j++) {
                    for (int k = 0; k < N-(n+1); k++) {
                        rA[i*(n+1) + j][k] = rA[i*(n+1)][k];
                    }
                }
            }
        }

        free(prevT);
        free(prevMx);
        free(prevMy);
        prevT = t;
        prevMx = mx;
        prevMy = my;

        for (int i = 0; i < prevAHeight; i++) free(prevLA[i]);
        free(prevLA);
        prevLA = lA;
        for (int i = 0; i < AHeight; i++) prevLA[i] = lA[i];

        for (int i = 0; i < prevAHeight; i++) free(prevRA[i]);
        free(prevRA);
        prevRA = rA;
        for (int i = 0; i < AHeight; i++) prevRA[i] = rA[i];
        prevAHeight = AHeight;
    }

    double tmpT[prevAHeight];
    int bestPlan = 0;
    for (int i = 0; i < prevAHeight; i++) {
        tmpT[i] = planOneM(N, prevLA[i], yerpNum);

        if (T > tmpT[i] || T == 0.) {
            T = tmpT[i];
            bestPlan = i;
        }
    }

    for (int i = 0; i < N; i++) realPlan[i] = prevLA[bestPlan][i];

    free(prevT);
    free(prevMx);
    free(prevMy);
    for (int i = 0; i < prevAHeight; i++) {free(prevLA[i]); free(prevRA[i]);}
    free(prevLA);
    free(prevRA);

    return T;
}
double Solver::timeOneYerpBase(int rPSize, int *realPlan, int yerpNum)
{
    double T = 0.;

    double tmpT;
    int initRealPlan[rPSize];
    int planIndex[rPSize];
    int plan[rPSize];

    int it1, it2;
    for (it1 = 0; it1 < rPSize; it1++)
    {
        planIndex[it1] = it1;
        plan[it1] = realPlan[it1];
        initRealPlan[it1] = realPlan[it1];
    }

    while (1)   //Полный перебор
    {
        for (int i = 0; i < rPSize; i++) plan[i] = initRealPlan[planIndex[i]];

        tmpT = planOneM(rPSize, plan, yerpNum);

        if (T == 0. || tmpT < T)
        {
            T = tmpT;
            for (int i = 0; i < rPSize; i++) realPlan[i] = plan[i];
        }
        resetOne(yerpNum);

        // Находим самое правое место, где s[i] < s[i+1]
        for (it1=rPSize-2; it1>=0 && planIndex[it1] > planIndex[it1+1]; it1--) ;       // Тело цикла пустое
        if (it1<0) break; // Уже получили "10-9-8-7-6-5-4-3-2-1" - самую старшую перестановку

        // Находим s[j] - наименьший элемент справа от s[i] и больший его
        for (it2=rPSize-1; planIndex[it1] > planIndex[it2]; it2--) ;       // Тело цикла пустое
        // Меняем s[i] <-> s[j]
        swapp(&planIndex[it1], &planIndex[it2]);
        // Переворачиваем то, что справа от "i"
        for (int it4=it1+1, it3=rPSize-1; it3 > it4; it4++, it3--) swapp(&planIndex[it3], &planIndex[it4]);
    }

    return T;
}
double Solver::timeOnePredWFixedEnd(int N, int *realPlan, int pred, int end)
{
    double T = 0.; //Суммарное время
    double tmpT;

    //Поиск всех перестановок начинается
    int initRealPlan[N-1];
    int planIndex[N-1];
    int planWEnd[N];

    int num = 0;
    for (int i = 0; i < N; i++) if (realPlan[i] == end) num = i;
    swapp(&realPlan[num], &realPlan[N-1]);

    int it1, it2;
    for (it1 = 0; it1 < N-1; it1++)
    {
        planIndex[it1] = it1;
        planWEnd[it1] = realPlan[it1];
        initRealPlan[it1] = realPlan[it1];
    } //Начальное заполнение

    while (1)   //Полный перебор
    {
        for (int i = 0; i < N-1; i++) planWEnd[i] = initRealPlan[planIndex[i]];
        planWEnd[N-1] = realPlan[N-1];

        tmpT = planOneM(N, planWEnd, pred);

        if (T == 0. || tmpT < T)
        {
            T = tmpT;
            for (int i = 0; i < N-1; i++) realPlan[i] = planWEnd[i];
        }
        resetOne(pred);

        // Находим самое правое место, где s[i] < s[i+1]
        for (it1=N-3; it1>=0 && planIndex[it1] > planIndex[it1+1]; it1--) ;       // Тело цикла пустое
        if (it1<0) break; // Уже получили "10-9-8-7-6-5-4-3-2-1" - самую старшую перестановку

        // Находим s[j] - наименьший элемент справа от s[i] и больший его
        for (it2=N-2; planIndex[it1] > planIndex[it2]; it2--) ;       // Тело цикла пустое
        // Меняем s[i] <-> s[j]
        swapp(&planIndex[it1], &planIndex[it2]);
        // Переворачиваем то, что справа от "i"
        for (int it4=it1+1, it3=N-2; it3 > it4; it4++, it3--) swapp(&planIndex[it3], &planIndex[it4]);
    }

    return T;
}
double Solver::planOneM(int rPSize, int *plan, int yerpNum)
{
    vC++;
    if ((int) ((double)vC / vAll * 100) != prevPercent) emit changeProgressBar(vC, vAll);
    prevPercent = (int) ((double)vC / vAll * 100);

    double T = 0.;
    for(int i = 0; i < rPSize; i++)
    {
        T += oneIntercept(plan[i], yerpNum);
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
double Solver::shiftTime(int prey, double mx, double my, double prevT)
{
    double preyX = initx[prey] + initvx[prey]*prevT;
    double preyY = inity[prey] + initvy[prey]*prevT;

    double deltaX = preyX - mx;
    double deltaY = preyY - my;
    double r0sqr = pow(deltaX, 2) + pow(deltaY, 2);
    double v0sqr = pow(initvx[prey], 2) + pow(initvy[prey], 2);
    double dotprodr0v0 = initvx[prey]*deltaX + initvy[prey]*deltaY;

    double t = (dotprodr0v0 + sqrt(dotprodr0v0*dotprodr0v0 - r0sqr*(v0sqr-1)))/(1-v0sqr);

    return t;
}
void Solver::rearrange(long int M, int N, int* realPlan, int ***lA, int ***rA, int n, double** t, double** mx, double** my)
{
    long int* existingHashes = (long int*)malloc(M/n*sizeof(long int));
    long int eHashesSize = 0;

    int num[N];
    for (int i = 0; i < N; i++) num[i] = realPlan[i];
    int subset;
    int bs;
    for (subset = (1 << n) - 1; subset < (1 << N); subset = next_combination(subset))
    {
      int bit, i;

      int bits[n];
      bs = 0;

      for (bit = 1, i = 0; bit < (1 << N); bit <<= 1, ++i)
        if ((subset & bit) != 0) {
            bits[bs] = num[i];
            bs++;
        }

      long int na = 0;
      for (int j = 0; j < n; j++) na += pow(2, bits[j]);

      existingHashes[eHashesSize] = na;
      eHashesSize++;
    }

    long int BHeight = 0;
    for (int i = 1; i <= n; i++) BHeight += pow(2, this->N-i);
    long int** B = (long int**)malloc(BHeight*sizeof(long int*));
    for (long int i = 0; i < BHeight; i++) B[i] = (long int*)malloc(n*sizeof(int));
    long int* currentBLength = (long int*)malloc(BHeight*sizeof(BHeight));
    for (int i = 0; i < BHeight; i++) currentBLength[i] = 0;
    for (int i = 0; i < M; i++) {
        B[bitSet(n, (*lA)[i])-1][currentBLength[bitSet(n, (*lA)[i])-1]] = i;
        currentBLength[bitSet(n, (*lA)[i])-1]++;
    }
    free(currentBLength);

    double* tmpT = (double*)malloc(M*sizeof(double));
    double* tmpMx = (double*)malloc(M*sizeof(double));
    double* tmpMy = (double*)malloc(M*sizeof(double));

    int** tmpLA = (int**)malloc(M*sizeof(int*));
    int** tmpRA = (int**)malloc(M*sizeof(int*));
    for (int i = 0; i < eHashesSize; i++) {
        for (int j = 0; j < n; j++) {
            tmpT[n*i+j] = (*t)[B[existingHashes[i]-1][j]];
            tmpMx[n*i+j] = (*mx)[B[existingHashes[i]-1][j]];
            tmpMy[n*i+j] = (*my)[B[existingHashes[i]-1][j]];

            tmpLA[n*i+j] = (*lA)[B[existingHashes[i]-1][j]];
            tmpRA[n*i+j] = (*rA)[B[existingHashes[i]-1][j]];
        }
    }
    free(existingHashes);

    for (long int i = 0; i < BHeight; i++) free(B[i]);
    free(B);

    free((*t));
    free((*mx));
    free((*my));
    free((*lA));
    free((*rA));
    (*t) = tmpT;
    (*mx) = tmpMx;
    (*my) = tmpMy;
    (*lA) = tmpLA;
    (*rA) = tmpRA;
}
long int Solver::bitSet(int N, int* a)
{
    long int na = 0;
    for (int i = 0; i < N; i++) na += pow(2, a[i]);

    return na;
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
void Solver::storeInterceptionInfo(MyQGraphicsView* view, int *plan, int rPSize, int yerpNum)
{
    if (rPSize == 0) return;
    double T = 0.;

    for(int i = 0; i < rPSize; i++) {
        T += oneIntercept(plan[i], yerpNum);

        Prey* p = view->prey[plan[i]];
        p->setDieTime(QString::number(T, 'f', 2).toDouble());
        p->setYerpNum(yerpNum);
    }

    Yerp* y = view->yerp[yerpNum];
    y->firstPrey = view->prey[plan[0]];
    y->lastPrey = view->prey[plan[rPSize-1]];

    fullReset();
}

long long Solver::vars(int M, int N)
{
    long long res = 0;

    if (M == 1)
    {
        switch (N) {
        case 1:
            res = 1;
            break;
        case 2:
            res = 2;
            break;
        case 3:
            res = 6;
            break;
        case 4:
            res = 28;
            break;
        case 5:
            res = 65;
            break;
        case 6:
            res = 126;
            break;
        case 7:
            res = 217;
            break;
        case 8:
            res = 344;
            break;
        case 9:
            res = 513;
            break;
        case 10:
            res = 730;
            break;
        case 11:
            res = 1001;
            break;
        case 12:
            res = 1332;
            break;
        case 13:
            res = 1729;
            break;
        case 14:
            res = 2198;
            break;
        case 15:
            res = 2745;
            break;
        case 16:
            res = 3376;
            break;
        case 17:
            res = 4097;
            break;
        case 18:
            res = 4914;
            break;
        case 19:
            res = 5833;
            break;
        case 20:
            res = 6916;
            break;
        }
    }
    else
    {
        switch (N) {
        case 1:
            res = 6;
            break;
        case 2:
            res = 14;
            break;
        case 3:
            res = 44;
            break;
        case 4:
            res = 194;
            break;
        case 5:
            res = 712;
            break;
        case 6:
            res = 2438;
            break;
        case 7:
            res = 7842;
            break;
        case 8:
            res = 23906;
            break;
        case 9:
            res = 69644;
            break;
        case 10:
            res = 195302;
            break;
        case 11:
            res = 530422;
            break;
        case 12:
            res = 1402178;
            break;
        case 13:
            res = 3622608;
            break;
        case 14:
            res = 9177254;
            break;
        }
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
void Solver::swapp(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int Solver::next_combination(int x)
{
  int u = x & -x;
  int v = u + x;
  x = v  + (((v ^ x) / u) >> 2);
  return x;
}
void Solver::freeMallocs()
{
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
}
