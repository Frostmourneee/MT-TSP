#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMinimumSize(QSize(1200, 630));
    resize(QSize(1200, 630));

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

    ui->buttonUsePlan->setIcon(QIcon("icons\\usePlanIcon.png"));
    ui->actionUsePlan->setIcon(QIcon("icons\\usePlanIcon.png"));
    ui->buttonBestPlan->setIcon(QIcon("icons\\bestPlanIcon.png"));
    ui->actionUseBestPlan->setIcon(QIcon("icons\\bestPlanIcon.png"));
    ui->optimalZoomButton->setIcon(QIcon("icons\\optimalZoomIcon.png"));
    ui->actionOptimalZoom->setIcon(QIcon("icons\\optimalZoomIcon.png"));
    ui->actionStart->setIcon(QIcon("icons\\startIcon.png"));
    ui->actionStart->setText("Start Calculation\tShift+Enter");
    ui->playButton->setIcon(QIcon("icons\\playIcon.png"));
    ui->actionPlay->setIcon(QIcon("icons\\playIcon.png"));
    ui->speedUpButton->setIcon(QIcon("icons\\speedUpIcon.png"));
    ui->actionSpeedUp->setIcon(QIcon("icons\\speedUpIcon.png"));
    ui->resetViewButton->setIcon(QIcon("icons\\resetIcon.png"));
    ui->actionResetView->setIcon(QIcon("icons\\resetIcon.png"));
    ui->optionsButton->setIcon(QIcon("icons\\optionsIcon.png"));
    ui->actionShow->setIcon(QIcon("icons\\optionsIcon.png"));
    ui->actionClear->setIcon(QIcon("icons\\restartIcon.png"));
    ui->actionLoad_from_file->setIcon(QIcon("icons\\openConfigIcon.png"));
    ui->actionSave_as->setIcon(QIcon("icons\\saveAsIcon.png"));
    ui->actionBack->setIcon(QIcon("icons\\backIcon.png"));
    ui->actionRandom->setIcon(QIcon("icons\\randomIcon.png"));
    ui->actionFullscreen->setIcon(QIcon("icons\\fullscreenIcon.png"));
    ui->actionExit->setIcon(QIcon("icons\\exitIcon.png"));

    connect(view->timer4Animation, SIGNAL(timeout()), this, SLOT(sliderTick()));
    connect(view, SIGNAL(preyWasCreated(bool)), this, SLOT(preyWasCreated(bool)));
    connect(view, SIGNAL(yerpWasCreated(bool)), this, SLOT(yerpWasCreated(bool)));
    connect(view, SIGNAL(fillTableDueToPreyCreation()), this, SLOT(fillTableDueToPreyCreation()));
    connect(view, SIGNAL(fillTableDueToYerpCreation()), this, SLOT(fillTableDueToYerpCreation()));

    ui->progressBar->setStyleSheet("text-align: center");
    ui->info->setAutoFillBackground(true);
    ui->randomGen->setAutoFillBackground(true);
    ui->controlPanel->hide();

    connect(ui->lineEditUsePlan, SIGNAL(returnPressed()), this, SLOT(setFocus()));
    connect(ui->spinBoxPreys, SIGNAL(editingFinished()), this, SLOT(setFocus()));
    connect(ui->spinBoxYerps, SIGNAL(editingFinished()), this, SLOT(setFocus()));
    connect(ui->dSpinBoxVelMin, SIGNAL(editingFinished()), this, SLOT(setFocus()));
    connect(ui->dSpinBoxVelMax, SIGNAL(editingFinished()), this, SLOT(setFocus()));

    initTables();
    connect(modelPrey, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(on_modelPreyDataChanged(QModelIndex, QModelIndex)));
    connect(modelYerp, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(on_modelYerpDataChanged(QModelIndex, QModelIndex)));
    connect(ui->tableViewPrey->horizontalScrollBar(), SIGNAL(sliderReleased()), this, SLOT(setFocus()));
    connect(ui->tableViewPrey->verticalScrollBar(), SIGNAL(sliderReleased()), this, SLOT(setFocus()));
    connect(ui->tableViewPrey->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(setFocus()));
    connect(ui->tableViewYerp->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(setFocus()));
    connect(ui->tableViewPrey, SIGNAL(clicked(QModelIndex)), this, SLOT(setFocus()));
    connect(ui->tableViewYerp, SIGNAL(clicked(QModelIndex)), this, SLOT(setFocus()));
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
            if (e->modifiers().testFlag(Qt::ShiftModifier) && e->modifiers().testFlag(Qt::ControlModifier)) // CTRL+SHIFT+T pressed
            {
                testAmount = 0;
                QString filename = "C:/Qt/MT-TSP/tests/" + QString::number(testAmount) + ".txt";
                while (QFile(filename).exists())
                {
                    testAmount++;
                    filename = "C:/Qt/MT-TSP/tests/" + QString::number(testAmount) + ".txt";
                }

                testFileNum = 0;
                oneTest();
            }
            else qDebug() << view->width() << view->height(); // T pressed
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

