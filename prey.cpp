#include "prey.h"
#include <mainwindow.h>

void Prey::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    int rad = GraphicsEntities::smallGraphicsUnit;
//    if (isHlighted) {
//        painter->setPen(QPen(QColor(255, 0, 255, 130), 3));
//        painter->setBrush(Qt::transparent);
//        painter->drawEllipse(sStart.x() - 2*rad,
//                             sStart.y() - 2*rad, 4*rad, 4*rad);
//    }

//    if (isDied) {
//        painter->setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
//        painter->setBrush(Qt::red);

//        painter->drawLine(sStart.x() - rad,
//                          sStart.y() - rad, sStart.x() + rad, sStart.y() + rad);
//        painter->drawLine(sStart.x() - rad,
//                          sStart.y() + rad, sStart.x() + rad, sStart.y() - rad);
//    } else {
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(QBrush(QColor(0, 0, 255, 80)));

        painter->drawEllipse(sStart.x() - rad, sStart.y() - rad, 2*rad, 2*rad);
//    }
}
QRectF Prey::boundingRect() const
{
    int rad = GraphicsEntities::smallGraphicsUnit;
    return QRectF(sStart.x() - 2*rad, sStart.y() - 2*rad, 4*rad, 4*rad);
}
void Prey::advance(int phase)
{
    //if (!phase || (vx == 0 && vy == 0) || isDied) return;
    if (!phase || (vx == 0 && vy == 0)) return;

    int unit = dynamic_cast<MyQGraphicsView*>(scene()->parent())->getUnit();
    moveBy(vx*(4*unit)/100., -vy*(4*unit)/100.);

//    if (dynamic_cast<MainWindow*>(scene()->parent()->parent()->parent())->isGifMode()) return;
    bool vxPrevailvy = fabs(vx) - fabs(vy) > 0;
    QPointF sceneE_S = dynamic_cast<MyQGraphicsView*>(scene()->parent())->coordsToScene(end) -
                       dynamic_cast<MyQGraphicsView*>(scene()->parent())->coordsToScene(start);
    if (vxPrevailvy ? (vx >= 0 && pos().x() > sceneE_S.x()) || (vx < 0 && pos().x() < sceneE_S.x()) :
                   (vy >= 0 && pos().y() < sceneE_S.y()) || (vy < 0 && pos().y() > sceneE_S.y())) {
        setPos(0, 0);
    }
}
