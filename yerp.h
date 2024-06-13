#ifndef YERP_H
#define YERP_H

#include <graphicsEntities.h>
#include <QPainter>

class Yerp : public GraphicsEntities
{
public:
    Yerp(int num, QPointF sSt, QPointF st) : yerpNum{num}
    {sStart = sSt; start = st;}
    void setSStart(QPointF sSt) override {prepareGeometryChange(); sStart = sSt;}
    int getYerpNum() {return yerpNum;}

private:
    QPen pen = QPen(Qt::red, 3);
    int yerpNum;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
};

#endif // YERP_H
