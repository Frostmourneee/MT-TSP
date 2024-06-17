#include "mainwindow.h"
#include "ui_mainwindow.h"

//TODO Zoom
//TODO подумать над плавностью смены сотых долей в координатах
//TODO из-за симметрий быть может можно перебор уменьшить когда M = 2
//TODO тесты
//TODO сортировка по иксам работает?
//TODO нельзя задать план из двузначной цели
//TODO позволить при большом N не искать оптимум, а просто летать
//TODO при M = 2 в графе идеального плана для одного считает видимо лучший для облёта именно первым! Если из разных точек стартуют, то может вторым лучше

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMinimumSize(QSize(800, 600));
    resize(QSize(800, 600));

    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);

    view = new MyQGraphicsView(this);
    ui->vLScene->insertWidget(0, view);
    view->genRect->setRect(QRectF(20, 20, 1318, 773));
    view->setFocus();

    thread = new QThread(this);
    connect(this, SIGNAL(destroyed()), thread, SLOT(quit()));

    solver = new Solver();
    connect(this, SIGNAL(solve(MyQGraphicsView*)), solver, SLOT(solve(MyQGraphicsView*)));
    connect(solver, SIGNAL(solvingEnded()), this, SLOT(solvingEnded()));
    connect(solver, SIGNAL(changeProgressBar(long long, long long)), this, SLOT(changeProgressBar(long long, long long)));
    solver->moveToThread(thread);

    ui->progressBar->setStyleSheet("text-align: center");
    ui->playButton->setIcon(QIcon("playIcon.png"));
    ui->speedUpButton->setIcon(QIcon("speedUpIcon.png"));

    connect(view->timer, SIGNAL(timeout()), this, SLOT(sliderTick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
        case Qt::Key_I:
        case 1064: {
            if (!e->modifiers().testFlag(Qt::ControlModifier)) return; // +Ctrl pressed

            view->info();
            break;
        }

    case Qt::Key_T: // Test key
        {

            break;
        }
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent * e) {
    Q_UNUSED(e);

    view->setVisibleText(false);
}

void MainWindow::on_actionClear_triggered()
{
    setFocus();

    view->clear();
    view->genRect->show();
    ui->rBConstruction->setChecked(true);
    ui->rBAnimation->setEnabled(false);
    ui->dSBTime->setValue(0);
    ui->sliderTime->setValue(0);
    ui->playButton->setIcon(QIcon("playIcon.png"));
    ui->playButton->setEnabled(false);
    ui->speedUpButton->setIcon(QIcon("speedUpIcon.png"));
    ui->speedUpButton->setEnabled(false);

    QPointF pMathCursorPos = view->sceneToCoords(view->mapFromGlobal(QCursor::pos()));
    double x = pMathCursorPos.x();
    double y = pMathCursorPos.y();
    view->textCoords(x + 0.02, y - 0.02);
    view->timer->start(10);
}
void MainWindow::on_actionExit_triggered()
{
    exit(0);
}
void MainWindow::on_actionFullscreen_triggered()
{
    setFocus();
    if (isMaximized()) showNormal();
    else showMaximized();
}
void MainWindow::on_actionRandom_triggered()
{
    QRectF genRect = view->genRect->rect();
    QPointF genLeft = view->sceneToCoords(QPointF(genRect.x(), genRect.y()));
    QPointF genRight = view->sceneToCoords(QPointF(genRect.x()+genRect.width(), genRect.y()+genRect.height()));
    double xmax = QString::number(genRight.x(), 'f', 2).toDouble();
    double xmin = QString::number(genLeft.x(), 'f', 2).toDouble();
    double ymax = QString::number(genLeft.y(), 'f', 2).toDouble();
    double ymin = QString::number(genRight.y(), 'f', 2).toDouble();
    double maxVel1f = 7;
    double minVel1f = 0;

    if (xmax <= xmin || ymax <= ymin) {
        QMessageBox::critical(this, "MT-TSP", "Invalid generation bounds\n");
        return;
    }

    on_actionClear_triggered();
    srand(time(NULL));
    int M = rand()%2 + 1;
    int N = rand()%12 + 1;

    int parts;
    double r2fValue, x, y, v, xEnd, yEnd;
    for (int i = 0; i < M; i++) // Yerps generation
    {
        parts = (xmax-xmin)*100;
        r2fValue = xmin + rand()%(parts + 1)*0.01;
        if (r2fValue > xmax) r2fValue = xmax;
        else if (r2fValue < xmin) r2fValue = xmin;
        x = r2fValue;

        parts = (ymax-ymin)*100;
        r2fValue = ymin + rand()%(parts + 1)*0.01;
        if (r2fValue > ymax) r2fValue = ymax;
        else if (r2fValue < ymin) r2fValue = ymin;
        y = r2fValue;

        view->createYerp(QPointF(x, y));
    }

    for (int i = 0; i < N; i++) // Preys generation
    {
        parts = (xmax-xmin)*100;
        r2fValue = xmin + rand()%(parts + 1)*0.01;
        if (r2fValue > xmax) r2fValue = xmax;
        else if (r2fValue < xmin) r2fValue = xmin;
        x = r2fValue;

        parts = (ymax-ymin)*100;
        do
        {
            r2fValue = ymin + rand()%(parts + 1)*0.01;
            if (r2fValue > ymax) r2fValue = ymax;
            else if (r2fValue < ymin) r2fValue = ymin;
            y = r2fValue;
        }
        while (M == 1 ? QPointF(x, y) == view->yerp[0]->getStart() :
                        (QPointF(x, y) == view->yerp[0]->getStart() || QPointF(x, y) == view->yerp[1]->getStart()));   // No need for Prey to start from the same position as Yerp

        parts = (xmax-xmin)*100;
        r2fValue = xmin + rand()%(parts + 1)*0.01;
        if (r2fValue > xmax) r2fValue = xmax;
        else if (r2fValue < xmin) r2fValue = xmin;
        xEnd = r2fValue;

        parts = (ymax-ymin)*100;
        r2fValue = ymin + rand()%(parts + 1)*0.01;
        if (r2fValue > ymax) r2fValue = ymax;
        else if (r2fValue < ymin) r2fValue = ymin;
        yEnd = r2fValue;

        parts = (maxVel1f-minVel1f)*10;
        r2fValue = minVel1f*0.1 + rand()%(parts + 1)*0.01;
        v = r2fValue;
        if (r2fValue >= maxVel1f*0.1) v = maxVel1f*0.1;

        view->createPreyOnFullInfo(QPointF(x, y), QPointF(xEnd, yEnd), v);
    }
}
void MainWindow::on_actionStart_triggered()
{
    setFocus();
    if (!isDataReadyToStartProcess()) return;

    view->setEnabled(false);
    view->setStatus(StatusScene::disabled);
    ui->actionClear->setEnabled(false);
    ui->actionLoad_from_file->setEnabled(false);
    ui->rBConstruction->setEnabled(false);
    ui->rBAnimation->setChecked(true);
    ui->actionStart->setEnabled(false);
    ui->actionRandom->setEnabled(false);
    ui->actionBack->setEnabled(false);
    view->setVisibleText(false);
    view->genRect->hide();

    FILE* initDataFile = fopen("initData.txt", "w+"); // Saving all the data to the default "initData.txt" file
    saveDataToFile(initDataFile);

    thread->start();
    emit solve(view);

}
void MainWindow::on_actionBack_triggered()
{
    setFocus();
    view->backAction();
}
void MainWindow::on_actionSave_as_triggered()
{
    setFocus();
    if (!isDataReadyToStartProcess()) return;

    if (userHasntSeenOnlyLatinLettersWarning)
    {
        QMessageBox::information(this, "MT-TSP", "Use only latin letters in the file name");
        userHasntSeenOnlyLatinLettersWarning = false;
    }
    QString filename = QFileDialog::getOpenFileName(this, "Save as", QDir::currentPath(), "Text files (*.txt)");
    if (strcmp(filename.toStdString().c_str(), "") == 0)
    {
        QMessageBox::critical(this, "MT-TSP", "Can't open the file");
        return;
    }

    FILE* f = fopen(filename.toStdString().c_str(), "w+"); // Saving all the data to the chosen file
    saveDataToFile(f);
}
void MainWindow::on_actionLoad_from_file_triggered()
{
    on_actionClear_triggered();
    setFocus();
    if (userHasntSeenOnlyLatinLettersWarning)
    {
        QMessageBox::information(this, "MT-TSP", "Use only latin letters in the file name");
        userHasntSeenOnlyLatinLettersWarning = false;
    }
    QString filename = QFileDialog::getOpenFileName(this, "Load from", QDir::currentPath(), "Text files (*.txt)");
    if (strcmp(filename.toStdString().c_str(), "") == 0)
    {
        QMessageBox::critical(this, "MT-TSP", "Can't open the file");
        on_actionClear_triggered();
        return;
    }

    FILE* f = fopen(filename.toStdString().c_str(), "r");
    int M, N;
    double x, y, v, xEnd, yEnd;
    char buffer1[256];
    char *tmpstr1;
    fgets(buffer1, 256, f); // Yerps # string
    fgets(buffer1, 256, f);
    tmpstr1 = strtok(buffer1, " ");
    M = strtol(tmpstr1, &tmpstr1, 0); // Catching # of Yerps
    if (M != 1 && M != 2) {
        QMessageBox::critical(this, "MT-TSP", "Invalid amount of Yerps");
        return;
    }
    fgets(buffer1, 256, f); // X, Y string

    for (int i = 0; i < M; i++) { // Catching data of Yerps and rendering them
        fgets(buffer1, 256, f);

        tmpstr1 = strtok(buffer1," ");
        x = strtod(tmpstr1, &tmpstr1);
        tmpstr1 = strtok(NULL," ");
        y = strtod(tmpstr1, &tmpstr1);

        view->createYerp(QPointF(x, y));
    }

    fgets(buffer1, 256, f);
    fgets(buffer1, 256, f);
    tmpstr1 = strtok(buffer1, " ");
    N = strtol(tmpstr1, &tmpstr1, 0); // Catching # of Yerps
    if (N < 0 || N > 12) {
        QMessageBox::critical(this, "MT-TSP", "Invalid amount of Preys");
        on_actionClear_triggered();
        return;
    }
    fgets(buffer1, 256, f); // X, Y, alpha, v, xEnd, yEnd string

    for (int i = 0; i < N; i++) { // Catching data of Preys and rendering them
        fgets(buffer1, 256, f);

        tmpstr1 = strtok(buffer1," "); // Taking data from file
        x = strtod(tmpstr1, &tmpstr1);
        tmpstr1 = strtok(NULL," ");
        y = strtod(tmpstr1, &tmpstr1);
        tmpstr1 = strtok(NULL," ");
        v = strtod(tmpstr1, &tmpstr1);
        tmpstr1 = strtok(NULL," ");
        v = strtod(tmpstr1, &tmpstr1);
        tmpstr1 = strtok(NULL," ");
        xEnd = strtod(tmpstr1, &tmpstr1);
        tmpstr1 = strtok(NULL," ");
        yEnd = strtod(tmpstr1, &tmpstr1);

        view->createPreyOnFullInfo(QPointF(x, y), QPointF(xEnd, yEnd), v);
    }

    fclose(f);
}
void MainWindow::saveDataToFile(FILE *f)
{
    fprintf(f, "Yerps #\n");
    fprintf(f, "%d\n", view->yerp.size());
    fprintf(f, "X    Y\n");
    int maxSignsX = 0;
    int maxSignsY = 0;
    int maxSignsAlpha = 0;
    int maxSignsV = 0;
    int maxSignsXEnd = 0;
    int maxSignsYEnd = 0;
    double x, y, alpha, v, xEnd, yEnd;
    for (Yerp* ye : view->yerp)
    {
        x = ye->getStart().x();
        y = ye->getStart().y();
        if (signs(x) > maxSignsX) maxSignsX = signs(x);
        if (signs(y) > maxSignsY) maxSignsY = signs(y);
    }
    for (Yerp* ye : view->yerp) fprintf(f, "%s\n",
                                        yerpDataStrSave(ye->getStart().x(), ye->getStart().y(),
                                                        maxSignsX, maxSignsY).toStdString().c_str());

    fprintf(f, "Preys #\n");
    fprintf(f, "%d\n", view->prey.size());
    fprintf(f, "X    Y    Tilt to the horizontal in degrees    Absolute value of velocity (should be less than 1)    xEnd    yEnd\n");
    maxSignsX = 0;
    maxSignsY = 0;
    maxSignsAlpha = 0;
    maxSignsV = 0;
    maxSignsXEnd = 0;
    maxSignsYEnd = 0;
    for (Prey* p : view->prey)
    {
        x = p->getStart().x();
        y = p->getStart().y();
        alpha = p->getAlpha();
        v = p->getV();
        xEnd = p->getEnd().x();
        yEnd = p->getEnd().y();
        if (signs(x) > maxSignsX) maxSignsX = signs(x);
        if (signs(y) > maxSignsY) maxSignsY = signs(y);
        if (signs(alpha) > maxSignsAlpha) maxSignsAlpha = signs(alpha);
        if (signs(v) > maxSignsV) maxSignsV = signs(v);
        if (signs(xEnd) > maxSignsXEnd) maxSignsXEnd = signs(xEnd);
        if (signs(yEnd) > maxSignsYEnd) maxSignsYEnd = signs(yEnd);
    }
    for (Prey* p : view->prey) fprintf(f, "%s\n",
                                       preyDataStrSave(p->getStart().x(), p->getStart().y(),
                                                       p->getAlpha(), p->getV(),
                                                       p->getEnd().x(), p->getEnd().y(),
                                                       maxSignsX, maxSignsY, maxSignsAlpha, maxSignsV, maxSignsXEnd, maxSignsYEnd).toStdString().c_str());
    fclose(f);
}

QString MainWindow::preyDataStrSave(double x, double y, double alpha, double v, double xEnd, double yEnd, int maxX, int maxY, int maxAlpha, int maxV, int maxXEnd, int maxYEnd)
{
    QString str = "";
    str.append(QString(maxX - signs(x), ' '));
    str += QString::number(x, 'f', 2) + "    ";
    str.append(QString(maxY - signs(y), ' '));
    str += QString::number(y, 'f', 2) + "    ";
    str.append(QString(maxAlpha - signs(alpha), ' '));
    str += QString::number(alpha, 'f', 2) + "    ";
    str.append(QString(maxV - signs(v), ' '));
    str += QString::number(v, 'f', 2) + "    ";
    str.append(QString(maxXEnd - signs(xEnd), ' '));
    str += QString::number(xEnd, 'f', 2) + "    ";
    str.append(QString(maxYEnd - signs(yEnd), ' '));
    str += QString::number(yEnd, 'f', 2);

    return str;
}
QString MainWindow::yerpDataStrSave(double x, double y, int maxX, int maxY)
{
    QString str = "";
    str.append(QString(maxX - signs(x), ' '));
    str += QString::number(x, 'f', 2) + "    ";
    str.append(QString(maxY - signs(y), ' '));
    str += QString::number(y, 'f', 2) + "    ";

    return str;
}
void MainWindow::on_rBConstruction_toggled(bool checked)
{
    if (!checked) return;

    view->setStatus(StatusScene::settingPreyStart);
    view->genRect->show();
    ui->rBAnimation->setEnabled(false);
    ui->actionStart->setEnabled(true);
    ui->actionRandom->setEnabled(true);
    ui->actionBack->setEnabled(true);

    view->timer->start(10);
    ui->dSBTime->setValue(0);
    ui->sliderTime->setValue(0);
    ui->playButton->setIcon(QIcon("playIcon.png"));
    ui->playButton->setEnabled(false);
    ui->speedUpButton->setIcon(QIcon("speedUpIcon.png"));
    ui->speedUpButton->setEnabled(false);

    for (Prey* p : view->prey)
    {
        p->sEll->show();
        p->eEll->show();
        p->line->show();
        p->setPos(p->getSStart());
        p->setIsDied(false);
    }

    for (Yerp* y : view->yerp) {
        y->setVel(0, 0);
        y->setPos(view->coordsToScene(y->getStart()));
    }
}

void MainWindow::solvingEnded()
{
    thread->exit(0);

    view->setEnabled(true);
    view->setStatus(StatusScene::animationMode);
    ui->actionClear->setEnabled(true);
    ui->actionLoad_from_file->setEnabled(true);
    ui->rBConstruction->setEnabled(true);
    ui->rBAnimation->setEnabled(true);
    ui->rBAnimation->setChecked(true);

    ui->progressBar->setValue(0);
    ui->dSBTime->setMaximum(solver->getResT());
    ui->dSBTime->setValue(0);
    ui->sliderTime->setMaximum(100*solver->getResT()-(int)(solver->getResT()*100) < 0.5 ? (int)(solver->getResT()*100):(int)(solver->getResT()*100)+1);
    ui->sliderTime->setValue(0);
    ui->playButton->setEnabled(true);
    ui->speedUpButton->setEnabled(true);
    view->timer->stop();

    for (Prey* p : view->prey)
    {
        p->sEll->hide();
        p->eEll->hide();
        p->line->hide();
        p->setPos(p->getSStart());
    }
}

void MainWindow::sliderTick() // Timer calls every 10ms
{
    if (view->getStatus() != StatusScene::animationMode) return;

    ui->sliderTime->setValue(ui->sliderTime->value() + ui->sliderTime->singleStep());
}
void MainWindow::on_sliderTime_valueChanged(int newV)
{
    if (view->getStatus() != StatusScene::animationMode) return;

    if (sliderVsDSBTime) {
        sliderVsDSBTime = false;
        ui->dSBTime->setValue(newV / 100.0);
    } else sliderVsDSBTime = true;
}
void MainWindow::on_dSBTime_valueChanged(double newV)
{
    if (view->getStatus() != StatusScene::animationMode) return;

    if (sliderVsDSBTime) {
        sliderVsDSBTime = false;
        ui->sliderTime->setValue((int)(newV*100));
    } else sliderVsDSBTime = true;

    for (Prey* p : view->prey) {
        if (newV == 0) p->setPos(p->getSStart());

        if (newV - p->getDieTime() > 0) {p->setIsDied(true); p->update();}
        else if (newV - p->getDieTime() < 0) {p->setIsDied(false); p->update();}
        else {
            p->setIsDied(true);
            p->update();

            p->setPos(view->coordsToScene(p->getStart()+newV*QPointF(p->getVx(), p->getVy())));
        } // The die moment itself
    }

    for (Yerp* y : view->yerp) {
        if (y->plan.isEmpty()) continue;
        if (newV == 0) y->setPos(view->coordsToScene(y->getStart()));

        if (newV >= view->prey[y->plan.last()]->getDieTime()) { // Yerp killed every Prey devoted to it
            y->setVel(0, 0);
            continue;
        }

        double alpha;
        QPointF start, end;
        if (newV < view->prey[y->plan[0]]->getDieTime()) {
            start = y->getStart(), end = view->prey[y->plan[0]]->getDiePoint();
        } else {
            for (int i = 0; i < y->plan.size()-1; i++) {
                if (view->prey[y->plan[i]]->getDieTime() <= newV && newV < view->prey[y->plan[i+1]]->getDieTime()) {
                    start = view->prey[y->plan[i]]->getDiePoint(), end = view->prey[y->plan[i+1]]->getDiePoint();
                }
            }
        }

        alpha = (fabs((end-start).x()) < 1.e-2 ? ((end-start).y() > 0 ? PI/2. : -PI/2.) : // Angle in radians
                                                 atan2((end-start).y(), (end-start).x()));
        y->setVel(cos(alpha), sin(alpha));
    }

    if (newV == ui->dSBTime->maximum()) { // Animation has ended
        ui->playButton->setIcon(QIcon("playIcon.png"));
        ui->sliderTime->setEnabled(true);
        view->timer->stop();
    } // Animation has ended

    //===============// Placing positions via mouse click
    if (view->timer->isActive()) return;
    QPointF newP;
    for (Prey* p : view->prey) {
        if (p->getIsDied()) {
            p->setPos(view->coordsToScene(p->getDiePoint()));
            continue;
        }

        newP = p->getStart() + newV*QPointF(p->getVx(), p->getVy());
        p->setPos(view->coordsToScene(newP));
    }

    for (auto y : view->yerp) {
        if (y->plan.isEmpty()) continue;
        if (newV >= view->prey[y->plan.last()]->getDieTime()) {
            y->setPos(view->coordsToScene(view->prey[y->plan.last()]->getDiePoint()));
            continue;
        } // Yerp killed every Prey devoted to it

        if (newV < view->prey[y->plan[0]]->getDieTime()) {
            newP = y->getStart() + newV*QPointF(y->getVx(), y->getVy());
        } else {
            for (int i = 0; i < y->plan.size()-1; i++) {
                double t_i0 = view->prey[y->plan[i]]->getDieTime();
                double t_i1 = view->prey[y->plan[i+1]]->getDieTime();

                if (t_i0 <= newV && newV < t_i1) {
                    newP = view->prey[y->plan[i]]->getDiePoint() + (newV-t_i0)*QPointF(y->getVx(), y->getVy());
                }
            }

            if (newV == view->prey[y->plan.last()]->getDieTime()) {
                newP = view->prey[y->plan.last()]->getDiePoint();
            } // Sync at last moment
        }

        y->setPos(view->coordsToScene(newP));
    }
    //===============//
}
void MainWindow::on_playButton_clicked()
{
    if (view->getStatus() != StatusScene::animationMode) return;

    if (view->timer->isActive()) {
        view->timer->stop();
        ui->playButton->setIcon(QIcon("playIcon.png"));
        ui->sliderTime->setEnabled(true);
    } else {
        view->timer->start(10);
        ui->playButton->setIcon(QIcon("pauseIcon.png"));
        ui->sliderTime->setEnabled(false);
        if (ui->dSBTime->value() == ui->dSBTime->maximum()) { // Pressed when the whole animation was played
            ui->sliderTime->setValue(0);
        }
    }
}
void MainWindow::on_speedUpButton_clicked()
{
    int tick = view->timer->interval();
    switch (tick) {
        case 10:
        {
            tick = 5;
            break;
        }
        case 5:
        {
            tick = 2;
            break;
        }
        case 2:
        {
            tick = 1;
            break;
        }
        case 1:
        {
            tick = 10;
            break;
        }
    }
    view->timer->setInterval(tick);
}

void MainWindow::changeProgressBar(long long vC, long long vAll)
{
    ui->progressBar->setValue((int) ((double)vC / vAll * 100));
}

bool MainWindow::isDataReadyToStartProcess()
{
    if (view->getStatus() == StatusScene::settingPreyEnd || view->getStatus() == StatusScene::settingPreyVelocity) return false;
    if (view->prey.size() > 12)
    {
        QMessageBox::critical(this, "MT-TSP", "Should be less then 13 Preys");
        return false;
    }
    if (view->prey.size() == 0 || view->yerp.size() == 0)
    {
        QMessageBox::information(this, "MT-TSP", "No Preys or Yerps");
        return false;
    }
    return true;
}

int MainWindow::signs(double r)
{
    int n = (int)r;
    if (n == 0) return r >= 0 ? 1 : 2;

    int tmp = 0;
    if (n < 0) tmp++;

    while (n != 0)
    {
        n /= 10;
        tmp++;
    }

    return tmp++;
}
