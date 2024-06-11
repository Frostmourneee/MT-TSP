#include "myqgraphicsview.h"

MyQGraphicsView::MyQGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    setMouseTracking(true);
    scene = new QGraphicsScene(0, 0, parent->width(), parent->height(), this);
    setScene(scene);

    setRenderHint(QPainter::Antialiasing);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    text = new QGraphicsTextItem("Move the cursor in the \n       working area");
    text->setPos(70, 70);
    text->setFont(QFont("Times", 20, QFont::Bold));
    scene->addItem(text);

    arrow = new Arrow(0, 0, 0, 0);
    arrow->setVisible(false);
    scene->addItem(arrow);

//First try to git!
}

void MyQGraphicsView::mousePressEvent(QMouseEvent * e)
{
    if (e->button() != Qt::LeftButton && e->button() != Qt::RightButton) return;

    QPointF pScene = mapToScene(e->pos()); // Scene coords
    QPointF pMath = sceneToCoords(pScene); // Convinient "maths" coords

    if (e->button() == Qt::RightButton)
    {
        if (yerp.size() == 2) return;

        Yerp* yerpInst = new Yerp(yerp.size(), pScene, pMath); // Click born Yerp instance
        scene->addItem(yerpInst);
        yerp.push_back(yerpInst);

        return;
    }

    Prey* tmpPrey = prey.back();
    switch (status) {
        case StatusScene::settingPreyStart: // Click borns the preyStart point
        {
            int r = GraphicsEntities::smallGraphicsUnit; // Blue Start point creation
            QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(pScene.x() - r, pScene.y() - r, 2*r, 2*r);
            ellipse->setPen(QPen(Qt::black));
            ellipse->setBrush(Qt::blue);
            scene->addItem(ellipse);

            Prey* preyInst = new Prey(); // Data storage in Prey instance
            preyInst->setSStart(pScene);
            preyInst->setStart(pMath);
            preyInst->setSEll(ellipse);
            prey.push_back(preyInst);

            arrow->setVisible(true);
            arrow->setPen(QPen(QBrush(Qt::black), 2, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
            arrow->setLine(pScene, pScene); // For refreshing previous

            status = StatusScene::settingPreyEnd;
            break;
        }
        case StatusScene::settingPreyEnd: // Click borns the preyEnd point
        {
            if (e->modifiers().testFlag(Qt::ShiftModifier)) {
                pScene = arrow->getEnd();
                pMath = sceneToCoords(pScene);
            }

            QPointF start = tmpPrey->getStart();
            if (fabs((start-pMath).x()) < 0.3 &&
                fabs((start-pMath).y()) < 0.3) return; // Too close Start and End seems weird

            int r = GraphicsEntities::smallGraphicsUnit; // Red end point creation
            QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(pScene.x() - r, pScene.y() - r, 2*r, 2*r);
            ellipse->setPen(QPen(Qt::black));
            ellipse->setBrush(Qt::red);
            scene->addItem(ellipse);

            QVector<qreal> dashes; // Line between Start and End
            dashes << 5.0 << 5.0;
            QPen* pen = new QPen(QBrush(QColor(0, 0, 0, 80)), 2, Qt::DashLine, Qt::RoundCap, Qt::BevelJoin);
            pen->setDashPattern(dashes);
            QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(arrow->getStart(), arrow->getEnd()));
            line->setPen(*pen);
            scene->addItem(line);

            tmpPrey->setSEnd(pScene); // Data storage in Prey instance
            tmpPrey->setEnd(pMath);
            tmpPrey->setEEll(ellipse);
            tmpPrey->setLine(line);
            tmpPrey->setAlpha(fabs(pMath.x() - start.x()) < 1.e-2 ?
                        (pMath.y() - start.y() > 0 ? 90 : -90) : 180/PI * atan2(pMath.y() - start.y(), pMath.x() - start.x()));

            arrow->setPen(QPen(QBrush(Qt::black), 4, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin)); // Preparing for velocity arrow
            arrow->setLine(coordsToScene(tmpPrey->getStart()), coordsToScene(tmpPrey->getEnd()));
            textV(0.99);

            status = StatusScene::settingPreyVelocity;
            break;
        }
        case StatusScene::settingPreyVelocity: // Click gives the velocity to the prey point (and this means Prey was fully born!)
        {
            textCoords(pMath.x(), pMath.y());

            double v = tmpPrey->getV();
            double alpha = tmpPrey->getAlpha();
            tmpPrey->setVel(v*cos(alpha*PI/180.), v*sin(alpha*PI/180.));

            arrow->setVisible(false);

            status = StatusScene::settingPreyStart;
            break;
        }
    }
}
void MyQGraphicsView::mouseMoveEvent(QMouseEvent * e)
{
    showText();
    if (e->buttons() != Qt::NoButton) return; // We need only movement without any signals

    QPointF pScene = mapToScene(e->pos()); // Scene coords
    QPointF pMath = sceneToCoords(pScene); // Convinient "maths" coords
    Prey* tmpPrey = prey.back();

    switch (status) {
        case StatusScene::settingPreyStart: {
            textCoords(pMath.x(), pMath.y());

            break;
        }
        case StatusScene::settingPreyEnd: {
            if (e->modifiers().testFlag(Qt::ShiftModifier)) {
                QPoint e_s = QPoint(pScene.toPoint().x() - coordsToScene(tmpPrey->getStart()).toPoint().x(),
                                    -pScene.toPoint().y() + coordsToScene(tmpPrey->getStart()).toPoint().y());
                bool isHorizontal = (e_s.y() <= e_s.x() && e_s.y() >= -e_s.x()) || (e_s.y() <= -e_s.x() && e_s.y() >= e_s.x());
                pScene = coordsToScene(tmpPrey->getStart()) + QPointF(isHorizontal ? pScene.x() - coordsToScene(tmpPrey->getStart()).x() : 0,
                                                           isHorizontal ? 0 : pScene.y() - coordsToScene(tmpPrey->getStart()).y());
                pMath = sceneToCoords(pScene);
            } // Horizontal or vertical arrow if shift is pressed

            textCoords(pMath.x(), pMath.y());

            arrow->setPen(QPen(QBrush(Qt::black), 2, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
            arrow->setLine(coordsToScene(tmpPrey->getStart()), pScene);

            break;
        }
        case StatusScene::settingPreyVelocity: {
            QPointF red = tmpPrey->getEnd(); // Preparing for velocity arrow
            QPointF blue = tmpPrey->getStart();
            QPointF resP;
            if (fabs(red.y() - blue .y()) < 1.e-2) resP = QPointF(pMath.x(), red.y());
            else if (fabs(red.x() - blue.x()) < 1.e-2) resP = QPointF(red.x(), pMath.y());
            else
            {
                double k = (red.y() - blue.y())/(red.x()-blue.x());
                double resX = (pMath.y()-red.y()+k*red.x()+1/k * pMath.x()) / (k+1/k);
                double resY = k*(resX-red.x())+red.y();
                resP = QPointF(resX, resY);
            }

            double v; // Velocity count
            if (distSqr(resP, red) > distSqr(blue, red)) v = 0.0;
            else
            {
                v = clamp(sqrt(distSqr(resP, blue) / distSqr(blue, red)), 0.01, 0.99);

                arrow->setPen(QPen(QBrush(Qt::black), 4, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
                arrow->setLine(coordsToScene(blue).x(), coordsToScene(blue).y(),
                        distSqr(resP, blue) > distSqr(blue, red) ? coordsToScene(red).x() : coordsToScene(resP).x(),
                        distSqr(resP, blue) > distSqr(blue, red) ? coordsToScene(red).y()  : coordsToScene(resP).y());
            }
            v = int(v*100. + 1.e-5) / 100.0;
            textV(v);

            tmpPrey->setV(v);

            break;
        }
    }
}
void MyQGraphicsView::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);

    scene->setSceneRect(0, 0, width(), height());
}

QPointF MyQGraphicsView::sceneToCoords(QPointF scenePoint) // Translate point from Scene coords to convinient "maths" coords
{
    int w = width();
    int h = height();

    QPointF pToLineX = scenePoint - QPointF(w/2, h/2);
    return QPointF(pToLineX.x() / unit, -1 * pToLineX.y() / unit);
}
QPointF MyQGraphicsView::coordsToScene(QPointF coordPoint) // NOT LINEAR!!! Translate point from convinient "maths" coords to Scene coords
{
    int w = width();
    int h = height();

    QPointF pToLineXInverse = unit*coordPoint - QPointF(0, 2*unit*coordPoint.y());
    return pToLineXInverse + QPointF(w/2, h/2);
}

QString MyQGraphicsView::doubleW2Decimals(double val)
{
    QString valStr = QString::number(val);

    if (valStr.indexOf('.') == -1) return valStr+QString(".00");
    else return valStr.split('.')[1].size() == 2 ? valStr : valStr+QString("0");
}
void MyQGraphicsView::textCoords(double x, double y)
{
    text->setFont(QFont("Times", 12, QFont::Bold));
    text->setPlainText(QString("%1; %2").arg(doubleW2Decimals(x)).arg(doubleW2Decimals(y)));
    text->setPos(QPointF(5, 5));
}
void MyQGraphicsView::textV(double v)
{
    text->setPlainText(tr("V = %1").arg(doubleW2Decimals(v)));
    text->setPos(QPointF(5, 5));
    text->setFont(QFont("Times", 12, QFont::Bold));
}

void MyQGraphicsView::info()
{
    qDebug() << "Preys created" << prey.size() <<
                "\nYerps created" << yerp.size() << '\n';

    qDebug() << "(sStart, sEnd, start, end, vx, vy, alpha, V)" << '\n';
    for (Prey* p : prey)
    {
        qDebug() << "(" << p->getSStart() << "," << p->getSEnd() << "," << p->getStart() << "," << p->getEnd() << "," << p->getVx() << "," << p->getVy() << "," << p->getAlpha() << p->getV() << ")" << '\n';
    }
    qDebug() << "(yerpNum, sStart, start)" << '\n';
    for (Yerp* y : yerp)
    {
        qDebug() << "(" << y->getYerpNum() << "," << y->getSStart() << "," << y->getStart() << '\n';
    }
}
