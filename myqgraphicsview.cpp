#include "myqgraphicsview.h"

MyQGraphicsView::MyQGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    setMouseTracking(true);
    scene = new QGraphicsScene(0, 0, parent->width(), parent->height(), this);
    setScene(scene);

    setRenderHint(QPainter::Antialiasing);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    text = new QGraphicsTextItem();
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
    QPointF pMath = sceneToCoords(pScene); // Convenient "maths" coords

    if (e->button() == Qt::RightButton)
    {
        if (yerp.size() == 2 || status != StatusScene::settingPreyStart) return;

        createYerp(pMath);

        return;
    }

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
            QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(-r, -r, 2*r, 2*r);
            ellipse->setPos(pScene);
            ellipse->setPen(QPen(Qt::black));
            ellipse->setBrush(Qt::blue);
            scene->addItem(ellipse);

            Prey* preyInst = new Prey(); // Data storage in Prey instance
            preyInst->setSStart(pScene);
            preyInst->setPos(pScene);
            preyInst->setStart(pMath);
            preyInst->setCurr(pMath);
            preyInst->sEll = ellipse;
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

            Prey* tmpPrey = prey.back();
            QPointF start = tmpPrey->getStart();
            if (fabs((start-pMath).x()) < 0.3 &&
                fabs((start-pMath).y()) < 0.3) return; // Too close Start and End seems weird

            int r = GraphicsEntities::smallGraphicsUnit; // Red end point creation
            QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(-r, -r, 2*r, 2*r);
            ellipse->setPos(pScene);
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
            tmpPrey->eEll = ellipse;
            tmpPrey->line = line;
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

            Prey* tmpPrey = prey.back();
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
    QPointF pMath = sceneToCoords(pScene); // Convenient "maths" coords
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

    switch (status) {
        case StatusScene::settingPreyEnd: // Moving with Arrow
        {
            Prey* tmpPrey = prey.back();
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
            Prey* tmpPrey = prey.back();
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
        default: // Just moving the cursor
        {
            textCoords(pMath.x(), pMath.y());

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
void MyQGraphicsView::wheelEvent(QWheelEvent *e)
{
    //if (status != StatusScene::animationMode && status != StatusScene::settingPreyStart)

    QPointF sAnchor = mapToScene(e->pos());
    anchor = sceneToCoords(sAnchor); // Should be before changing sceneSF because it affects sceneToCoords

    //===============// Calculating new sceneSF
    double aDelta = e->angleDelta().y();
    if (mouseSF == 1)
    {
        mouseSF += aDelta > 0 ? aDelta / 1200. : aDelta / 120000.; // +-0.1 || +-0.0001
    }
    else mouseSF += mouseSF > 1 ? aDelta / 1200. : aDelta / 120000.;

    mouseSF = clamp(mouseSF, 0.51, 50);
    sceneSF = mouseSF >= 1 ? mouseSF : 1/(1+100*(1-mouseSF)); // Zooming in or out from 1 to 100 with step 0.1 (zoom in 1, 1.1, 1.2, ..., 100 times or zoom out 1, 1.1, 1.2, ... 100 times
    sceneSF = aDelta > 0 ? 1.1 : 0.9;
    //===============//

    sCoordCenter = sAnchor + sceneSF*(sCoordCenter-sAnchor);
    zoomGraphics(sceneSF);
}
void MyQGraphicsView::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);

    int w = width();
    int h = height();
    scene->setSceneRect(0, 0, w, h);
    sCoordCenter = QPointF(w/2., h/2.);

    QRectF rect = genRect->rect();
    double needRectW = rect.width() < w-20-rect.x() ? rect.width() : w-20-rect.x(); // Stuff for checking whether genRect is smaller than scene or not
    double needRectH = rect.height() < h-20-rect.y() ? rect.height() : h-20-rect.y();
    QRectF newRect = QRectF(rect.x(), rect.y(), needRectW, needRectH).normalized();
    genRect->setRect(newRect);

    resizeCoordlines();

    for (Prey* p : prey) // Prey's ellipses and dotted line repositioning
    {
        QPointF newSStart = coordsToScene(p->getStart());
        QPointF delta = newSStart-p->getSStart();
        p->moveBy(delta.x(), delta.y());
        p->setSStart(newSStart);
        p->setSEnd(coordsToScene(p->getEnd()));

        QPointF st = p->getSStart();
        QPointF e = p->getSEnd();
        p->sEll->setPos(st);
        p->eEll->setPos(e);
        p->line->setLine(QLineF(st, e));
    }

    for (Yerp* y : yerp) // Yerp's repositioning
    {
        QPointF newSStart = coordsToScene(y->getStart());
        QPointF delta = newSStart-y->getSStart();
        y->moveBy(delta.x(), delta.y());
        y->setSStart(newSStart);
    }
}
void MyQGraphicsView::createYerp(QPointF pMath)
{
    if (yerp.size() == 2) return;

    Yerp* yerpInst = new Yerp(yerp.size(), pMath); // Click born Yerp instance
    yerpInst->setPos(coordsToScene(pMath));
    yerpInst->setSStart(coordsToScene(pMath));
    yerpInst->setCurr(pMath);
    scene->addItem(yerpInst);
    yerp.push_back(yerpInst);
}
void MyQGraphicsView::createPreyOnFullInfo(QPointF st, QPointF end, double v)
{
    Prey* preyInst = new Prey(); // Data storage in Prey and some rendering stuff
    QPointF pScene = coordsToScene(st);
    QPointF pSceneEnd = coordsToScene(end);
    QPointF e_s = end-st;
    double alpha = (fabs(e_s.x()) < 1.e-2 ? (e_s.y() > 0 ? 90 : -90) : 180/PI * atan2(e_s.y(), e_s.x()));
    int r = GraphicsEntities::smallGraphicsUnit;

    QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(-r, -r, 2*r, 2*r);
    ellipse->setPos(pScene);
    ellipse->setPen(QPen(Qt::black));
    ellipse->setBrush(Qt::blue);
    scene->addItem(ellipse);
    scene->addItem(preyInst);

    preyInst->setSStart(pScene);
    preyInst->setPos(pScene);
    preyInst->setStart(st);
    preyInst->setCurr(st);
    preyInst->sEll = ellipse;
    prey.push_back(preyInst);

    ellipse = new QGraphicsEllipseItem(-r, -r, 2*r, 2*r);
    ellipse->setPos(pSceneEnd);
    ellipse->setPen(QPen(Qt::black));
    ellipse->setBrush(Qt::red);
    scene->addItem(ellipse);

    QVector<qreal> dashes; // Line between Start and End
    dashes << 5.0 << 5.0;
    QPen pen = QPen(QBrush(QColor(0, 0, 0, 80)), 2, Qt::DashLine, Qt::RoundCap, Qt::BevelJoin);
    pen.setDashPattern(dashes);
    QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(pScene, pSceneEnd));
    line->setPen(pen);
    scene->addItem(line);

    preyInst->setSEnd(pSceneEnd); // Data storage in Prey instance
    preyInst->setEnd(end);
    preyInst->eEll = ellipse;
    preyInst->line = line;
    preyInst->setAlpha(alpha);
    preyInst->setVel(v*cos(alpha*PI/180.), v*sin(alpha*PI/180.));
    preyInst->setV(v);
}

