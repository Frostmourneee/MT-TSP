#ifndef PREY_H
#define PREY_H

#include <graphicsEntities.h>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <math.h>

class Prey : public GraphicsEntities
{
public:
    Prey(QPointF st, QPointF vel)
    {
        start = st;
        vx = vel.x();
        vy = vel.y();
    }
    Prey()
    { }
    QPointF getEnd() {return end;}
    QPointF getSEnd() {return sEnd;}
    QPointF getDiePoint() {return start+dieTime*QPointF(vx, vy);}
    double getAlpha() {return alpha;} // Degrees
    double getV() {return v;}
    double getDieTime() {return dieTime;}
    int getYerpNum() {return yerpNum;}
    bool getIsDied() {return isDied; update();}
    void setEnd(QPointF e) {end = e;}
    void setSEnd(QPointF sE) {sEnd = sE;}
    void setAlpha(double ang) {alpha = ang;}
    void setV(double velAbs) {v = velAbs;}
    void setDieTime(double t) {dieTime = t;}
    void setYerpNum(int num) {yerpNum = num;}
    void setIsDied(bool b) {isDied = b;}
    void deleteSEll() {if (sEll == NULL) return; if (scene()->items().indexOf(sEll) != -1) scene()->removeItem(sEll); delete sEll; sEll = NULL;}
    void deleteEEll() {if (eEll == NULL) return; if (scene()->items().indexOf(eEll) != -1) scene()->removeItem(eEll); delete eEll; eEll = NULL;}
    void deleteLine() {if (line == NULL) return; if (scene()->items().indexOf(line) != -1) scene()->removeItem(line); delete line; line = NULL;}
    QGraphicsEllipseItem* sEll = NULL;
    QGraphicsEllipseItem* eEll = NULL;
    QGraphicsLineItem* line = NULL;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void advance(int phase) override;

private:
    QPointF end; // Stored in Math coords
    QPointF sEnd; // Stored in Scene coords
    double alpha;
    double v;
    double dieTime; // Interception moment
    int yerpNum; // Interceptor id
    bool isDied = false;
};

#endif // PREY_H
