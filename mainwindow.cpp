#include "mainwindow.h"
#include "ui_mainwindow.h"

//TODO укрупнение сетки
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
    resize(QSize(1440, 900));
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);

    view = new MyQGraphicsView(this);
    ui->vLScene->addWidget(view);
    view->setRectangle(QRectF(20, 20, 1318, 773));
    view->setFocus();

    thread = new QThread(this);
    connect(this, SIGNAL(destroyed()), thread, SLOT(quit()));

    solver = new Solver();
    connect(this, SIGNAL(solve(MyQGraphicsView*)), solver, SLOT(solve(MyQGraphicsView*)));
    connect(solver, SIGNAL(solvingEnded()), this, SLOT(solvingEnded()));
    solver->moveToThread(thread);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClear_triggered()
{
    setFocus();

    view->clear();
    QPointF pMathCursorPos = view->sceneToCoords(view->mapFromGlobal(QCursor::pos()));
    double x = pMathCursorPos.x();
    double y = pMathCursorPos.y();
    view->textCoords(x + 0.02, y - 0.02);
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
    QRectF genRect = view->getGenRect();
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
    int r = GraphicsEntities::smallGraphicsUnit;

    int parts;
    double r2fValue, x, y, alpha, v, xEnd, yEnd;
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

        Yerp* yerpInst = new Yerp(view->yerp.size(), view->coordsToScene(QPointF(x, y)), QPointF(x, y));
        view->getScene()->addItem(yerpInst);
        view->yerp.push_back(yerpInst);
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

        QPointF e_s(xEnd - x, yEnd - y);
        alpha = (fabs(e_s.x()) < 1.e-2 ? (e_s.y() > 0 ? 90 : -90) : 180/PI * atan2(e_s.y(), e_s.x()));

        Prey* preyInst = new Prey(); // Data storage in Prey and some rendering stuff
        QPointF pScene = view->coordsToScene(QPointF(x, y));
        QPointF pSceneEnd = view->coordsToScene(QPointF(xEnd, yEnd));
        QPointF pMath = QPointF(x, y);
        QPointF pMathEnd = QPointF(xEnd, yEnd);
        QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(pScene.x() - r, pScene.y() - r, 2*r, 2*r);
        ellipse->setPen(QPen(Qt::black));
        ellipse->setBrush(Qt::blue);
        view->getScene()->addItem(ellipse);
        view->getScene()->addItem(preyInst);

        preyInst->setSStart(pScene);
        preyInst->setStart(pMath);
        preyInst->setSEll(ellipse);
        view->prey.push_back(preyInst);

        ellipse = new QGraphicsEllipseItem(pSceneEnd.x() - r, pSceneEnd.y() - r, 2*r, 2*r);
        ellipse->setPen(QPen(Qt::black));
        ellipse->setBrush(Qt::red);
        view->getScene()->addItem(ellipse);

        QVector<qreal> dashes; // Line between Start and End
        dashes << 5.0 << 5.0;
        QPen pen = QPen(QBrush(QColor(0, 0, 0, 80)), 2, Qt::DashLine, Qt::RoundCap, Qt::BevelJoin);
        pen.setDashPattern(dashes);
        QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(pScene, pSceneEnd));
        line->setPen(pen);
        view->getScene()->addItem(line);

        preyInst->setSEnd(pSceneEnd); // Data storage in Prey instance
        preyInst->setEnd(pMathEnd);
        preyInst->setEEll(ellipse);
        preyInst->setLine(line);
        preyInst->setAlpha(alpha);
        preyInst->setVel(v*cos(alpha*PI/180.), v*sin(alpha*PI/180.));
        preyInst->setV(v);
    }
}
void MainWindow::on_actionStart_triggered()
{
    setFocus();
    if (!isDataReadyToStartProcess()) return;

    enableUI(false);

    FILE* initDataFile = fopen("initData.txt", "w+"); // Saving all the data to the default "initData.txt" file
    saveDataToFile(initDataFile);

    thread->start();
    emit solve(view);
}
void MainWindow::solvingEnded()
{
    enableUI(true);

    thread->exit(0);
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
    int M, N, r = GraphicsEntities::smallGraphicsUnit;
    double x, y, alpha, v, xEnd, yEnd;
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

        Yerp* yerpInst = new Yerp(view->yerp.size(), view->coordsToScene(QPointF(x, y)), QPointF(x, y));
        view->getScene()->addItem(yerpInst);
        view->yerp.push_back(yerpInst);
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
        alpha = strtod(tmpstr1, &tmpstr1);
        tmpstr1 = strtok(NULL," ");
        v = strtod(tmpstr1, &tmpstr1);
        tmpstr1 = strtok(NULL," ");
        xEnd = strtod(tmpstr1, &tmpstr1);
        tmpstr1 = strtok(NULL," ");
        yEnd = strtod(tmpstr1, &tmpstr1);

        Prey* preyInst = new Prey(); // Data storage in Prey and some rendering stuff
        QPointF pScene = view->coordsToScene(QPointF(x, y));
        QPointF pSceneEnd = view->coordsToScene(QPointF(xEnd, yEnd));
        QPointF pMath = QPointF(x, y);
        QPointF pMathEnd = QPointF(xEnd, yEnd);
        QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(pScene.x() - r, pScene.y() - r, 2*r, 2*r);
        ellipse->setPen(QPen(Qt::black));
        ellipse->setBrush(Qt::blue);
        view->getScene()->addItem(ellipse);
        view->getScene()->addItem(preyInst);

        preyInst->setSStart(pScene);
        preyInst->setStart(pMath);
        preyInst->setSEll(ellipse);
        view->prey.push_back(preyInst);

        ellipse = new QGraphicsEllipseItem(pSceneEnd.x() - r, pSceneEnd.y() - r, 2*r, 2*r);
        ellipse->setPen(QPen(Qt::black));
        ellipse->setBrush(Qt::red);
        view->getScene()->addItem(ellipse);

        QVector<qreal> dashes; // Line between Start and End
        dashes << 5.0 << 5.0;
        QPen pen = QPen(QBrush(QColor(0, 0, 0, 80)), 2, Qt::DashLine, Qt::RoundCap, Qt::BevelJoin);
        pen.setDashPattern(dashes);
        QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(pScene, pSceneEnd));
        line->setPen(pen);
        view->getScene()->addItem(line);

        preyInst->setSEnd(pSceneEnd); // Data storage in Prey instance
        preyInst->setEnd(pMathEnd);
        preyInst->setEEll(ellipse);
        preyInst->setLine(line);
        preyInst->setAlpha(alpha);
        preyInst->setVel(v*cos(alpha*PI/180.), v*sin(alpha*PI/180.));
        preyInst->setV(v);
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
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
        case Qt::Key_I:
        case 1064: {
            if (!e->modifiers().testFlag(Qt::ControlModifier)) return; // +Ctrl pressed

            view->info();
            break;
        }
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent * e) {
    Q_UNUSED(e);

    view->setVisibleText(false);
}

void MainWindow::enableUI(bool shouldEnable)
{
    view->setEnabled(shouldEnable);
    view->setVisibleText(shouldEnable);
    view->setStatus(shouldEnable ? StatusScene::settingPreyStart : StatusScene::disabled);
    ui->actionClear->setEnabled(shouldEnable);
    ui->actionStart->setEnabled(shouldEnable);
    ui->actionLoad_from_file->setEnabled(shouldEnable);
    ui->actionRandom->setEnabled(shouldEnable);
    ui->actionBack->setEnabled(shouldEnable);
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
