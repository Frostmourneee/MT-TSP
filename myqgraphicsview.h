#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsEllipseItem>
#include <arrow.h>
#include <prey.h>
#include <yerp.h>
#include <math.h>
#include <QGuiApplication>
#include <QDebug>

#define PI 3.1415926535

enum class StatusScene {settingPreyStart, settingPreyEnd, settingPreyVelocity};
class MyQGraphicsView : public QGraphicsView
{

public:
    MyQGraphicsView(QWidget *parent = 0);
    QPointF sceneToCoords(QPointF);
    QPointF coordsToScene(QPointF);
    void info();
    void hideText() {text->hide();}
    void showText() {text->show();}

public slots:
    void mousePressEvent(QMouseEvent * e) override;
    void mouseMoveEvent(QMouseEvent * e) override;
    void resizeEvent(QResizeEvent *e) override;

private:
    QVector<Prey* > prey;
    QVector<Yerp* > yerp;
    QGraphicsScene* scene;
    QGraphicsLineItem* coordLineX;
    QGraphicsLineItem* coordLineY;
    QVector<QGraphicsLineItem* > coordGridLine;
    QGraphicsTextItem* text;
    Arrow* arrow;
    QString doubleW2Decimals(double val);
    StatusScene status = StatusScene::settingPreyStart;
    int unit = 50; // Pixels per 1 coord unit
    double distSqr(QPointF a, QPointF b) {return (a.x()-b.x())*(a.x()-b.x()) + (a.y()-b.y())*(a.y()-b.y());};
    double clamp(double value, double min, double max) {return value > max ? max : value < min ? min : value;};
    void textCoords(double x, double y);
    void textV(double v);
};

#endif // MYQGRAPCHICSVIEW_H
