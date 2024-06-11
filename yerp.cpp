#include "yerp.h"

void Yerp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);

    int rad = GraphicsEntities::smallGraphicsUnit;
    if (yerpNum == 0) {
        painter->drawLine(QLineF(sStart + QPointF(0, -2*rad), sStart + QPointF(0, 2*rad)));
        painter->drawLine(QLineF(sStart + QPointF(-2*rad+4, 2*rad), sStart + QPointF(2*rad-4, 2*rad)));
        painter->drawLine(QLineF(sStart + QPointF(0, -2*rad), sStart + QPointF(-2*rad+4, -4)));
    } else if (yerpNum == 1) {
        QPolygon pol;
        pol << QPoint(sStart.x() - 2*rad, sStart.y() - rad) <<
               QPoint(sStart.x() - rad, sStart.y() - 2*rad) <<
               QPoint(sStart.x(), sStart.y() - 2*rad) <<
               QPoint(sStart.x() + rad, sStart.y() - rad) <<
               QPoint(sStart.x() - 2*rad, sStart.y() + 2*rad) <<
               QPoint(sStart.x() + rad, sStart.y() + 2*rad);

        painter->drawPolyline(pol);
    }
}
QRectF Yerp::boundingRect() const
{
    int rad = GraphicsEntities::smallGraphicsUnit;
    return QRectF(sStart.x() - 3*rad, sStart.y() - 3*rad, 6*rad, 6*rad);
}
