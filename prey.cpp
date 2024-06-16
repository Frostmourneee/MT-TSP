#include "prey.h"

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

        painter->drawEllipse(-rad, -rad, 2*rad, 2*rad);
//    }
}
QRectF Prey::boundingRect() const
{
    int rad = GraphicsEntities::smallGraphicsUnit;
    return QRectF(-2*rad, -2*rad, 4*rad, 4*rad);
}
void Prey::advance(int phase)
{
    //if (!phase || (vx == 0 && vy == 0) || isDied) return;
    if (!phase || (vx == 0 && vy == 0)) return;

    moveBy(2*vx, -2*vy); // Timer shots 100 p/s, so movement velocity is 100*2*V pixels per second

//    if (dynamic_cast<MainWindow*>(scene()->parent()->parent()->parent())->isGifMode()) return;
    QLineF e_s = QLineF(sStart, sEnd);
    QLineF cur_s = QLineF(sStart, pos());

    if (e_s.length() < cur_s.length()) setPos(sStart);
}
