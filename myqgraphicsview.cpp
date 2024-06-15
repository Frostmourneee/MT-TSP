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
    text->setPos(70, 50);
    text->setFont(QFont("Times", 20, QFont::Bold));
    scene->addItem(text);

    arrow = new Arrow(0, 0, 0, 0);
    arrow->hide();
    scene->addItem(arrow);

    coordLineX = new QGraphicsLineItem();
    coordLineY = new QGraphicsLineItem();
    scene->addItem(coordLineX);
    scene->addItem(coordLineY);

    genRect = new QGraphicsRectItem(0, 0, 100, 100);
    genRect->setPen(QPen(QBrush(Qt::blue), 1, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
    genRect->setBrush(QBrush(Qt::transparent));
    scene->addItem(genRect);

    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(10);
}

void MyQGraphicsView::mousePressEvent(QMouseEvent * e)
{
    if (e->button() != Qt::LeftButton && e->button() != Qt::RightButton) return;

    QPointF pScene = mapToScene(e->pos()); // Scene coords
    QPointF pMath = sceneToCoords(pScene); // Convinient "maths" coords

    if (e->button() == Qt::RightButton && status == StatusScene::settingPreyStart)
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
            if (onGenRect(pScene)) // Start resizing genRect
            {
                setCursor(QCursor(Qt::ClosedHandCursor));
                status = StatusScene::draggingGenRect;

                QRectF rect = genRect->rect();
                double x = pScene.x();
                double y = pScene.y();
                bool ts = fabs(y-rect.y()) < 5; // Top side of rect
                bool rs = fabs(x-(rect.x()+rect.width())) < 5; // Right side of rect
                bool bs = fabs(y-(rect.y()+rect.height())) < 5; // Bot side of rect
                bool ls = fabs(x-rect.x()) < 5; // Left side of genRect

                if (ts) side = GenRectSide::topSide;
                else if (rs) side = GenRectSide::rightSide;
                else if (bs) side = GenRectSide::botSide;
                else if (ls) side = GenRectSide::leftSide;
                return;
            }

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
            scene->addItem(preyInst);

            arrow->show();
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
            QPen pen = QPen(QBrush(QColor(0, 0, 0, 80)), 2, Qt::DashLine, Qt::RoundCap, Qt::BevelJoin);
            pen.setDashPattern(dashes);
            QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(arrow->getStart(), arrow->getEnd()));
            line->setPen(pen);
            scene->addItem(line);

            QPointF e_s = pMath - start;
            tmpPrey->setSEnd(pScene); // Data storage in Prey instance
            tmpPrey->setEnd(pMath);
            tmpPrey->setEEll(ellipse);
            tmpPrey->setLine(line);
            tmpPrey->setAlpha(fabs(e_s.x()) < 1.e-2 ? (e_s.y() > 0 ? 90 : -90) : 180/PI * atan2(e_s.y(), e_s.x()));

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

            arrow->hide();

            status = StatusScene::settingPreyStart;
            break;
        }
        default:
        {
            break;
        }
    }
}
void MyQGraphicsView::mouseMoveEvent(QMouseEvent* e)
{
    text->show();
    if (e->buttons() != Qt::NoButton && e->buttons() != Qt::LeftButton) return; // We need only movement or movement with Qt::LeftButton

    QPointF pScene = mapToScene(e->pos()); // Scene coords
    QPointF pMath = sceneToCoords(pScene); // Convinient "maths" coords
    if (onGenRect(pScene))
    {
        if (status == StatusScene::settingPreyStart) setCursor(QCursor(Qt::OpenHandCursor));
        if (status == StatusScene::draggingGenRect)
        {
            QRectF rect = genRect->rect();
            double x = pScene.x();
            double y = pScene.y();

            switch (side)
            {
                case GenRectSide::topSide:
                {
                    if (y < 20) return;

                    double deltaY = y-rect.y();
                    QRectF newRect = QRectF(rect.x(), y, rect.width(), rect.height() - deltaY);
                    genRect->setRect(newRect);
                    break;
                }
                case GenRectSide::rightSide:
                {
                    if (x > width()-20) return;

                    double deltaX = x-(rect.x()+rect.width());
                    QRectF newRect = QRectF(rect.x(), rect.y(), rect.width() + deltaX, rect.height());
                    genRect->setRect(newRect);
                    break;
                }
                case GenRectSide::botSide:
                {
                    if (y > height()-20) return;

                    double deltaY = y-(rect.y()+rect.height());
                    QRectF newRect = QRectF(rect.x(), rect.y(), rect.width(), rect.height() + deltaY);
                    genRect->setRect(newRect);
                    break;
                }
                case GenRectSide::leftSide:
                {
                    if (x < 20) return;

                    double deltaX = x-rect.x();
                    QRectF newRect = QRectF(x, rect.y(), rect.width() - deltaX, rect.height());
                    genRect->setRect(newRect);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
    else if (status != StatusScene::draggingGenRect) setCursor(QCursor(Qt::ArrowCursor));

    Prey* tmpPrey = prey.back();
    switch (status) {
        case StatusScene::settingPreyStart: // Just moving the cursor
        {
            textCoords(pMath.x(), pMath.y());

            break;
        }
        case StatusScene::settingPreyEnd: // Moving with Arrow
        {
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
        case StatusScene::settingPreyVelocity: // Moving while velocity setting
        {
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
        default:
        {
            break;
        }
    }
}
void MyQGraphicsView::mouseReleaseEvent(QMouseEvent *e)
{
    if (status == StatusScene::draggingGenRect)
    {
        status = StatusScene::settingPreyStart;
        side = GenRectSide::noSide;
        setCursor(QCursor(Qt::ArrowCursor));
    }

    Q_UNUSED(e);
}
void MyQGraphicsView::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);

    int w = width();
    int h = height();
    scene->setSceneRect(0, 0, w, h);

    QRectF rect = genRect->rect();
    double needRectW = rect.width() < w-20-rect.x() ? rect.width() : w-20-rect.x();
    double needRectH = rect.height() < h-20-rect.y() ? rect.height() : h-20-rect.y();
    QRectF newRect = QRectF(rect.x(), rect.y(), needRectW, needRectH).normalized();
    genRect->setRect(newRect);

    coordLineX->setLine(-w*0.49, 0, w*0.49, 0); // Main absciss line
    coordLineY->setLine(0, -h*0.49, 0, h*0.49); // Main ordinate line
    coordLineX->setPos(w / 2., h / 2.);
    coordLineY->setPos(w / 2., h / 2.);
    coordLineX->setPen(QPen(QBrush(Qt::black, Qt::SolidPattern), 3));
    coordLineY->setPen(QPen(QBrush(Qt::black, Qt::SolidPattern), 3));

    for (QGraphicsLineItem* l : coordGridLine)
    {
        scene->removeItem(l);
        delete l;
    }
    coordGridLine.clear();

    for (int i = 1; i < 0.98*w/(2*unit); i++) // Thin absciss lines, need to be renewed because amount of them isn't constant
    {
        QGraphicsLineItem* coordL = new QGraphicsLineItem(i*unit, -0.98*h/2., i*unit, 0.98*h/2.);
        coordL->setPos(w / 2., h / 2.);
        coordL->setPen(QPen(QColor(0, 0, 0, 130), 1, Qt::DotLine));
        coordGridLine.push_back(coordL);
        scene->addItem(coordL);

        coordL = new QGraphicsLineItem(-i*unit, -0.98*h/2., -i*unit, 0.98*h/2.);
        coordL->setPos(w / 2., h / 2.);
        coordL->setPen(QPen(QColor(0, 0, 0, 130), 1, Qt::DotLine));
        coordGridLine.push_back(coordL);
        scene->addItem(coordL);
    }

    for (int i = 1; i < 0.98*h/(2*unit); i++) // Thin ordinate lines, need to be renewed because amount of them isn't constant
    {
        QGraphicsLineItem* coordL = new QGraphicsLineItem(-0.98*w/2., i*unit, 0.98*w/2., i*unit);
        coordL->setPos(w / 2., h / 2.);
        coordL->setPen(QPen(QColor(0, 0, 0, 130), 1, Qt::DotLine));
        coordGridLine.push_back(coordL);
        scene->addItem(coordL);

        coordL = new QGraphicsLineItem(-0.98*w/2., -i*unit, 0.98*w/2., -i*unit);
        coordL->setPos(w / 2., h / 2.);
        coordL->setPen(QPen(QColor(0, 0, 0, 130), 1, Qt::DotLine));
        coordGridLine.push_back(coordL);
        scene->addItem(coordL);
    }

    for (Prey* p : prey) // Prey's ellipses and dotted line repositioning
    {
        int rad = GraphicsEntities::smallGraphicsUnit;
        p->setSStart(coordsToScene(p->getStart()));
        p->setSEnd(coordsToScene(p->getEnd()));

        QPointF st = p->getSStart();
        QPointF e = p->getSEnd();
        p->getSEll()->setRect(st.x() - rad, st.y() - rad, 2*rad, 2*rad);
        p->getEEll()->setRect(e.x() - rad, e.y() - rad, 2*rad, 2*rad);
        p->getLine()->setLine(QLineF(st, e));
    }

    for (Yerp* y : yerp) y->setSStart(coordsToScene(y->getStart())); // Yerp's repositioning
}

QPointF MyQGraphicsView::sceneToCoords(QPointF scenePoint) // Translate point from Scene coords to convinient "maths" coords
{
    int w = width();
    int h = height();

    QPointF pToCoordLineX = scenePoint - QPointF(w/2, h/2); // Data will be stored with 2 decimals for convenience
    return QPointF(round(pToCoordLineX.x()/unit * 100)/100, -1 * round(pToCoordLineX.y()/unit * 100)/100);
}
QPointF MyQGraphicsView::coordsToScene(QPointF coordPoint) // NOT LINEAR!!! Translate point from convinient "maths" coords to Scene coords
{
    int w = width();
    int h = height();

    QPointF pTocoordLineXInverse = unit*coordPoint - QPointF(0, 2*unit*coordPoint.y());
    return pTocoordLineXInverse + QPointF(w/2, h/2);
}

void MyQGraphicsView::textCoords(double x, double y)
{
    QString xStr = x < 0 ? QString::number(x, 'f', 2) : " " + QString::number(x, 'f', 2);
    QString yStr = y < 0 ? QString::number(y, 'f', 2) : " " + QString::number(y, 'f', 2);
    text->setFont(QFont("Times", 12, QFont::Bold));
    text->setPlainText(QString("%1; %2").arg(xStr).arg(yStr));
    text->setPos(QPointF(20, 20));
}
void MyQGraphicsView::textV(double v)
{
    text->setPlainText(tr("V = %1").arg(QString::number(v, 'f', 2)));
    text->setPos(QPointF(20, 20));
    text->setFont(QFont("Times", 12, QFont::Bold));
}

void MyQGraphicsView::backAction()
{
    switch (status) {
        case StatusScene::settingPreyStart: // Rollback to previous Prey velocity choosing
        {
            if (!yerp.isEmpty()) // Firstly Yerps will be removed
            {
                scene->removeItem(yerp.last());
                delete yerp.last();
                yerp.removeLast();
                return;
            }

            if (prey.isEmpty()) return;
            Prey* lastPrey = prey.last();
            arrow->setPen(QPen(QBrush(Qt::black), 4, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
            arrow->setLine(lastPrey->getSStart(), lastPrey->getSEnd());
            arrow->show();
            textV(0.99);

            status = StatusScene::settingPreyVelocity;

            break;
        }
        case StatusScene::settingPreyEnd: // Rollback to looking for Prey Start point
        {
            arrow->hide();
            prey.last()->deleteSEll();
            delete prey.last();
            prey.removeLast();
            status = StatusScene::settingPreyStart;

            break;
        }
        case StatusScene::settingPreyVelocity: // Rollback to looking for Prey End point
        {
            Prey* lastPrey = prey.last();
            lastPrey->deleteLine();
            lastPrey->deleteEEll();

            QPointF pSceneCursorPos = mapFromGlobal(QCursor::pos());
            arrow->setPen(QPen(QBrush(Qt::black), 2, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
            arrow->setLine(lastPrey->getSStart(), pSceneCursorPos);
            textCoords(sceneToCoords(pSceneCursorPos).x(), sceneToCoords(pSceneCursorPos).y());
            status = StatusScene::settingPreyEnd;

            break;
        }
        default:
        {
            break;
        }
    }
}
void MyQGraphicsView::clear()
{
    arrow->hide();

    status = StatusScene::settingPreyStart;

    for (Prey* p : prey)
    {
        p->deleteSEll();
        p->deleteEEll();
        p->deleteLine();
        delete p;
    }
    prey.clear();

    for (Yerp* y : yerp)
    {
        scene->removeItem(y);
        delete y;
    }
    yerp.clear();

}

bool MyQGraphicsView::onGenRect(QPointF pScene)
{
    double x = pScene.x();
    double y = pScene.y();

    QRectF rect = genRect->rect();
    return fabs(x-rect.x()) < 5 || fabs(x-(rect.x()+rect.width())) < 5 ||
           fabs(y-rect.y()) < 5 || fabs(y-(rect.y()+rect.height())) < 5 ||
           status == StatusScene::draggingGenRect;
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
    qDebug() << "Primitives in Scene" << scene->items().size();
}