void MyQGraphicsView::zoomGraphics(double scaleFactor)
{
    scaleFactor == 1 ? unit = baseUnit : unit *= scaleFactor;

    for (Prey* p : prey) preyTransform(p, p->getCurr());
    for (Yerp* y : yerp) yerpTransform(y, y->getCurr());

    if (!prey.isEmpty())
    {
        Prey* tmpPrey = prey.last();
        arrow->setLine(tmpPrey->getSStart(), status == StatusScene::settingPreyVelocity ? tmpPrey->getSEnd() : mapFromGlobal(QCursor::pos()));
    }

    resizeCoordlines();
}
void MyQGraphicsView::resizeCoordlines()
{
    for (GridLineItem* l : coordLinesX)
    {
        scene->removeItem(l);
        delete l;
    }
    for (GridLineItem* l : coordLinesY)
    {
        scene->removeItem(l);
        delete l;
    }
    coordLinesX.clear();
    coordLinesY.clear();

    int w = width();
    int h = height();
    QPointF sRD = QPointF(0.98*w, 0.98*h); // Scene right down point
    QPointF sLU = QPointF(0.02*w, 0.02*h); // Scene left up point
    QPointF rD = sceneToCoords(sRD);
    QPointF lU = sceneToCoords(sLU);
    int xMax = rD.x() > 0 ? floor(rD.x()) : floor(rD.x()) + 1;
    int xMin = lU.x() > 0 ? floor(lU.x()) : floor(lU.x()) + 1;
    int yMin = rD.y() > 0 ? floor(rD.y()) : floor(rD.y()) + 1;
    int yMax = lU.y() > 0 ? floor(lU.y()) : floor(lU.y()) + 1;
    if (xMax == 0) xMax = -1;
    if (xMin == 0) xMin = 1;
    if (yMax == 0) yMax = -1;
    if (yMin == 0) yMin = 1;

    coordLineX->setLine((sLU-sCoordCenter).x(), 0, (sRD-sCoordCenter).x(), 0); // Main absciss line
    coordLineY->setLine(0, (sLU-sCoordCenter).y(), 0, (sRD-sCoordCenter).y()); // Main ordinate line
    coordLineX->setPos(coordsToScene(QPointF(0, 0)));
    coordLineY->setPos(coordsToScene(QPointF(0, 0)));
    coordLineX->setPen(QPen(QBrush(Qt::black, Qt::SolidPattern), 3));
    coordLineY->setPen(QPen(QBrush(Qt::black, Qt::SolidPattern), 3));

    int idxAbsciss = -1;
    int idxOrdinate = -1;
    for (int i = xMin; i < xMax+1 && xMin != xMax; i++) // Thin vertical lines, need to be renewed because amount of them isn't constant
    {
        GridLineItem* coordL = new GridLineItem(0, (sLU-sCoordCenter).y(), 0, (sRD-sCoordCenter).y(), i, 0);
        coordL->setPos(coordsToScene(QPointF(i, 0)));
        coordL->setPen(QPen(QColor(0, 0, 0, 130), 1, Qt::DotLine));
        coordLinesX.push_back(coordL);
        scene->addItem(coordL);
        if (i == 0) idxAbsciss = coordLinesX.size()-1;
    }
    for (int i = yMin; i < yMax+1 && yMin != yMax; i++) // Thin horizontal lines, need to be renewed because amount of them isn't constant
    {
        GridLineItem* coordL = new GridLineItem((sLU-sCoordCenter).x(), 0, (sRD-sCoordCenter).x(), 0, 0, i);
        coordL->setPos(coordsToScene(QPointF(0, i)));
        coordL->setPen(QPen(QColor(0, 0, 0, 130), 1, Qt::DotLine));
        coordLinesY.push_back(coordL);
        scene->addItem(coordL);
        if (i == 0) idxOrdinate = coordLinesY.size()-1;
    }

    if (coordLinesX.size() < 2 && coordLinesY.size() < 2) return; //TODO странное место, подумать об ограничении на зум
    int linesInBaseUnit = baseUnit / (coordsToScene(coordLinesX[1]->getPos()).x() - coordsToScene(coordLinesX[0]->getPos()).x());
    if (linesInBaseUnit < 1) return; // No collapsing grid if distance among lines = 1 baseUnit (50 pixels) or less

    if (idxAbsciss == -1) {for (int i = 0; i < coordLinesX.size(); i++) if (i % linesInBaseUnit != linesInBaseUnit-1) coordLinesX[i]->hide();}
    else
    {
        for (int i = idxAbsciss+1; i < coordLinesX.size(); i++) if (i % linesInBaseUnit != idxAbsciss % linesInBaseUnit) coordLinesX[i]->hide();
        for (int i = idxAbsciss-1; i > -1; i--) if (i % linesInBaseUnit != idxAbsciss % linesInBaseUnit) coordLinesX[i]->hide();
    }
    if (idxOrdinate == -1) {for (int i = 0; i < coordLinesY.size(); i++) if (i % linesInBaseUnit != linesInBaseUnit-1) coordLinesY[i]->hide();}
    else
    {
        for (int i = idxOrdinate+1; i < coordLinesY.size(); i++) if (i % linesInBaseUnit != idxOrdinate % linesInBaseUnit) coordLinesY[i]->hide();
        for (int i = idxOrdinate-1; i > -1; i--) if (i % linesInBaseUnit != idxOrdinate % linesInBaseUnit) coordLinesY[i]->hide();
    }

    return;
}
void MyQGraphicsView::translateGraphics(Qt::Key key)
{
    if (status != StatusScene::animationMode) return;

    switch (key)
    {
        case Qt::Key_W:
        {
            sCoordCenter += QPointF(0, 5);
            for (Prey* p : prey) preyTransform(p, sceneToCoords(p->pos()+QPointF(0, 5)));
            for (Yerp* y : yerp) yerpTransform(y, sceneToCoords(y->pos()+QPointF(0, 5)));

            resizeCoordlines();
            break;
        }
        case Qt::Key_A:
        {
            sCoordCenter += QPointF(5, 0);
            for (Prey* p : prey) preyTransform(p, sceneToCoords(p->pos()+QPointF(5, 0)));
            for (Yerp* y : yerp) yerpTransform(y, sceneToCoords(y->pos()+QPointF(5, 0)));

            resizeCoordlines();
            break;
        }
        case Qt::Key_S:
        {
            sCoordCenter += QPointF(0, -5);
            for (Prey* p : prey) preyTransform(p, sceneToCoords(p->pos()+QPointF(0, -5)));
            for (Yerp* y : yerp) yerpTransform(y, sceneToCoords(y->pos()+QPointF(0, -5)));

            resizeCoordlines();
            break;
        }
        case Qt::Key_D:
        {
            sCoordCenter += QPointF(-5, 0);
            for (Prey* p : prey) preyTransform(p, sceneToCoords(p->pos()+QPointF(-5, 0)));
            for (Yerp* y : yerp) yerpTransform(y, sceneToCoords(y->pos()+QPointF(-5, 0)));

            resizeCoordlines();
            break;
        }
        default:
        {
            break;
        }
    }
}
void MyQGraphicsView::preyTransform(Prey* p, QPointF st)
{
    p->setPos(coordsToScene(st));
    p->setSStart(coordsToScene(p->getStart()));
    p->setSEnd(coordsToScene(p->getEnd()));
    p->sEll->setPos(p->getSStart()); // Impossible to have prey but not to have sEll
    if (p->eEll != NULL) p->eEll->setPos(p->getSEnd());
    if (p->line != NULL) p->line->setLine(QLineF(p->getSStart(), p->getSEnd()));
}
void MyQGraphicsView::yerpTransform(Yerp* y, QPointF st)
{
    y->setPos(coordsToScene(st));
    y->setSStart(coordsToScene(y->getStart()));
}

