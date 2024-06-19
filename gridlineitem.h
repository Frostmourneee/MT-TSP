#ifndef GRIDLINEITEM_H
#define GRIDLINEITEM_H
#include <QGraphicsLineItem>

class GridLineItem : public QGraphicsLineItem
{
public:
    GridLineItem() : QGraphicsLineItem()
    {}
    GridLineItem(QPointF st, QPointF end, QPointF p) : QGraphicsLineItem(QLineF(st, end)), pos{p}
    {}
    GridLineItem(double stX, double stY, double endX, double endY, double pX, double pY) : QGraphicsLineItem(stX, stY, endX, endY), pos{QPointF(pX, pY)}
    {}
    QPointF getPos() {return pos;}

private:
    const QPointF pos;
};

#endif // GRIDLINEITEM_H
