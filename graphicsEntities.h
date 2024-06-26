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

    static const int smallGraphicsUnit = 7; // In pixels

    QPointF getStart() {return start;};
    QPointF getSStart() {return sStart;}
    QPointF getCurr() {return curr;}
    double getVx() {return vx;}
    double getVy() {return vy;}
    bool getIsHlighted() {return isHlighted;}
    void setStart(QPointF st) {start = st;}
    void setSStart(QPointF sS) {sStart = sS;}
    void setCurr(QPointF p) {curr = p;}
    void setVel(double velx, double vely) {vx = velx; vy = vely;}
    void setVel(QPointF vec) {vx = vec.x(); vy = vec.y();}
    void setIsHlighted(bool b) {isHlighted = b; update();}

protected:
    QPointF start; // Stored in Scene coords for Arrow, in Math coords for Prey, Yerp
    QPointF sStart; // Stored in Scene coords
    QPointF curr = start; // Current pos stored in Math coords
    double vx = 0;
    double vy = 0;
    bool isHlighted = false;
};

#endif // GRAPHICSENTITIES_H