QPointF MyQGraphicsView::sceneToCoords(QPointF scenePoint) // Translate point from Scene coords to Convenient "maths" coords
{
    QPointF pToCoordLineX = scenePoint - sCoordCenter;
    return QPointF(pToCoordLineX.x()/unit, -1 * pToCoordLineX.y()/unit);
}
QPointF MyQGraphicsView::coordsToScene(QPointF coordPoint) // NOT LINEAR!!! Translate point from Convenient "maths" coords to Scene coords
{
    QPointF pToCoordLineXInverse = unit*coordPoint - QPointF(0, 2*unit*coordPoint.y());
    return sCoordCenter + pToCoordLineXInverse;
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
            lastPrey->setVel(0, 0);
            lastPrey->setPos(lastPrey->getSStart());
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
        qDebug() << "(" << p->getSStart() << "," << p->getSEnd() << "," << p->getStart() << "," << p->getEnd() << "," << p->getVx() << "," << p->getVy() << "," << p->getAlpha() << "," << p->getV() << ")" << p->pos() << '\n';
    }
    qDebug() << "(yerpNum, sStart, start)" << '\n';
    for (Yerp* y : yerp)
    {
        qDebug() << "(" << y->getYerpNum() << "," << coordsToScene(y->getStart()) << "," << y->getStart() << '\n';
    }
    qDebug() << "Primitives in Scene" << scene->items().size();
}

