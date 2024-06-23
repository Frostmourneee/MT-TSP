#ifndef YERP_H
#define YERP_H

#include <graphicsEntities.h>
#include <QPainter>
#include <prey.h>

class Yerp : public GraphicsEntities
{
public:
    Yerp(int num, QPointF st) : yerpNum{num}
    {start = st;}
    int getYerpNum() {return yerpNum;}
    QVector<int> bestPlan;
    QVector<int> plan4AP; // For all Preys
    QVector<int> curPlan; // For lineEditUsePlan
    Prey* lastPrey;
    Prey* firstPrey;

private:
    QPen pen = QPen(Qt::red, 3);
    int yerpNum;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void advance(int phase) override;
};

#endif // YERP_H
