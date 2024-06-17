#ifndef PREY_H
#define PREY_H

#include <graphicsEntities.h>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <math.h>

class Prey : public GraphicsEntities
{
public:
    QGraphicsEllipseItem* getSEll() {return sEll;}
    QGraphicsEllipseItem* getEEll() {return eEll;}
    QGraphicsLineItem* getLine() {return line;}
    QPointF getEnd() {return end;}
    QPointF getSStart() {return sStart;}
    QPointF getSEnd() {return sEnd;}
    QPointF getDiePoint() {return start+dieTime*QPointF(vx, vy);}
    double getAlpha() {return alpha;} // Degrees
    double getV() {return v;}
    double getDieTime() {return dieTime;}
    double getYerpNum() {return yerpNum;}
    bool getIsDied() {return isDied;}
    void setEnd(QPointF e) {end = e;}
    void setSStart(QPointF sS) {sStart = sS;}
    void setSEnd(QPointF sE) {sEnd = sE;}
    void setAlpha(double ang) {alpha = ang;}
    void setV(double velAbs) {v = velAbs;}
    void setSEll(QGraphicsEllipseItem* ell) {sEll = ell;}
    void setEEll(QGraphicsEllipseItem* ell) {eEll = ell;}
    void setLine(QGraphicsLineItem* l) {line = l;}
    void setDieTime(double t) {dieTime = t;}
    void setYerpNum(int num) {yerpNum = num;}
    void setIsDied(bool b) {isDied = b;}
    void deleteSEll() {if (sEll == NULL) return; if (scene()->items().indexOf(sEll) != -1) scene()->removeItem(sEll); delete sEll; sEll = NULL;}
    void deleteEEll() {if (eEll == NULL) return; if (scene()->items().indexOf(eEll) != -1) scene()->removeItem(eEll); delete eEll; eEll = NULL;}
    void deleteLine() {if (line == NULL) return; if (scene()->items().indexOf(line) != -1) scene()->removeItem(line); delete line; line = NULL;}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void advance(int phase) override;

private:
    QGraphicsEllipseItem* sEll;
    QGraphicsEllipseItem* eEll;
    QGraphicsLineItem* line;
    QPointF end; // Stored in Math coords
    QPointF sStart; // Stored in Scene coords
    QPointF sEnd; // Stored in Scene coords
    double alpha;
    double v;
    double dieTime; // Interception moment
    int yerpNum; // Interceptor id
    bool isDied = false;
};

#endif // PREY_H
