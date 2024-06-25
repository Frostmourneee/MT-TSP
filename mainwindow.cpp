#include "mainwindow.h"
#include "ui_mainwindow.h"

//TODO тесты
//TODO сортировка по иксам работает?
//TODO нельзя задать план из двузначной цели
//TODO позволить при большом N не искать оптимум, а просто летать
//TODO посмотреть размер итогового времени лейбла
//TODO исправить почему-то Z->I->I не даёт оптимального вью

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
    view->genRect->setRect(QRectF(20, 20, 1318, 773)); // Rect is bigger than it should be but in resizeEvent it will get the size it needs
    view->setSCoordCenter(QPointF(299, 218));
    view->setFocus();

    thread = new QThread(this);
    connect(this, SIGNAL(destroyed()), thread, SLOT(quit()));

    solver = new Solver();
    connect(this, SIGNAL(solve(MyQGraphicsView*)), solver, SLOT(solve(MyQGraphicsView*)));
    connect(this, SIGNAL(usePlan(MyQGraphicsView*)), solver, SLOT(usePlan(MyQGraphicsView*)));
    connect(solver, SIGNAL(solvingEnded()), this, SLOT(solvingEnded()));
    connect(solver, SIGNAL(usePlanEnded()), this, SLOT(usePlanEnded()));
    connect(solver, SIGNAL(changeProgressBar(long long, long long)), this, SLOT(changeProgressBar(long long, long long)));
    solver->moveToThread(thread);

    ui->progressBar->setStyleSheet("text-align: center");
    ui->buttonUsePlan->setIcon(QIcon("usePlanIcon.png"));
    ui->actionUsePlan->setIcon(QIcon("usePlanIcon.png"));
    ui->buttonBestPlan->setIcon(QIcon("bestPlanIcon.png"));
    ui->actionUseBestPlan->setIcon(QIcon("bestPlanIcon.png"));
    ui->optimalZoomButton->setIcon(QIcon("optimalZoomIcon.png"));
    ui->actionOptimalZoom->setIcon(QIcon("optimalZoomIcon.png"));
    ui->playButton->setIcon(QIcon("playIcon.png"));
    ui->actionPlay->setIcon(QIcon("playIcon.png"));
    ui->speedUpButton->setIcon(QIcon("speedUpIcon.png"));
    ui->actionSpeedUp->setIcon(QIcon("speedUpIcon.png"));
    ui->resetViewButton->setIcon(QIcon("resetIcon.png"));
    ui->actionResetView->setIcon(QIcon("resetIcon.png"));
    ui->optionsButton->setIcon(QIcon("optionsIcon.png"));
    ui->actionShow->setIcon(QIcon("optionsIcon.png"));
    ui->actionClear->setIcon(QIcon("restartIcon.png"));
    ui->actionLoad_from_file->setIcon(QIcon("openConfigIcon.png"));
    ui->actionSave_as->setIcon(QIcon("saveAsIcon.png"));
    ui->actionBack->setIcon(QIcon("backIcon.png"));
    ui->actionStart->setIcon(QIcon("startIcon.png"));
    ui->actionStart->setText("Start Calculation\tShift+Enter");
    ui->actionRandom->setIcon(QIcon("randomIcon.png"));
    ui->actionFullscreen->setIcon(QIcon("fullscreenIcon.png"));
    ui->actionExit->setIcon(QIcon("exitIcon.png"));

    connect(view->timer4Animation, SIGNAL(timeout()), this, SLOT(sliderTick()));

    connect(view, SIGNAL(preyWasCreatedOrDestroyed()), this, SLOT(preyWasCreatedOrDestroyed()));
    connect(view, SIGNAL(yerpWasCreatedOrDestroyed()), this, SLOT(yerpWasCreatedOrDestroyed()));

    ui->controlPanel->setStyleSheet("background-color: rgb(240, 240, 240);");
    ui->controlPanel->hide();

    connect(ui->lineEditUsePlan, SIGNAL(returnPressed()), this, SLOT(setFocus()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    int translateSpeed = 5;
    switch (e->key())
    {
        case Qt::Key_I:
        case 1064:
        {
            if (!e->modifiers().testFlag(Qt::ControlModifier)) return; // +Ctrl pressed

            view->info();
            break;
        }
        case Qt::Key_W:
        case 1062:
        {
            isWPressed = true;
            if (isWPressed == true && isAPressed == false && isSPressed == false && isDPressed == false) view->translateGraphics(translateSpeed*QPointF(0, 1));
            if (isWPressed == true && isAPressed == true && isSPressed == false && isDPressed == false) view->translateGraphics(translateSpeed*QPointF(sqrt(2)/2, sqrt(2)/2));
            if (isWPressed == true && isAPressed == false && isSPressed == false && isDPressed == true) view->translateGraphics(translateSpeed*QPointF(-sqrt(2)/2, sqrt(2)/2));
            break;
        }
        case Qt::Key_A:
        case 1060:
        {
            isAPressed = true;
            if (isWPressed == false && isAPressed == true && isSPressed == false && isDPressed == false) view->translateGraphics(translateSpeed*QPointF(1, 0));
            if (isWPressed == true && isAPressed == true && isSPressed == false && isDPressed == false) view->translateGraphics(translateSpeed*QPointF(sqrt(2)/2, sqrt(2)/2));
            if (isWPressed == false && isAPressed == true && isSPressed == true && isDPressed == false) view->translateGraphics(translateSpeed*QPointF(sqrt(2)/2, -sqrt(2)/2));
            break;
        }
        case Qt::Key_S:
        case 1067:
        {
            isSPressed = true;
            if (isWPressed == false && isAPressed == false && isSPressed == true && isDPressed == false) view->translateGraphics(translateSpeed*QPointF(0, -1));
            if (isWPressed == false && isAPressed == true && isSPressed == true && isDPressed == false) view->translateGraphics(translateSpeed*QPointF(sqrt(2)/2, -sqrt(2)/2));
            if (isWPressed == false && isAPressed == false && isSPressed == true && isDPressed == true) view->translateGraphics(translateSpeed*QPointF(-sqrt(2)/2, -sqrt(2)/2));
            break;
        }
        case Qt::Key_D:
        case 1042:
        {
            isDPressed = true;
            if (isWPressed == false && isAPressed == false && isSPressed == false && isDPressed == true) view->translateGraphics(translateSpeed*QPointF(-1, 0));
            if (isWPressed == true && isAPressed == false && isSPressed == false && isDPressed == true) view->translateGraphics(translateSpeed*QPointF(-sqrt(2)/2, sqrt(2)/2));
            if (isWPressed == false && isAPressed == false && isSPressed == true && isDPressed == true) view->translateGraphics(translateSpeed*QPointF(-sqrt(2)/2, -sqrt(2)/2));
            break;
        }
        case Qt::Key_T: // Test key
        {
            qDebug() << view->width() << view->height();
            break;
        }
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key())
    {
        case Qt::Key_W:
        case 1062:
        {
            isWPressed = false;
            break;
        }
        case Qt::Key_A:
        case 1060:
        {
            isAPressed = false;
            break;
        }
        case Qt::Key_S:
        case 1067:
        {
            isSPressed = false;
            break;
        }
        case Qt::Key_D:
        case 1042:
        {
            isDPressed = false;
            break;
        }
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent * e) {
    Q_UNUSED(e);

    view->setVisibleText(false);
}

void MainWindow::preyWasCreatedOrDestroyed()
{
    ui->labelPreysNum->setText(QString::number(view->prey.size()));
}
void MainWindow::yerpWasCreatedOrDestroyed()
{
    ui->labelYerpsNum->setText(QString::number(view->yerp.size()));
}
void MainWindow::sliderTick()
{
    if (view->getStatus() != StatusScene::animationMode) return;

    ui->sliderTime->setValue(ui->sliderTime->value() + ui->sliderTime->singleStep());
}
void MainWindow::setBestPlanToLineEditUsePlan()
{
    QString toLineEdit = ""; // Stuff to produce plan to the lineEditUsePlan
    for (Yerp* y : view->yerp)
    {
        for (int num : y->bestPlan)
        {
            toLineEdit += QString::number(num)+"-";
        }
        if (!toLineEdit.isEmpty() && toLineEdit[toLineEdit.size()-1] == "-") toLineEdit.chop(1);
        toLineEdit += "; ";
    }
    toLineEdit.chop(1);
    ui->lineEditUsePlan->setText(toLineEdit);
}
void MainWindow::on_sliderTime_valueChanged(int newV)
{
    if (view->getStatus() != StatusScene::animationMode) return;

    if (sliderVsDSBTime) {
        sliderVsDSBTime = false;
        ui->dSBTime->setValue(newV / 100.0);
    } else sliderVsDSBTime = true;
}
void MainWindow::on_dSBTime_valueChanged(double newT) // Main func for graphics in Animation mode
{
    if (view->getStatus() != StatusScene::animationMode) return;

    if (sliderVsDSBTime) {
        sliderVsDSBTime = false;
        ui->sliderTime->setValue((int)(newT*100));
    } else sliderVsDSBTime = true;

    for (Prey* p : view->prey) {
        if (newT == 0)
        {
            p->setPos(p->getSStart()); // Initial time moment
            p->setCurr(p->getStart());
        }

        if (newT - p->getDieTime() > 0) {p->setIsDied(true); p->update();}
        else if (newT - p->getDieTime() < 0) {p->setIsDied(false); p->update();}
        else {
            p->setIsDied(true);
            p->update();

            p->setPos(view->coordsToScene(p->getDiePoint()));
            p->setCurr(p->getDiePoint());
        } // The die moment itself
    }

    for (Yerp* y : view->yerp) {
        if (y->curPlan.isEmpty()) // Yerp has no Preys to kill
        {
            y->setVel(0, 0);
            continue;
        }
        if (newT == 0)
        {
            y->setPos(view->coordsToScene(y->getStart())); // Initial time moment
            y->setCurr(y->getStart());
        }

        if (newT >= y->lastPrey->getDieTime()) { // Yerp killed every Prey devoted to it
            y->setVel(0, 0);
            continue;
        }

        double alpha;
        QPointF start, end;
        if (newT < y->firstPrey->getDieTime()) {
            start = y->getStart();
            end = y->firstPrey->getDiePoint();
        } else {
            for (int i = 0; i < y->curPlan.size()-1; i++) {
                Prey* prevPrey = view->prey[y->curPlan[i]];
                Prey* nextPrey = view->prey[y->curPlan[i+1]];

                if (prevPrey->getDieTime() <= newT && newT < nextPrey->getDieTime()) {
                    start = prevPrey->getDiePoint();
                    end = nextPrey->getDiePoint();
                }
            }
        }

        alpha = (fabs((end-start).x()) < 1.e-4 ? ((end-start).y() > 0 ? PI/2. : -PI/2.) : // Angle in radians
                                                 atan2((end-start).y(), (end-start).x()));
        y->setVel(cos(alpha), sin(alpha));
    }

    if (newT == ui->dSBTime->maximum()) { // Animation has ended
        ui->playButton->setIcon(QIcon("playIcon.png"));
        ui->actionPlay->setIcon(QIcon("playIcon.png"));
        ui->sliderTime->setEnabled(true);
        view->timer4Animation->stop();
    } // Animation has ended

    //===============// Placing positions via mouse click
    if (view->timer4Animation->isActive()) return;
    QPointF newP;
    for (Prey* p : view->prey) {
        if (p->getIsDied()) {
            p->setPos(view->coordsToScene(p->getDiePoint()));
            p->setCurr(p->getDiePoint());
            continue;
        }

        newP = p->getStart() + newT*QPointF(p->getVx(), p->getVy());
        p->setPos(view->coordsToScene(newP));
        p->setCurr(newP);
    }

    for (Yerp* y : view->yerp) {
        if (y->curPlan.isEmpty()) // Yerp has no Preys to kill
        {
            y->setVel(0, 0);
            continue;
        }
        if (newT >= y->lastPrey->getDieTime()) {
            y->setPos(view->coordsToScene(y->lastPrey->getDiePoint()));
            y->setCurr(y->lastPrey->getDiePoint());
            continue;
        } // Yerp killed every Prey devoted to it

        if (newT < y->firstPrey->getDieTime()) {
            newP = y->getStart() + newT*QPointF(y->getVx(), y->getVy());
        } else {
            for (int i = 0; i < y->curPlan.size()-1; i++) {
                Prey* prevPrey = view->prey[y->curPlan[i]];
                Prey* nextPrey = view->prey[y->curPlan[i+1]];
                double t_i0 = prevPrey->getDieTime();
                double t_i1 = nextPrey->getDieTime();

                if (t_i0 <= newT && newT < t_i1) {
                    newP = prevPrey->getDiePoint() + (newT-t_i0)*QPointF(y->getVx(), y->getVy());
                }
            }

            if (newT == y->lastPrey->getDieTime()) {
                newP = y->lastPrey->getDiePoint();
            } // Sync at last moment
        }

        y->setPos(view->coordsToScene(newP));
        y->setCurr(newP);
    }
    //===============//
}
void MainWindow::on_playButton_clicked()
{
    if (view->getStatus() != StatusScene::animationMode) return;
    if (view->timer4Animation->isActive()) {
        view->timer4Animation->stop();
        ui->playButton->setIcon(QIcon("playIcon.png"));
        ui->actionPlay->setIcon(QIcon("playIcon.png"));
        ui->sliderTime->setEnabled(true);
    } else {
        view->timer4Animation->start(10);
        ui->playButton->setIcon(QIcon("pauseIcon.png"));
        ui->actionPlay->setIcon(QIcon("pauseIcon.png"));
        ui->sliderTime->setEnabled(false);
        if (ui->dSBTime->value() == ui->dSBTime->maximum()) { // Pressed when the whole animation was played
            ui->sliderTime->setValue(0);
        }
    }
}
void MainWindow::on_actionPlay_triggered()
{
    on_playButton_clicked();
}
void MainWindow::on_speedUpButton_clicked()
{
    QVector<int> tickVar;
    tickVar.push_back(10); tickVar.push_back(5); tickVar.push_back(2); tickVar.push_back(1);

    int tick = tickVar[(tickVar.indexOf(view->timer4Animation->interval())+1) % 4]; // 10 -> 5 -> 2 -> 1 -> 10

    view->timer4Animation->setInterval(tick);
}
void MainWindow::on_actionSpeedUp_triggered()
{
    on_speedUpButton_clicked();
}
void MainWindow::on_resetViewButton_clicked()
{
    view->setSF(1);
    view->setAnchor(QPointF(0, 0));
    view->setSCoordCenter(QPointF(view->width()/2., view->height()/2.));

    view->zoomGraphics(1);

    QGraphicsRectItem* genRect = view->genRect;
    QRectF newRect = QRectF(20, 20, view->width()-40, view->height()-40).normalized();
    genRect->setRect(newRect);
}
void MainWindow::on_actionResetView_triggered()
{
    on_resetViewButton_clicked();
}
void MainWindow::on_optimalZoomButton_clicked()
{
    view->transformViewToOptimal();
}
void MainWindow::on_actionOptimalZoom_triggered()
{
    on_optimalZoomButton_clicked();
}
void MainWindow::on_optionsButton_clicked()
{
    view->setResizeDueToOnOptionsButtonClicked(true); // Should be BEFORE the next code
    ui->controlPanel->isVisible() ? ui->controlPanel->hide() : ui->controlPanel->show(); // This code will trigger resizeEvent on view, so view->ViewToOptimal() will be triggered properly there
}
void MainWindow::on_actionShow_triggered()
{
    on_optionsButton_clicked();
}
void MainWindow::on_buttonUsePlan_clicked()
{
    QVector<int> plan4FirstYerp;
    QVector<int> plan4SecondYerp;
    for (QString i : ui->lineEditUsePlan->text().split(";")[0].split("-"))
        if (i != "" && QString::number(i.toInt()) == i) plan4FirstYerp.push_back(i.toInt());

    if (ui->lineEditUsePlan->text().split(";").size() > 1)
        for (QString i : ui->lineEditUsePlan->text().split(";")[1].split("-"))
            if (i != "" && i != " " && (QString::number(i.toInt()) == i || QString::number(i.toInt()) == i.remove(0, 1)))
                plan4SecondYerp.push_back(i.toInt());

    QPalette palette;
    if (view->yerp.size() == 2 && !plan4SecondYerp.isEmpty())
    {
        palette.setColor(QPalette::Text,Qt::red);
        ui->lineEditUsePlan->setPalette(palette);
        return;
    } // Only one Yerp but smth is written in lineEdit after first Yerp

    if (plan4FirstYerp.size()+plan4SecondYerp.size() != view->prey.size()) {
        palette.setColor(QPalette::Text,Qt::red);
        ui->lineEditUsePlan->setPalette(palette);
        return;
    } // Not all Preys on lineEdit were used or additional (non-existing) Preys were used

    for (int i : plan4FirstYerp) if (i < 0 || i > view->prey.size()-1) {
        palette.setColor(QPalette::Text,Qt::red);
        ui->lineEditUsePlan->setPalette(palette);
        return;
    } // Found incorrect Prey in plan4FirstYerp
    for (int i : plan4SecondYerp) if (i < 0 || i > view->prey.size()-1) {
        palette.setColor(QPalette::Text,Qt::red);
        ui->lineEditUsePlan->setPalette(palette);
        return;
    } // Found incorrect Prey in plan4SecondYerp

    QVector<int> tmp;
    for (int i : plan4FirstYerp) tmp.push_back(i);
    for (int i : plan4SecondYerp) tmp.push_back(i);
    for (int i = 0; i < tmp.size() - 1; i++) {
        for (int j = i+1; j < tmp.size(); j++) if (tmp[j] == tmp[i]) {
            palette.setColor(QPalette::Text,Qt::red);
            ui->lineEditUsePlan->setPalette(palette);
            return;
        }
    } // Found Same Preys

    palette.setColor(QPalette::Text, Qt::black);
    ui->lineEditUsePlan->setPalette(palette); // lineEdit filled correctly

    ui->dSBTime->setValue(0); // To put everything to its start

    Yerp* y1 = view->yerp[0];
    if (view->yerp.size() == 1)
    {
        y1->curPlan.clear();
        for (int i : plan4FirstYerp) y1->curPlan.push_back(i);
    }
    else if (view->yerp.size() == 2)
    {
        Yerp* y2 = view->yerp[1];
        y1->curPlan.clear();
        y2->curPlan.clear();
        for (int i : plan4FirstYerp) y1->curPlan.push_back(i);
        for (int i : plan4SecondYerp) y2->curPlan.push_back(i);
    }

    thread->start();
    emit usePlan(view);
}
void MainWindow::on_actionUsePlan_triggered()
{
    on_buttonUsePlan_clicked();
}
void MainWindow::on_buttonBestPlan_clicked()
{
    setBestPlanToLineEditUsePlan();

    Yerp* y1 = view->yerp[0];
    if (view->yerp.size() == 1)
    {
        y1->curPlan.clear();
        for (int i : y1->bestPlan) y1->curPlan.push_back(i);
    }
    else if (view->yerp.size() == 2)
    {
        Yerp* y2 = view->yerp[1];
        y1->curPlan.clear();
        y2->curPlan.clear();
        for (int i : y1->bestPlan) y1->curPlan.push_back(i);
        for (int i : y2->bestPlan) y2->curPlan.push_back(i);
    }

    thread->start();
    emit usePlan(view);
}
void MainWindow::on_actionUseBestPlan_triggered()
{
    on_buttonBestPlan_clicked();
}
void MainWindow::on_rBConstruction_toggled(bool checked)
{
    if (!checked) return;

    view->setStatus(StatusScene::settingPreyStart);

    ui->rBAnimation->setEnabled(false);
    ui->actionStart->setEnabled(true);
    ui->actionRandom->setEnabled(true);
    ui->actionBack->setEnabled(true);

    view->genRect->show();
    view->transformViewToOptimal();
    ui->labelT->setText("");
    ui->dSBTime->setValue(0);
    ui->sliderTime->setValue(0);
    ui->lineEditUsePlan->clear();
    ui->lineEditUsePlan->setEnabled(false);
    ui->lineEditUsePlan->setStyleSheet("background-color: rgb(240, 240, 240);");
    ui->optimalZoomButton->setEnabled(false);
    ui->actionOptimalZoom->setEnabled(false);
    ui->playButton->setIcon(QIcon("playIcon.png"));
    ui->playButton->setEnabled(false);
    ui->actionPlay->setIcon(QIcon("playIcon.png"));
    ui->actionPlay->setEnabled(false);
    ui->dSBTime->setEnabled(false);
    ui->sliderTime->setEnabled(false);
    ui->speedUpButton->setEnabled(false);
    ui->actionSpeedUp->setEnabled(false);
    ui->buttonUsePlan->setEnabled(false);
    ui->actionUsePlan->setEnabled(false);
    ui->buttonBestPlan->setEnabled(false);
    ui->actionUseBestPlan->setEnabled(false);

    view->timer4Animation->start(10);

    for (Prey* p : view->prey)
    {
        p->sEll->show();
        p->eEll->show();
        p->line->show();
        p->setPos(p->getSStart());
        p->setIsDied(false);
        p->setCurr(p->getStart());
    }

    for (Yerp* y : view->yerp) {
        y->setVel(0, 0);
        y->setPos(view->coordsToScene(y->getStart()));
        y->setCurr(y->getStart());
    }
}
void MainWindow::on_actionClear_triggered()
{
    setFocus();

    view->clear();
    ui->labelPreysNum->setText("0");
    ui->labelYerpsNum->setText("0");
    ui->labelT->setText("");
    ui->lineEditUsePlan->clear();
    ui->lineEditUsePlan->setEnabled(false);
    ui->lineEditUsePlan->setStyleSheet("background-color: rgb(240, 240, 240);");
    view->genRect->show();
    ui->rBConstruction->setChecked(true);
    ui->rBAnimation->setEnabled(false);
    ui->dSBTime->setValue(0);
    ui->sliderTime->setValue(0);
    ui->optimalZoomButton->setEnabled(false);
    ui->actionOptimalZoom->setEnabled(false);
    ui->playButton->setIcon(QIcon("playIcon.png"));
    ui->playButton->setEnabled(false);
    ui->actionPlay->setIcon(QIcon("playIcon.png"));
    ui->actionPlay->setEnabled(false);
    ui->dSBTime->setEnabled(false);
    ui->sliderTime->setEnabled(false);
    ui->speedUpButton->setEnabled(false);
    ui->actionSpeedUp->setEnabled(false);
    ui->buttonUsePlan->setEnabled(false);
    ui->actionUsePlan->setEnabled(false);
    ui->buttonBestPlan->setEnabled(false);
    ui->actionUseBestPlan->setEnabled(false);

    QPointF pMathCursorPos = view->sceneToCoords(view->mapFromGlobal(QCursor::pos()));
    double x = pMathCursorPos.x();
    double y = pMathCursorPos.y();
    view->textCoords(x + 0.02, y - 0.02);
    view->timer4Animation->start(10);
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
    double minVel1f = 5;

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

    view->transformViewToOptimal();
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

    ui->lineEditUsePlan->setEnabled(true);
    ui->lineEditUsePlan->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->progressBar->setValue(0);
    ui->dSBTime->setMaximum(solver->getResT());
    ui->dSBTime->setValue(0);
    ui->sliderTime->setMaximum(100*solver->getResT()-(int)(solver->getResT()*100) < 0.5 ? (int)(solver->getResT()*100) : (int)(solver->getResT()*100)+1);
    ui->sliderTime->setValue(0);
    ui->labelT->setText(QString::number(solver->getResT(), 'f', 2));
    ui->optimalZoomButton->setEnabled(true);
    ui->actionOptimalZoom->setEnabled(true);
    ui->playButton->setEnabled(true);
    ui->actionPlay->setEnabled(true);
    ui->dSBTime->setEnabled(true);
    ui->sliderTime->setEnabled(true);
    ui->speedUpButton->setEnabled(true);
    ui->actionSpeedUp->setEnabled(true);
    ui->buttonUsePlan->setEnabled(true);
    ui->actionUsePlan->setEnabled(true);
    ui->buttonBestPlan->setEnabled(true);
    ui->actionUseBestPlan->setEnabled(true);
    view->timer4Animation->stop();

    for (Prey* p : view->prey)
    {
        p->sEll->hide();
        p->eEll->hide();
        p->line->hide();
        p->setPos(p->getSStart());
        p->setCurr(p->getStart());
    }

    setBestPlanToLineEditUsePlan();
}
void MainWindow::usePlanEnded()
{
    double resT = qMax(view->yerp[0]->lastPrey->getDieTime(), view->yerp.size() == 2 ? view->yerp[1]->lastPrey->getDieTime() : view->yerp[0]->lastPrey->getDieTime());
    ui->labelT->setText(QString::number(resT, 'f', 2));
    ui->dSBTime->setMaximum(resT);
    ui->sliderTime->setMaximum(100*resT-(int)(resT*100) < 0.5 ? (int)(resT*100) : (int)(resT*100)+1);
    thread->exit(0);
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
