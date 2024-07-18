#ifndef ARROW_H
#define ARROW_H

#include <graphicsEntities.h>
#include <math.h>

class Arrow : public GraphicsEntities
{
public:
    Arrow(QPointF, QPointF, double angle = 30, double length = 20);
    Arrow(double, double, double, double, double angle = 30, double length = 20);
    void setPen(QPen p) {pen = p;};
    void setLine(QPointF, QPointF);
    void setLine(double x1, double y1, double x2, double y2) {setLine(QPointF(x1, y1), QPointF(x2, y2));};
    QPointF getEnd() {return end;};
    QPointF getP1() {return p1;};
    QPointF getP2() {return p2;};

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

private:
    QPointF p1; // Stored in Scene coords
    QPointF p2; // Stored in Scene coords
    QPointF end; // Stored in Scene coords
    QPen pen = QPen(Qt::black);
    double angle;
    double length; // In pixels
};

#endif // ARROW_H
