#include "yerp.h"
#include "mainwindow.h"

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
void Yerp::advance(int phase)
{
    if (!phase || (vx == 0 && vy == 0)) return;

    double unit = dynamic_cast<MyQGraphicsView*>(scene()->parent())->getUnit();
    moveBy(vx*unit/100., -vy*unit/100.); // Timer shots 100 p/s, so movement velocity is V*unit pixels per second
    curr += QPointF(vx/100., vy/100.);
}

QString Yerp::plan4APToQString()
{
    QString str = "";
    for (int num : plan4AP) str += QString::number(num)+"-";
    str.chop(1);

    return str;
}

QString Yerp::curPlanToQString()
{
    QString str = "";
    for (int num : curPlan) str += QString::number(num)+"-";
    if (!str.isEmpty() && str[str.size()-1] == "-") str.chop(1);

    return str;
}
