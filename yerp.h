#ifndef YERP_H
#define YERP_H

#include <graphicsEntities.h>
#include <QPainter>

class Yerp : public GraphicsEntities
{
public:
    Yerp(int num, QPointF sSt, QPointF st) : yerpNum{num}
    {sStart = sSt; start = st;}
    QVector<int> plan;
    QVector<int> plan4AP; // For all Preys
    int getYerpNum() {return yerpNum;}
    void setSStart(QPointF sSt) override {prepareGeometryChange(); sStart = sSt;}

private:
    QPen pen = QPen(Qt::red, 3);
    int yerpNum;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
};

#endif // YERP_H
