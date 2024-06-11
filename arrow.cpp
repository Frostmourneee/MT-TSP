#include "arrow.h"

Arrow::Arrow(QPointF st, QPointF e, double ang, double len) : end{e}, angle{ang * 3.1415926535 / 180.}, length{len}
{
    start = st;
    QPointF r =  end - start;

    if (fabs(r.x()) < 5 && fabs(r.y()) < 5) // Too close Start and End seems weird
    {
        p1 = end;
        p2 = end;
        return;
    }

    QPointF rPerp = QPointF(-r.y(), r.x());
    QPointF vec1 = 1./sqrt(r.x()*r.x() + r.y()*r.y()) * (-r*cos(angle) + rPerp*sin(angle));
    QPointF vec2 = 1./sqrt(r.x()*r.x() + r.y()*r.y()) * (-r*cos(angle) - rPerp*sin(angle));

    p1 = end + vec1*length;
    p2 = end + vec2*length;
}
Arrow::Arrow(double x1, double y1, double x2, double y2, double ang, double len) : Arrow(QPointF(x1, y1), QPointF(x2, y2), ang, len)
{ }

void Arrow::setLine(QPointF st, QPointF e)
{
    prepareGeometryChange();
    start = st;
    end = e;

    QPointF r = end - start;

    if (fabs(r.x()) < 5 && fabs(r.y()) < 5) // Too close Start and End seems weird
    {
        p1 = end;
        p2 = end;
        update();

        return;
    }

    QPointF rPerp = QPointF(-r.y(), r.x());
    QPointF vec1 = 1./sqrt(r.x()*r.x() + r.y()*r.y()) * (-r*cos(angle) + rPerp*sin(angle));
    QPointF vec2 = 1./sqrt(r.x()*r.x() + r.y()*r.y()) * (-r*cos(angle) - rPerp*sin(angle));

    p1 = end + vec1*length;
    p2 = end + vec2*length;

    update();
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);

    painter->drawLine(QLineF(start, end));
    if (p1 != p2)
    {
        painter->drawLine(QLineF(end, p1));
        painter->drawLine(QLineF(end, p2));
    }
}
QRectF Arrow::boundingRect() const
{
    double lx = qMin(qMin(p1.x(), p2.x()), qMin(start.x(), end.x()));
    double rx = qMax(qMax(p1.x(), p2.x()), qMax(start.x(), end.x()));
    double ty = qMin(qMin(p1.y(), p2.y()), qMin(start.y(), end.y()));
    double by = qMax(qMax(p1.y(), p2.y()), qMax(start.y(), end.y()));

    return QRectF(lx, ty, rx - lx, by - ty);
}
