#include "mainwindow.h"
#include "ui_mainwindow.h"

//TODO укрупнение сетки
//TODO после clear нужно добавить text = Переместите курсор
//TODO подумать над плавностью смены сотых долей в координатах
//TODO из-за симметрий быть может можно перебор уменьшить когда M = 2
//TODO прямоугольник ограничивающий происходящее
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

    setFixedSize(QSize(1440, 900));
    setFixedSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);

    view = new MyQGraphicsView(this);
    ui->vLScene->addWidget(view);
    view->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    //TODO clear()
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
        //TODO clear();
        return;
    }

    FILE* f = fopen(filename.toStdString().c_str(), "r");
    int M, N, r = GraphicsEntities::smallGraphicsUnit;;
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
        //TODO clear()
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
        preyInst->setAlpha(fabs(pMathEnd.x() - pMath.x()) < 1.e-2 ?
                    (pMathEnd.y() - pMath.y() > 0 ? 90 : -90) : 180/PI * atan2(pMathEnd.y() - pMath.y(), pMathEnd.x() - pMath.x()));
        preyInst->setVel(v*cos(alpha*PI/180.), v*sin(alpha*PI/180.));
        preyInst->setV(v);
    }

    fclose(f);
}

void MainWindow::on_actionStart_triggered()
{
    setFocus();
    if (!isDataReadyToStartProcess()) return;

    view->setDisabled(true);
    view->hideText();

    FILE* initDataFile = fopen("initData.txt", "w+"); // Saving all the data to the default "initData.txt" file
    saveDataToFile(initDataFile);


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

    view->hideText();
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

bool MainWindow::isDataReadyToStartProcess()
{
    if (view->getStatus() != StatusScene::settingPreyStart) return false;
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
