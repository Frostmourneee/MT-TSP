#include "prey.h"

void Prey::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
QRectF Prey::boundingRect() const
{
    return QRectF(0, 0, 0, 0);
}
