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
#include <QMessageBox>

#define PI 3.1415926535

enum class StatusScene {settingPreyStart, settingPreyEnd, settingPreyVelocity, disabled};
class MyQGraphicsView : public QGraphicsView
{

public:
    MyQGraphicsView(QWidget *parent = 0);
    QVector<Prey* > prey;
    QVector<Yerp* > yerp;
    QPointF sceneToCoords(QPointF);
    QPointF coordsToScene(QPointF);
    QGraphicsScene* getScene() {return scene;}
    StatusScene getStatus() {return status;}
    void info();
    void setStatus(StatusScene s) {status = s;}
    void hideText() {text->hide();}
    void showText() {text->show();}
    void clear();
    void backAction();

public slots:
    void mousePressEvent(QMouseEvent * e) override;
    void mouseMoveEvent(QMouseEvent * e) override;
    void resizeEvent(QResizeEvent *e) override;

private:
    QGraphicsScene* scene;
    QGraphicsLineItem* coordLineX;
    QGraphicsLineItem* coordLineY;
    QVector<QGraphicsLineItem* > coordGridLine;
    QGraphicsTextItem* text;
    Arrow* arrow;
    StatusScene status = StatusScene::settingPreyStart;
    int unit{50}; // Pixels per 1 coord unit
    double distSqr(QPointF a, QPointF b) {return (a.x()-b.x())*(a.x()-b.x()) + (a.y()-b.y())*(a.y()-b.y());};
    double clamp(double value, double min, double max) {return value > max ? max : value < min ? min : value;};
    void textCoords(double x, double y);
    void textV(double v);
};

#endif // MYQGRAPCHICSVIEW_H
