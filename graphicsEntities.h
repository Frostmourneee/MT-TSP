#ifndef GRAPHICSENTITIES_H
#define GRAPHICSENTITIES_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

class GraphicsEntities : public QGraphicsItem
{
public:
    GraphicsEntities()
    { }

    QPointF getStart() {return start;};
    QPointF getSStart() {return sStart;}
    double getVx() {return vx;}
    double getVy() {return vy;}
    void setStart(QPointF st) {start = st;}
    void setSStart(QPointF sS) {sStart = sS;}
    void setVel(double velx, double vely) {vx = velx; vy = vely;}
    static const int smallGraphicsUnit = 5; // Pixels

protected:
    QPointF start; // Stored in Scene coords for Arrow, in Math coords for Prey, Yerp
    QPointF sStart; // Stored in Scene coords
    double vx = 0;
    double vy = 0;
};

#endif // GRAPHICSENTITIES_H