void MainWindow::preyWasCreated(bool wasCreated)
{
    ui->labelPreysNum->setText(QString::number(view->prey.size()));

    if (wasCreated) return; // Wasn't destroyed

    modelPrey->removeRow(modelPrey->rowCount() - 1);
    ui->tableViewPrey->resizeColumnsToContents();
    ui->tableViewPrey->resizeRowsToContents();
}
void MainWindow::yerpWasCreated(bool wasCreated)
{
    ui->labelYerpsNum->setText(QString::number(view->yerp.size()));

    if (wasCreated) return; // Wasn't destroyed

    modelYerp->removeRow(modelYerp->rowCount() - 1);
    modelYerp->removeRow(modelYerp->rowCount() - 1); // *
    ui->tableViewYerp->resizeColumnsToContents();
    ui->tableViewYerp->resizeRowsToContents();
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

    QPalette palette;
    palette.setColor(QPalette::Text, Qt::black);
    ui->lineEditUsePlan->setPalette(palette); // lineEdit filled correctly
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

        if (newT - p->getDieTime() > 0) p->setIsDied(true);
        else if (newT - p->getDieTime() < 0) p->setIsDied(false);
        else {
            p->setIsDied(true);

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
        ui->playButton->setIcon(QIcon("icons\\playIcon.png"));
        ui->actionPlay->setIcon(QIcon("icons\\playIcon.png"));
        ui->sliderTime->setEnabled(true);
        view->timer4Animation->stop();
    } // Animation has ended

    //===============// Placing positions via mouse click (equally in time in table click)
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
void MainWindow::on_actionStart_triggered()
{
    setFocus();
    if (!isDataReadyToUsePlan()) return;
    if ((view->yerp.size() == 1 && view->prey.size() > 20) || (view->yerp.size() == 2 && view->prey.size() > 14))
    {
        QMessageBox::critical(this, "MT-TSP", "One Yerp can look for optimal plan with up to 20 Preys. Two yerps - up to 14. \nUse \"Use Plan\" option if you want to investigate one specified plan not to look for the optimal.");
        return;
    }

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
    view->eraseHlight();

    FILE* initDataFile = fopen("initData.txt", "w+"); // Saving all the data to the default "initData.txt" file
    saveDataToFile(initDataFile);
    fclose(initDataFile);

    thread->start();
    emit solve(view);
}
void MainWindow::on_playButton_clicked()
{
    if (view->getStatus() != StatusScene::animationMode) return;
    if (view->timer4Animation->isActive()) {
        view->timer4Animation->stop();
        ui->playButton->setIcon(QIcon("icons\\playIcon.png"));
        ui->actionPlay->setIcon(QIcon("icons\\playIcon.png"));
        ui->sliderTime->setEnabled(true);
    } else {
        view->timer4Animation->start(10);
        ui->playButton->setIcon(QIcon("icons\\pauseIcon.png"));
        ui->actionPlay->setIcon(QIcon("icons\\pauseIcon.png"));
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
    ui->controlPanel->setVisible(!ui->controlPanel->isVisible()); // This code will trigger resizeEvent on view, so view->ViewToOptimal() will be triggered properly there
}
void MainWindow::on_actionShow_triggered()
{
    on_optionsButton_clicked();
}
void MainWindow::on_buttonUsePlan_clicked()
{
    if (!isDataReadyToUsePlan()) return;

    if (ui->lineEditUsePlan->text().isEmpty())
    {
        QMessageBox::critical(this, "MT-TSP", "Provide the plan you want to use");
        return;
    }

    QVector<int> plan4FirstYerp;
    QVector<int> plan4SecondYerp;
    for (QString i : ui->lineEditUsePlan->text().split(";")[0].split("-"))
        if (i != "" && QString::number(i.toInt()) == i) plan4FirstYerp.push_back(i.toInt());

    if (ui->lineEditUsePlan->text().split(";").size() > 1)
        for (QString i : ui->lineEditUsePlan->text().split(";")[1].split("-"))
            if (i != "" && i != " " && (QString::number(i.toInt()) == i || QString::number(i.toInt()) == i.remove(0, 1)))
                plan4SecondYerp.push_back(i.toInt());

    QPalette palette;
    if (view->yerp.size() == 1 && !plan4SecondYerp.isEmpty())
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
    view->eraseHlight();
    ui->labelT->setText("");
    ui->dSBTime->setValue(0);
    ui->sliderTime->setValue(0);
    ui->lineEditUsePlan->clear();
    ui->optimalZoomButton->setEnabled(false);
    ui->actionOptimalZoom->setEnabled(false);
    ui->playButton->setIcon(QIcon("icons\\playIcon.png"));
    ui->playButton->setEnabled(false);
    ui->actionPlay->setIcon(QIcon("icons\\playIcon.png"));
    ui->actionPlay->setEnabled(false);
    ui->dSBTime->setEnabled(false);
    ui->sliderTime->setEnabled(false);
    ui->speedUpButton->setEnabled(false);
    ui->actionSpeedUp->setEnabled(false);
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

    preyRowsToInit();
    yerpRowsToInit();
    for (int i = 0; i < view->prey.size(); i++) // x0, y0, angle, velocity
    {
        modelPrey->item(i, 1)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
        modelPrey->item(i, 2)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
        modelPrey->item(i, 3)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
        modelPrey->item(i, 4)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    }
    for (int i = 0; i < view->yerp.size(); i++) // x0, y0
    {
        modelYerp->item(2*i, 1)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
        modelYerp->item(2*i, 2)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);

        modelYerp->item(2*i+1, 1)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable); // x0, y0*
        modelYerp->item(2*i+1, 2)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    }
}
void MainWindow::on_actionClear_triggered()
{
    setFocus();

    view->eraseHlight();
    view->clear();
    ui->labelPreysNum->setText("0");
    ui->labelYerpsNum->setText("0");
    ui->labelT->setText("");
    ui->lineEditUsePlan->clear();
    view->genRect->show();
    ui->rBConstruction->setChecked(true);
    ui->rBAnimation->setEnabled(false);
    ui->dSBTime->setValue(0);
    ui->sliderTime->setValue(0);
    ui->optimalZoomButton->setEnabled(false);
    ui->actionOptimalZoom->setEnabled(false);
    ui->playButton->setIcon(QIcon("icons\\playIcon.png"));
    ui->playButton->setEnabled(false);
    ui->actionPlay->setIcon(QIcon("icons\\playIcon.png"));
    ui->actionPlay->setEnabled(false);
    ui->dSBTime->setEnabled(false);
    ui->sliderTime->setEnabled(false);
    ui->speedUpButton->setEnabled(false);
    ui->actionSpeedUp->setEnabled(false);
    ui->buttonBestPlan->setEnabled(false);
    ui->actionUseBestPlan->setEnabled(false);

    modelPrey->removeRows(0, modelPrey->rowCount());
    modelYerp->removeRows(0, modelYerp->rowCount());

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
    double maxVel = ui->dSpinBoxVelMax->value();
    double minVel = ui->dSpinBoxVelMin->value();

    if (xmax <= xmin || ymax <= ymin) {
        QMessageBox::critical(this, "MT-TSP", "Invalid generation bounds\n");
        return;
    }

    on_actionClear_triggered();
    srand(time(NULL));
    int M = ui->checkBoxRandomM->isChecked() ? rand()%2 + 1 : ui->spinBoxYerps->value();
    int N = ui->checkBoxRandomN->isChecked() ? rand()%20 + 1 : ui->spinBoxPreys->value();

    int parts;
    double r2fValue, x, y, v, xEnd, yEnd;
    for (int i = 0; i < M; i++) // Yerps generation
    {
        if (ui->checkBoxAllYerpsToZero->isChecked())
        {
            view->createYerp(QPointF(0., 0.));
            continue;
        }

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

        parts = (maxVel-minVel)*100;
        r2fValue = minVel + rand()%(parts + 1)*0.01;
        v = r2fValue;
        if (r2fValue >= maxVel) v = maxVel;

        view->createPreyOnFullInfo(QPointF(x, y), QPointF(xEnd, yEnd), v);
    }

    fillFullYerpTable();
    fillFullPreyTableAfter();
}
void MainWindow::on_actionBack_triggered()
{
    setFocus();
    view->backAction();
}
void MainWindow::on_actionSave_as_triggered()
{
    setFocus();
    if (!isDataReadyToUsePlan()) return;

    if (userHasntSeenOnlyLatinLettersWarning)
    {
        QDialog dlg(this);
        dlg.setWindowFlags(dlg.windowFlags() & ~Qt::WindowContextHelpButtonHint);

        QLabel userLatinLetterWarn("Use only latin letters in the file name", &dlg);
        userLatinLetterWarn.setFont(QFont("MS Shell Dlg 2", 10));

        QSpacerItem verticalSpacer(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        QCheckBox chkbx("Don't show me this again", &dlg);
        chkbx.setFont(QFont("MS Shell Dlg 2", 8));

        QDialogButtonBox btn_box(&dlg);
        btn_box.setStandardButtons(QDialogButtonBox::Ok);
        connect(&btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(&userLatinLetterWarn);
        layout->addItem(&verticalSpacer);
        layout->addWidget(&chkbx);
        layout->addWidget(&btn_box);
        layout->setSizeConstraint(QLayout::SetFixedSize);

        dlg.setLayout(layout);

        if(dlg.exec() == QDialog::Accepted && chkbx.isChecked()) userHasntSeenOnlyLatinLettersWarning = false;
    }
    QString filename = QFileDialog::getOpenFileName(this, "Save as", QDir::currentPath(), "Text files (*.txt)");
    if (strcmp(filename.toStdString().c_str(), "") == 0)
    {
        QMessageBox::critical(this, "MT-TSP", "Can't open the file");
        return;
    }

    FILE* f = fopen(filename.toStdString().c_str(), "w+"); // Saving all the data to the chosen file
    saveDataToFile(f);
    fclose(f);
}
void MainWindow::on_actionLoad_from_file_triggered()
{
    on_actionClear_triggered();
    setFocus();
    if (userHasntSeenOnlyLatinLettersWarning)
    {
        QDialog dlg(this);
        dlg.setWindowFlags(dlg.windowFlags() & ~Qt::WindowContextHelpButtonHint);

        QLabel userLatinLetterWarn("Use only latin letters in the file name", &dlg);
        userLatinLetterWarn.setFont(QFont("MS Shell Dlg 2", 10));

        QSpacerItem verticalSpacer(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        QCheckBox chkbx("Don't show me this again", &dlg);
        chkbx.setFont(QFont("MS Shell Dlg 2", 8));

        QDialogButtonBox btn_box(&dlg);
        btn_box.setStandardButtons(QDialogButtonBox::Ok);
        connect(&btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(&userLatinLetterWarn);
        layout->addItem(&verticalSpacer);
        layout->addWidget(&chkbx);
        layout->addWidget(&btn_box);
        layout->setSizeConstraint(QLayout::SetFixedSize);

        dlg.setLayout(layout);
        dlg.exec();
        if (chkbx.isChecked()) userHasntSeenOnlyLatinLettersWarning = false;

        delete layout;
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
    if (N < 0 || N > 20) {
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

    fillFullYerpTable();
    fillFullPreyTableAfter();
}
void MainWindow::on_checkBoxRandomM_stateChanged(int isChecked)
{
    ui->spinBoxYerps->setEnabled(!isChecked);
}
void MainWindow::on_checkBoxRandomN_stateChanged(int isChecked)
{
    ui->spinBoxPreys->setEnabled(!isChecked);
}
void MainWindow::on_dSpinBoxVelMin_editingFinished()
{
    ui->dSpinBoxVelMax->setMinimum(ui->dSpinBoxVelMin->value());
}
void MainWindow::on_dSpinBoxVelMax_editingFinished()
{
    ui->dSpinBoxVelMin->setMaximum(ui->dSpinBoxVelMax->value());
}
void MainWindow::on_tableViewPrey_clicked(const QModelIndex &index)
{
    if (modelPrey->item(index.row(), index.column())->foreground().color() != Qt::blue) return;

    if (index.column() == 0) // №
    {
        int i = modelPrey->data(index, Qt::DisplayRole).toInt();
        if (view->prey[i]->getIsHlighted()) {
            view->eraseHlight(); // Can't write it at the beginning of func cause eraseHlight() affects getIsHlighted()
            return;
        }

        view->eraseHlight(); // Can't write it at the beginning of func cause eraseHlight() affects getIsHlighted()
        view->prey[i]->setIsHlighted(true);
    } else if (index.column() == 5) // dieTime
    {
        ui->dSBTime->setValue(modelPrey->data(index, Qt::DisplayRole).toDouble());
    }
}
void MainWindow::on_tableViewYerp_clicked(const QModelIndex &index)
{
    if (modelYerp->item(index.row(), index.column())->foreground().color() != Qt::blue) return;

    // Fly (working) time
    if (index.column() == 4 && index.row() % 2 == 0) ui->dSBTime->setValue(modelYerp->data(index, Qt::DisplayRole).toDouble());
}
void MainWindow::on_tableViewPrey_doubleClicked(const QModelIndex &index)
{
    if (modelPrey->item(index.row(), index.column())->isEditable()) isTableViewPreyDataChangedByHand = true;
}
void MainWindow::on_modelPreyDataChanged(QModelIndex i1, QModelIndex i2)
{
    if (!isTableViewPreyDataChangedByHand) return;
    isTableViewPreyDataChangedByHand = false;

    int row = i1.row();
    int col = i1.column();
    if (col == 1 || col == 2) // x0, y0
    {
        Prey* p = view->prey[row];
        QPointF newSt = QPointF(modelPrey->item(row, 1)->data(Qt::DisplayRole).toDouble(), modelPrey->item(row, 2)->data(Qt::DisplayRole).toDouble());
        QPointF delta = newSt-p->getStart();
        p->setStart(newSt);
        p->setEnd(p->getEnd()+delta);
        view->preyTransform(p, p->getStart());
    }
    else if (col == 3) // angle
    {
        Prey* p = view->prey[row];
        double alpha = modelPrey->item(row, 3)->data(Qt::DisplayRole).toDouble();
        QPointF newEnd = p->getStart() + p->line->line().length()/view->getUnit()*QPointF(cos(PI/180.*alpha), sin(PI/180.*alpha));
        QPointF sNewEnd = view->coordsToScene(newEnd);

        p->eEll->setPos(sNewEnd);
        p->setEnd(newEnd);
        p->setSEnd(sNewEnd);
        p->setAlpha(alpha);
        p->line->setLine(QLineF(p->getSStart(), p->getSEnd()));
        p->setVel(p->getV()*QPointF(cos(PI/180.*alpha), sin(PI/180.*alpha)));
        p->setPos(p->getSStart());
    }
    else if (col == 4) // velocity
    {
        Prey* p = view->prey[row];
        if (modelPrey->item(row, 4)->data(Qt::DisplayRole).toDouble() > 0.95) modelPrey->item(row, 4)->setData(0.95, Qt::EditRole);
        else if (modelPrey->item(row, 4)->data(Qt::DisplayRole).toDouble() < 0.) modelPrey->item(row, 4)->setData(0., Qt::EditRole);

        p->setV(modelPrey->item(row, 4)->data(Qt::DisplayRole).toDouble());
        p->setVel(p->getV()*QPointF(cos(PI/180.*p->getAlpha()), sin(PI/180.*p->getAlpha())));
    }

    Q_UNUSED(i2);
}
void MainWindow::on_tableViewYerp_doubleClicked(const QModelIndex &index)
{
    if (modelYerp->item(index.row(), index.column())->isEditable()) isTableViewYerpDataChangedByHand = true;
}
void MainWindow::on_modelYerpDataChanged(QModelIndex i1, QModelIndex i2)
{
    if (!isTableViewYerpDataChangedByHand) return;
    isTableViewYerpDataChangedByHand = false;

    int row = i1.row();
    double x = modelYerp->item(row, 1)->data(Qt::DisplayRole).toDouble();
    double y = modelYerp->item(row, 2)->data(Qt::DisplayRole).toDouble();
    QPointF newSt = QPointF(x, y);
    QPointF sNewSt = view->coordsToScene(newSt);
    view->yerp[row/2]->setStart(newSt);
    view->yerp[row/2]->setSStart(sNewSt);
    view->yerp[row/2]->setPos(sNewSt);

    modelYerp->item(row+1, 1)->setData(x, Qt::EditRole);
    modelYerp->item(row+1, 2)->setData(y, Qt::EditRole);

    Q_UNUSED(i2);
}

void MainWindow::initTables()
{
    ui->tableViewPrey->setShowGrid(true);
    ui->tableViewPrey->setGridStyle(Qt::SolidLine);
    ui->tableViewPrey->verticalHeader()->hide();
    ui->tableViewPrey->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableViewPrey->verticalScrollBar()->setSingleStep(8);
    ui->tableViewPrey->horizontalScrollBar()->setSingleStep(3);
    ui->tableViewPrey->setSortingEnabled(false);

    ui->tableViewYerp->setShowGrid(true);
    ui->tableViewYerp->setGridStyle(Qt::SolidLine);
    ui->tableViewYerp->verticalHeader()->hide();
    ui->tableViewYerp->verticalHeader()->setStretchLastSection(true);
    ui->tableViewYerp->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewYerp->horizontalScrollBar()->setSingleStep(3);
    ui->tableViewYerp->setSortingEnabled(false);

    modelPrey = new QStandardItemModel();
    QStringList labels = QString::fromUtf8("№, X(0), Y(0), Angle (deg), V, Died, Yerp, dieX, dieY").simplified().split(",");
    modelPrey->setHorizontalHeaderLabels(labels);
    for (int i = 0; i < 9; i++) modelPrey->horizontalHeaderItem(i)->setFont(QFont("MS Shell Dlg 2", 11));
    ui->tableViewPrey->setModel(modelPrey);
    ui->tableViewPrey->resizeRowsToContents();
    ui->tableViewPrey->resizeColumnsToContents();

    modelYerp = new QStandardItemModel();
    labels = QString::fromUtf8("№, X(0), Y(0), Plan, Time").simplified().split(",");
    modelYerp->setHorizontalHeaderLabels(labels);
    for (int i = 0; i < 5; i++) modelYerp->horizontalHeaderItem(i)->setFont(QFont("MS Shell Dlg 2", 11));
    ui->tableViewYerp->setModel(modelYerp);
    ui->tableViewYerp->resizeRowsToContents();
    ui->tableViewYerp->resizeColumnsToContents();
}
void MainWindow::fillFullYerpTable()
{
    for (Yerp* y : view->yerp) createYerpTableItem(y);

    ui->tableViewYerp->resizeColumnsToContents();
    ui->tableViewYerp->resizeRowsToContents();
}
void MainWindow::fillFullPreyTableAfter()
{
    for (Prey* p : view->prey) createPreyTableItem(p);

    ui->tableViewPrey->resizeColumnsToContents();
    ui->tableViewPrey->resizeRowsToContents();
}
void MainWindow::preyRowsRearrangement(QString plan) // Rearrange rows in tableViewPrey according to plan
{
    for (int i = 0; i < view->prey.size(); i++) {
        QList<QStandardItem *> removedRow = modelPrey->takeRow(preyRowWithNum(plan.split("-")[i].toInt()));
        modelPrey->insertRow(i, removedRow);
    }
}
int MainWindow::preyRowWithNum(int num)
{
    for (int k = 0; k < view->prey.size(); k++)
        if (modelPrey->data(modelPrey->index(k, 0), Qt::DisplayRole).toInt() == num) return k;

    return -1; // Failure code
}
QString MainWindow::planToRowsRearrangementByYerp()
{
    QString str = "";
    for (Yerp* y : view->yerp)
    {
        for (int num : y->curPlan)
        {
            str += QString::number(num)+"-";
        }
    }
    str.chop(1);

    return str;
}
QString MainWindow::planToRowsRearrangementByDieTime()
{
    if (view->yerp[0]->curPlan.size() == view->prey.size()) return view->yerp[0]->curPlanToQString();

    int i1 = 0;
    int i2 = 0;
    Yerp* y1 = view->yerp[0];
    Yerp* y2 = view->yerp[1];
    QVector<Prey* > preys = view->prey;
    QString str = "";
    while (i1+i2 != preys.size())
    {
        if (i1 == y1->curPlan.size())
        {
            str += QString::number(y2->curPlan[i2])+"-";
            i2++;
            continue;
        }
        if (i2 == y2->curPlan.size())
        {
            str += QString::number(y1->curPlan[i1])+"-";
            i1++;
            continue;
        }

        if (preys[y1->curPlan[i1]]->getDieTime() < preys[y2->curPlan[i2]]->getDieTime())
        {
            str += QString::number(y1->curPlan[i1])+"-";
            i1++;
        }
        else
        {
            str += QString::number(y2->curPlan[i2])+"-";
            i2++;
        }
    }
    str.chop(1);

    return str;
}
void MainWindow::preyRowsToInit()
{
    for (int i = 0; i < view->prey.size(); i++) {
        modelPrey->item(i, 5)->setText(QString(""));
        modelPrey->item(i, 6)->setText(QString(""));
        modelPrey->item(i, 7)->setText(QString(""));
        modelPrey->item(i, 8)->setText(QString(""));
    }

    QString resetPlan = "";
    for (int i = 0; i <= view->prey.size()-1; i++) resetPlan += i == view->prey.size()-1 ? QString("%1").arg(i) : QString("%1-").arg(i);
    preyRowsRearrangement(resetPlan);
}
void MainWindow::yerpRowsToInit()
{
    for (int i = 0; i < view->yerp.size(); i++) {
        modelYerp->item(2*i, 3)->setText("");
        modelYerp->item(2*i, 4)->setText("");

        modelYerp->item(2*i+1, 3)->setText(""); // *
        modelYerp->item(2*i+1, 4)->setText("");
    }
}
void MainWindow::fillTableDueToPreyCreation()
{
    createPreyTableItem(view->prey.last());

    ui->tableViewPrey->resizeColumnsToContents();
    ui->tableViewPrey->resizeRowsToContents();
}
void MainWindow::fillTableDueToYerpCreation()
{
    createYerpTableItem(view->yerp.last());

    ui->tableViewYerp->resizeColumnsToContents();
    ui->tableViewYerp->resizeRowsToContents();
}
void MainWindow::createPreyTableItem(Prey *p)
{
    QStandardItem* item;
    item = new QStandardItem(); // №
    item->setData(QString::number(modelPrey->rowCount(), 'f', 2).toDouble(), Qt::EditRole);
    item->setFont(QFont("MS Shell Dlg 2", 11, QFont::Bold));
    item->setForeground(QBrush(Qt::blue));
    item->setFlags(Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    modelPrey->setItem(modelPrey->rowCount(), 0, item);

    item = new QStandardItem(); // x0
    item->setData(QString::number(p->getStart().x(), 'f', 2).toDouble(), Qt::EditRole);
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    item->setTextAlignment(Qt::AlignCenter);
    modelPrey->setItem(modelPrey->rowCount() - 1, 1, item);

    item = new QStandardItem(); // y0
    item->setData(QString::number(p->getStart().y(), 'f', 2).toDouble(), Qt::EditRole);
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    item->setTextAlignment(Qt::AlignCenter);
    modelPrey->setItem(modelPrey->rowCount() - 1, 2, item);

    item = new QStandardItem(); // angle
    item->setData(QString::number(p->getAlpha(), 'f', 2).toDouble(), Qt::EditRole);
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    item->setTextAlignment(Qt::AlignCenter);
    modelPrey->setItem(modelPrey->rowCount() - 1, 3, item);

    item = new QStandardItem(); // velocity
    item->setData(QString::number(p->getV(), 'f', 2).toDouble(), Qt::EditRole);
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    item->setTextAlignment(Qt::AlignCenter);
    modelPrey->setItem(modelPrey->rowCount() - 1, 4, item);

    item = new QStandardItem(); // dieTime
    item->setFont(QFont("MS Shell Dlg 2", 11, QFont::Bold));
    item->setForeground(QBrush(Qt::blue));
    item->setFlags(Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    modelPrey->setItem(modelPrey->rowCount() - 1, 5, item);

    item = new QStandardItem(); // yerpNum
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    modelPrey->setItem(modelPrey->rowCount() - 1, 6, item);

    item = new QStandardItem(); // dieX
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    modelPrey->setItem(modelPrey->rowCount() - 1, 7, item);

    item = new QStandardItem(); // dieY
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    modelPrey->setItem(modelPrey->rowCount() - 1, 8, item);
}
void MainWindow::createYerpTableItem(Yerp *y)
{
    QStandardItem* item;
    item = new QStandardItem(); // №
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setData(QString::number(y->getYerpNum(), 'f', 2).toDouble(), Qt::EditRole);
    item->setFlags(Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    modelYerp->setItem(modelYerp->rowCount(), 0, item);
    item = new QStandardItem(); // №*
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setData(QString::number(y->getYerpNum())+"*", Qt::EditRole);
    item->setFlags(Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    modelYerp->setItem(modelYerp->rowCount(), 0, item);

    item = new QStandardItem(); // x0
    item->setData(QString::number(y->getStart().x(), 'f', 2).toDouble(), Qt::EditRole);
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    item->setTextAlignment(Qt::AlignCenter);
    modelYerp->setItem(modelYerp->rowCount() - 2, 1, item);
    item = new QStandardItem(); // x0*
    item->setData(QString::number(y->getStart().x(), 'f', 2).toDouble(), Qt::EditRole);
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    modelYerp->setItem(modelYerp->rowCount() - 1, 1, item);

    item = new QStandardItem(); // y0
    item->setData(QString::number(y->getStart().y(), 'f', 2).toDouble(), Qt::EditRole);
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    item->setTextAlignment(Qt::AlignCenter);
    modelYerp->setItem(modelYerp->rowCount() - 2, 2, item);
    item = new QStandardItem(); // y0*
    item->setData(QString::number(y->getStart().y(), 'f', 2).toDouble(), Qt::EditRole);
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    modelYerp->setItem(modelYerp->rowCount() - 1, 2, item);

    item = new QStandardItem(); // Plan
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    modelYerp->setItem(modelYerp->rowCount() - 2, 3, item);
    item = new QStandardItem(); // Plan*
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    modelYerp->setItem(modelYerp->rowCount() - 1, 3, item);

    item = new QStandardItem(); // Fly (working) time
    item->setFont(QFont("MS Shell Dlg 2", 11, QFont::Bold));
    item->setForeground(QBrush(Qt::blue));
    item->setFlags(Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    modelYerp->setItem(modelYerp->rowCount() - 2, 4, item);
    item = new QStandardItem(); // Fly (working) time*
    item->setFont(QFont("MS Shell Dlg 2", 11));
    item->setFlags(Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    modelYerp->setItem(modelYerp->rowCount() - 1, 4, item);
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
}
void MainWindow::saveTestDataToFile(FILE *f)
{
    int M = view->yerp.size();
    int N = view->prey.size();

    fprintf(f, "%d\n", M);
    for (Yerp* y : view->yerp) fprintf(f, "%lf,%lf\n", y->getStart().x(), y->getStart().y());
    fprintf(f, "%d\n", N);
    for (Prey* p : view->prey) fprintf(f, "%lf,%lf,%lf,%lf\n", p->getStart().x(), p->getStart().y(), p->getVx(), p->getVy());
    fprintf(f, "%lf\n", solver->getResT());
    for (Yerp* y : view->yerp)
    {
        QString tmp = y->curPlanToQString()+";"+QString::number(y->curPlanToQString().isEmpty() ? 0 : y->lastPrey->getDieTime(), 'f', 2)+";";
        fprintf(f, "%s", tmp.toStdString().c_str());
        tmp = y->plan4APToQString()+";"+QString::number(y->getPlan4APTime(), 'f', 2);
        fprintf(f, "%s\n", tmp.toStdString().c_str());
    }
    for (Prey* p : view->prey)
    {
        fprintf(f, "%d,%lf,%lf,%lf\n", p->getYerpNum(), p->getDieTime(), p->getDiePoint().x(), p->getDiePoint().y());
    }
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
    ui->progressBar->setValue(0); // Should be before test stuff because emit solve(view) causes progressBar to twinkle

    if (testFileNum != -1)
    {
        QString filename = "C:/Qt/MT-TSP/tests/" + QString::number(testFileNum) + ".txt";
        QFile f(filename);
        f.open(QIODevice::ReadOnly);

        int M, N;
        QString tmpLine;

        tmpLine = f.readLine();
        M = tmpLine.toInt(); // Catching # of Yerps
        for (int i = 0; i < M; i++) tmpLine = f.readLine();

        tmpLine = f.readLine();
        N = tmpLine.toInt(); // Catching # of Preys
        for (int i = 0; i < N; i++) tmpLine = f.readLine();

        QVector<int> ansYerpNum;
        QVector<double> ansDieT, ansDieX, ansDieY;
        double ansResT, ansCur1T, ansPlan4AP1T, ansCur2T, ansPlan4AP2T;
        QString ansCurPlanY1, ansPlan4APY1, ansCurPlanY2, ansPlan4APY2;

        tmpLine = f.readLine();
        ansResT = tmpLine.toDouble(); // Catching resT

        tmpLine = f.readLine();
        ansCurPlanY1 = tmpLine.split(";")[0];
        ansCur1T = tmpLine.split(";")[1].toDouble();
        ansPlan4APY1 = tmpLine.split(";")[2];
        ansPlan4AP1T = tmpLine.split(";")[3].toDouble();

        if (M == 2)
        {
            tmpLine = f.readLine();

            ansCurPlanY2 = tmpLine.split(";")[0];
            ansCur2T = tmpLine.split(";")[1].toDouble();
            ansPlan4APY2 = tmpLine.split(";")[2];
            ansPlan4AP2T = tmpLine.split(";")[3].toDouble();
        }

        for (int i = 0; i < N; i++)
        {
            tmpLine = f.readLine();

            ansYerpNum.push_back(tmpLine.split(",")[0].toInt());
            ansDieT.push_back(tmpLine.split(",")[1].toDouble());
            ansDieX.push_back(tmpLine.split(",")[2].toDouble());
            ansDieY.push_back(tmpLine.split(",")[3].toDouble());
        }
        f.close();

        if (fabs(solver->getResT()-ansResT) > 1.e-1)
        {
            testFileNum = -1;
            qDebug() << "Test failed. Result time issue.";
            return;
        }

        Yerp* y1 = view->yerp[0];
        if (ansCurPlanY1 != y1->curPlanToQString() ||
            ansPlan4APY1 != y1->plan4APToQString() ||
            fabs((y1->curPlanToQString().isEmpty() ? 0 : y1->lastPrey->getDieTime())-ansCur1T) > 1.e-1 ||
            fabs(y1->getPlan4APTime()-ansPlan4AP1T) > 1.e-1)
        {
            testFileNum = -1;
            qDebug() << "Test failed. First Yerp issue.";
            return;
        }

        Yerp* y2;
        if (M == 2)
        {
            y2 = view->yerp[1];
            if (ansCurPlanY2 != y2->curPlanToQString() ||
                ansPlan4APY2 != y2->plan4APToQString() ||
                fabs((y2->curPlanToQString().isEmpty() ? 0 : y2->lastPrey->getDieTime())-ansCur2T) > 1.e-1 ||
                fabs(y2->getPlan4APTime()-ansPlan4AP2T) > 1.e-1)
            {
                testFileNum = -1;
                qDebug() << "Test failed. Second Yerp issue.";
                return;
            }
        }

        Prey* tmpPrey;
        for (int i = 0; i < N; i++)
        {
            tmpPrey = view->prey[i];
            if (tmpPrey->getYerpNum() != ansYerpNum[i] ||
                fabs(tmpPrey->getDieTime()-ansDieT[i]) > 1.e-1 ||
                fabs(tmpPrey->getDiePoint().x()-ansDieX[i]) > 1.e-1 ||
                fabs(tmpPrey->getDiePoint().y()-ansDieY[i]) > 1.e-1)
            {
                testFileNum = -1;
                qDebug() << "Test failed. Prey issue.";
                return;
            }
        }

        qDebug() << filename + "." << "Tests passed: " + QString::number(testFileNum+1)+"/" + QString::number(testAmount);
        testFileNum++;
        oneTest();
        return;
    }

    enableUIAfterUsePlan();
    view->setEnabled(true);
    ui->actionClear->setEnabled(true);
    ui->actionLoad_from_file->setEnabled(true);
    ui->rBConstruction->setEnabled(true);
    ui->dSBTime->setMaximum(solver->getResT());
    ui->sliderTime->setMaximum(100*solver->getResT()-(int)(solver->getResT()*100) < 0.5 ? (int)(solver->getResT()*100) : (int)(solver->getResT()*100)+1);
    ui->labelT->setText(QString::number(solver->getResT(), 'f', 2));
    ui->buttonBestPlan->setEnabled(true);
    ui->actionUseBestPlan->setEnabled(true);

    for (Prey* p : view->prey)
    {
        p->sEll->hide();
        p->eEll->hide();
        p->line->hide();
        p->setPos(p->getSStart());
        p->setCurr(p->getStart());
    }

    setBestPlanToLineEditUsePlan();
    afterPlanFillTable();

    //===============//
    // Tests stuff
    if (!addTest || view->prey.size()+view->yerp.size() > 10) return;

    int i = 0;
    QString filename = "C:/Qt/MT-TSP/tests/" + QString::number(i) + ".txt";

    while (QFile(filename).exists())
    {
        i++;
        filename = "C:/Qt/MT-TSP/tests/" + QString::number(i) + ".txt";
    }

    FILE* f = fopen(filename.toStdString().c_str(), "w+"); // Saving all the data to the chosen file
    saveTestDataToFile(f);
    fclose(f);
    //===============//
}
void MainWindow::usePlanEnded()
{
    thread->exit(0);

    view->genRect->hide();
    view->eraseHlight();

    enableUIAfterUsePlan();

    double resT = qMax(view->yerp[0]->lastPrey->getDieTime(), view->yerp.size() == 2 ? view->yerp[1]->lastPrey->getDieTime() : view->yerp[0]->lastPrey->getDieTime());
    ui->labelT->setText(QString::number(resT, 'f', 2));
    ui->dSBTime->setMaximum(resT);
    ui->sliderTime->setMaximum(100*resT-(int)(resT*100) < 0.5 ? (int)(resT*100) : (int)(resT*100)+1);

    for (Prey* p : view->prey)
    {
        p->sEll->hide();
        p->eEll->hide();
        p->line->hide();
        p->setPos(p->getSStart());
        p->setCurr(p->getStart());
    }

    afterPlanFillTable();
}

void MainWindow::afterPlanFillTable()
{
    preyRowsRearrangement(planToRowsRearrangementByYerp());

    Prey* tmpPrey;
    for (int i = 0; i < view->yerp[0]->curPlan.size(); i++) // Preys from 1st Yerp
    {
        tmpPrey = view->prey[view->yerp[0]->curPlan[i]];
        modelPrey->item(i, 1)->setFlags(Qt::ItemIsEnabled);
        modelPrey->item(i, 2)->setFlags(Qt::ItemIsEnabled);
        modelPrey->item(i, 3)->setFlags(Qt::ItemIsEnabled);
        modelPrey->item(i, 4)->setFlags(Qt::ItemIsEnabled);
        modelPrey->item(i, 5)->setData(QString::number(tmpPrey->getDieTime(), 'f', 2).toDouble(), Qt::EditRole);
        modelPrey->item(i, 6)->setData(1., Qt::EditRole);
        modelPrey->item(i, 7)->setData(QString::number(tmpPrey->getDiePoint().x(), 'f', 2).toDouble(), Qt::EditRole);
        modelPrey->item(i, 8)->setData(QString::number(tmpPrey->getDiePoint().y(), 'f', 2).toDouble(), Qt::EditRole);
    }

    int k1 = view->yerp[0]->curPlan.size();
    for (int i = view->yerp[0]->curPlan.size(); i < view->prey.size(); i++) // Preys from 2nd Yerp
    {
        tmpPrey = view->prey[view->yerp[1]->curPlan[i-k1]];
        modelPrey->item(i, 1)->setFlags(Qt::ItemIsEnabled);
        modelPrey->item(i, 2)->setFlags(Qt::ItemIsEnabled);
        modelPrey->item(i, 3)->setFlags(Qt::ItemIsEnabled);
        modelPrey->item(i, 4)->setFlags(Qt::ItemIsEnabled);
        modelPrey->item(i, 5)->setData(QString::number(tmpPrey->getDieTime(), 'f', 2).toDouble(), Qt::EditRole);
        modelPrey->item(i, 6)->setData(2., Qt::EditRole);
        modelPrey->item(i, 7)->setData(QString::number(tmpPrey->getDiePoint().x(), 'f', 2).toDouble(), Qt::EditRole);
        modelPrey->item(i, 8)->setData(QString::number(tmpPrey->getDiePoint().y(), 'f', 2).toDouble(), Qt::EditRole);
    }
    ui->tableViewPrey->resizeColumnsToContents();
    ui->tableViewPrey->resizeRowsToContents();

    Yerp* y;
    for (int i = 0; i < view->yerp.size(); i++)
    {
        y = view->yerp[i];
        modelYerp->item(2*i, 1)->setFlags(Qt::ItemIsEnabled);
        modelYerp->item(2*i, 2)->setFlags(Qt::ItemIsEnabled);
        modelYerp->item(2*i, 3)->setData(y->curPlanToQString(), Qt::EditRole);
        modelYerp->item(2*i, 4)->setData(QString::number(y->curPlan.isEmpty() ? 0.: y->lastPrey->getDieTime(), 'f', 2).toDouble(), Qt::EditRole);

        modelYerp->item(2*i+1, 3)->setData(y->plan4APToQString(), Qt::EditRole);
        modelYerp->item(2*i+1, 4)->setData(QString::number(y->getPlan4APTime(), 'f', 2).toDouble(), Qt::EditRole);
    }
    ui->tableViewYerp->resizeColumnsToContents();
    ui->tableViewYerp->resizeRowsToContents();

    preyRowsRearrangement(planToRowsRearrangementByDieTime());
}
void MainWindow::enableUIAfterUsePlan()
{
    ui->rBAnimation->setEnabled(true);
    ui->rBAnimation->setChecked(true);
    ui->dSBTime->setEnabled(true);
    ui->dSBTime->setValue(0);
    ui->sliderTime->setEnabled(true);
    ui->sliderTime->setValue(0);
    ui->optimalZoomButton->setEnabled(true);
    ui->actionOptimalZoom->setEnabled(true);
    ui->playButton->setEnabled(true);
    ui->actionPlay->setEnabled(true);
    ui->speedUpButton->setEnabled(true);
    ui->actionSpeedUp->setEnabled(true);

    view->setStatus(StatusScene::animationMode);
    view->timer4Animation->stop();
}

void MainWindow::changeProgressBar(long long vC, long long vAll)
{
    ui->progressBar->setValue((int) ((double)vC / vAll * 100));
}

bool MainWindow::isDataReadyToUsePlan()
{
    if (view->getStatus() == StatusScene::settingPreyEnd || view->getStatus() == StatusScene::settingPreyVelocity) return false;
    if (view->yerp.size() > 2)
    {
        QMessageBox::critical(this, "MT-TSP", "Program supports only 1 or 2 Yerps");
        return false;
    }
    if (view->prey.size() == 0 || view->yerp.size() == 0)
    {
        QMessageBox::critical(this, "MT-TSP", "No Preys or Yerps");
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

void MainWindow::oneTest()
{
    on_actionClear_triggered();

    QString filename = "C:/Qt/MT-TSP/tests/" + QString::number(testFileNum) + ".txt";
    if (!QFile(filename).exists())
    {
        testFileNum = -1;
        qDebug() << "\nALL TESTS PASSED";
        return;
    }

    QFile f(filename);
    f.open(QIODevice::ReadOnly);

    QString tmpLine;
    int M, N;
    double x, y, vx, vy;

    tmpLine = f.readLine();
    M = tmpLine.toInt();
    for (int i = 0; i < M; i++)
    {
        tmpLine = f.readLine();

        x = tmpLine.split(",")[0].toDouble();
        y = tmpLine.split(",")[1].toDouble();
        Yerp* yerpInst = new Yerp(i, QPointF(x, y));
        view->yerp.push_back(yerpInst);
    }

    tmpLine = f.readLine();
    N = tmpLine.toInt();
    for (int i = 0; i < N; i++)
    {
        tmpLine = f.readLine();

        x = tmpLine.split(",")[0].toDouble();
        y = tmpLine.split(",")[1].toDouble();
        vx = tmpLine.split(",")[2].toDouble();
        vy = tmpLine.split(",")[3].toDouble();
        Prey* preyInst = new Prey(QPointF(x, y), QPointF(vx, vy));
        view->prey.push_back(preyInst);
    }
    f.close();

    thread->start();
    emit solve(view);
}
