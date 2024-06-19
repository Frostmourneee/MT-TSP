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

    if (isDied) {
        painter->setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
        painter->setBrush(Qt::red);

        painter->drawLine(-rad, -rad, rad, rad);
        painter->drawLine(-rad, rad, rad, -rad);
    } else {
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(QBrush(QColor(0, 0, 255, dynamic_cast<MyQGraphicsView*>(scene()->parent())->getStatus() == StatusScene::animationMode ? 255 : 80)));

        painter->drawEllipse(-rad, -rad, 2*rad, 2*rad);
    }
}
QRectF Prey::boundingRect() const
{
    int rad = GraphicsEntities::smallGraphicsUnit;
    return QRectF(-2*rad, -2*rad, 4*rad, 4*rad);
}
void Prey::advance(int phase)
{
    if (!phase || (vx == 0 && vy == 0) || isDied) return;

    double unit = dynamic_cast<MyQGraphicsView*>(scene()->parent())->getUnit();
    moveBy(vx*unit/100., -vy*unit/100.); // Timer shots 100 p/s, so movement velocity is V*unit pixels per second
    curr += QPointF(vx/100., vy/100.);

    if (dynamic_cast<MyQGraphicsView*>(scene()->parent())->getStatus() == StatusScene::animationMode) return;
    QLineF e_s = QLineF(sStart, sEnd);
    QLineF cur_s = QLineF(sStart, pos());

    if (e_s.length() < cur_s.length())
    {
        setPos(sStart);
        curr = start;
    }
}
