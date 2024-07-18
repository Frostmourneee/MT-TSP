#include "prey.h"
#include <mainwindow.h>

void Prey::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    int rad = GraphicsEntities::smallGraphicsUnit;

    QBrush blue = QBrush(Qt::blue);
    QBrush red = QBrush(Qt::red);
    QBrush lightBlue = QBrush(QColor(0, 0, 255, 80));
    bool isInAnimMode = dynamic_cast<MyQGraphicsView*>(scene()->parent())->getStatus() == StatusScene::animationMode;
    if (isHlighted)
    {
        painter->setPen(QPen(QColor(255, 0, 255, 130), 3));
        painter->setBrush(Qt::transparent);
        painter->drawEllipse(-2*rad, -2*rad, 4*rad, 4*rad);
    }

    if (isDied)
    {
        painter->setPen(QPen(yerpNum == 0 ? Qt::red : blue, 3, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
        painter->setBrush(yerpNum == 0 ? red : blue);

        painter->drawLine(-rad, -rad, rad, rad);
        painter->drawLine(-rad, rad, rad, -rad);
    }
    else
    {
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(isInAnimMode ? (yerpNum == 0 ? red : blue) : lightBlue);

        painter->drawEllipse(-rad, -rad, 2*rad, 2*rad);
    }
}
QRectF Prey::boundingRect() const
{
    int rad = GraphicsEntities::smallGraphicsUnit;
    return QRectF(-2*rad, -2*rad, 4*rad, 4*rad);
}
void Prey::advance(int phase)
{
    if (!phase || (vx == 0 && vy == 0) || isDied) return;

    double unit = dynamic_cast<MyQGraphicsView*>(scene()->parent())->getUnit();
    moveBy(vx*unit/100., -vy*unit/100.); // Timer shots 100 per sec, so movement velocity is V*unit pixels per second
    curr += QPointF(vx/100., vy/100.);

    if (dynamic_cast<MyQGraphicsView*>(scene()->parent())->getStatus() == StatusScene::animationMode) return;
    QLineF e_s = QLineF(sStart, sEnd);
    QLineF cur_s = QLineF(sStart, pos());

    if (e_s.length() < cur_s.length())
    {
        setPos(sStart);
        curr = start;
    }
}
