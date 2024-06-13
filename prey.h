#ifndef PREY_H
#define PREY_H

#include <graphicsEntities.h>
#include <QGraphicsEllipseItem>

class Prey : public GraphicsEntities
{
public:
    QGraphicsEllipseItem* getSEll() {return sEll;}
    QGraphicsEllipseItem* getEEll() {return eEll;}
    QGraphicsLineItem* getLine() {return line;}
    QPointF getEnd() {return end;}
    QPointF getSEnd() {return sEnd;}
    double getVx() {return vx;}
    double getVy() {return vy;}
    double getAlpha() {return alpha;} // Degrees
    double getV() {return v;}
    void setEnd(QPointF e) {end = e;}
    void setSEnd(QPointF sE) {sEnd = sE;}
    void setAlpha(double ang) {alpha = ang;}
    void setV(double velAbs) {v = velAbs;}
    void setSEll(QGraphicsEllipseItem* ell) {sEll = ell;}
    void setEEll(QGraphicsEllipseItem* ell) {eEll = ell;}
    void setLine(QGraphicsLineItem* l) {line = l;}
    void deleteSEll() {if (scene()->items().indexOf(sEll) != -1) scene()->removeItem(sEll); delete(sEll);}
    void deleteEEll() {if (scene()->items().indexOf(eEll) != -1) scene()->removeItem(eEll); delete(eEll);}
    void deleteLine() {if (scene()->items().indexOf(line) != -1) scene()->removeItem(line); delete(line);}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

private:
    QGraphicsEllipseItem* sEll;
    QGraphicsEllipseItem* eEll;
    QGraphicsLineItem* line;
    QPointF end; // Stored in Math coords
    QPointF sEnd; // Stored in Scene coords
    double alpha;
    double v;
};

#endif // PREY_H
