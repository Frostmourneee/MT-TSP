#ifndef GRAPHICSENTITIES_H
#define GRAPHICSENTITIES_H

#include <QGraphicsItem>

class GraphicsEntities : public QGraphicsItem
{
public:
    GraphicsEntities()
    { }

    QPointF getStart() {return start;};
    QPointF getSStart() {return sStart;};
    void setStart(QPointF st) {start = st;}
    virtual void setSStart(QPointF sSt) {sStart = sSt;}
    void setVel(double velx, double vely) {vx = velx; vy = vely;}
    static const int smallGraphicsUnit = 5; // Pixels

protected:
    QPointF start; // Stored in Scene coords for Arrow, in Math coords for Prey, Yerp
    QPointF sStart; // For Prey and Yerp
    double vx;
    double vy;
};

#endif // GRAPHICSENTITIES_H
