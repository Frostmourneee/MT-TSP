#include "yerp.h"

void Yerp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);

    int rad = GraphicsEntities::smallGraphicsUnit;
    if (yerpNum == 0) {
        painter->drawLine(QLineF(QPointF(0, -2*rad), QPointF(0, 2*rad)));
        painter->drawLine(QLineF(QPointF(-2*rad+4, 2*rad), QPointF(2*rad-4, 2*rad)));
        painter->drawLine(QLineF(QPointF(0, -2*rad), QPointF(-2*rad+4, -4)));
    } else if (yerpNum == 1) {
        QPolygon pol;
        pol << QPoint(-2*rad,  -rad) <<
               QPoint(-rad,  -2*rad) <<
               QPoint(0,  -2*rad) <<
               QPoint(rad, -rad) <<
               QPoint(-2*rad,  2*rad) <<
               QPoint(rad,  2*rad);

        painter->drawPolyline(pol);
    }
}
QRectF Yerp::boundingRect() const
{
    int rad = GraphicsEntities::smallGraphicsUnit;
    return QRectF(-3*rad, -3*rad, 6*rad, 6*rad);
}
