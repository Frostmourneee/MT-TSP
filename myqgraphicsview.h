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
#include <QTimer>

#define PI 3.1415926535

enum class GenRectSide {noSide, topSide, rightSide, botSide, leftSide};
enum class StatusScene {settingPreyStart, settingPreyEnd, settingPreyVelocity, disabled, draggingGenRect, inAnimationMode};
class MyQGraphicsView : public QGraphicsView
{

public:
    MyQGraphicsView(QWidget *parent = 0);
    QPointF sceneToCoords(QPointF);
    QPointF coordsToScene(QPointF);
    QRectF getGenRect() {return genRect->rect();}
    QGraphicsScene* getScene() {return scene;}
    StatusScene getStatus() {return status;}
    int getUnit() {return unit;}
    void info();
    void setStatus(StatusScene s) {status = s;}
    void setVisibleText(bool b) {text->setVisible(b);}
    void setRectangle(QRectF r) {genRect->setRect(r);}
    void clear();
    void backAction();
    void textCoords(double x, double y);
    void createYerp(QPointF);
    void createPreyOnFullInfo(QPointF, QPointF, double);
    QVector<Prey* > prey;
    QVector<Yerp* > yerp;
    QTimer* timer;

public slots:
    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;

private:
    QGraphicsScene* scene;
    QGraphicsLineItem* coordLineX;
    QGraphicsLineItem* coordLineY;
    QVector<QGraphicsLineItem* > coordGridLine;
    QGraphicsRectItem* genRect;
    QGraphicsTextItem* text;
    Arrow* arrow;
    StatusScene status = StatusScene::settingPreyStart;
    GenRectSide side = GenRectSide::noSide;
    int unit{50}; // Pixels per 1 coord unit
    double distSqr(QPointF a, QPointF b) {return (a.x()-b.x())*(a.x()-b.x()) + (a.y()-b.y())*(a.y()-b.y());};
    double clamp(double value, double min, double max) {return value > max ? max : value < min ? min : value;};
    bool onGenRect(QPointF);
    void textV(double v);
};

#endif // MYQGRAPCHICSVIEW_H
