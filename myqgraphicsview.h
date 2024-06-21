#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsEllipseItem>
#include <arrow.h>
#include <prey.h>
#include <yerp.h>
#include <math.h>
#include <gridlineitem.h>
#include <QGuiApplication>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>

#define PI 3.1415926535

enum class GenRectSide {noSide, topSide, rightSide, botSide, leftSide};
enum class StatusScene {settingPreyStart, settingPreyEnd, settingPreyVelocity, disabled, draggingGenRect, animationMode};
class MyQGraphicsView : public QGraphicsView
{

public:
    MyQGraphicsView(QWidget *parent = 0);
    QPointF sceneToCoords(QPointF);
    QPointF coordsToScene(QPointF);
    StatusScene getStatus() {return status;}
    double getBaseUnit() {return baseUnit;}
    double getUnit() {return unit;}
    void info();
    void setStatus(StatusScene s) {status = s;}
    void setVisibleText(bool b) {text->setVisible(b);}
    void setSF(double fact) {mouseSF = fact; sceneSF = mouseSF >= 1 ? mouseSF : 1/(1+100*(1-mouseSF));}
    void setAnchor(QPointF p) {anchor = p;}
    void setSCoordCenter(QPointF p) {sCoordCenter = p;}
    void clear();
    void backAction();
    void textCoords(double x, double y);
    void createYerp(QPointF);
    void createPreyOnFullInfo(QPointF, QPointF, double);
    void zoomGraphics(double);
    void translateGraphics(Qt::Key);
    void preyTransform(Prey*, QPointF);
    void yerpTransform(Yerp*, QPointF);
    QVector<Prey* > prey;
    QVector<Yerp* > yerp;
    QTimer* timer;
    QGraphicsScene* scene;
    QGraphicsRectItem* genRect;

public slots:
    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
    void wheelEvent(QWheelEvent *) override;
    void resizeEvent(QResizeEvent* e) override;

private:
    double distSqr(QPointF a, QPointF b) {return (a.x()-b.x())*(a.x()-b.x()) + (a.y()-b.y())*(a.y()-b.y());};
    double clamp(double value, double min, double max) {return value > max ? max : value < min ? min : value;};
    bool onGenRect(QPointF);
    void textV(double v);
    void resizeCoordlines();
    QGraphicsLineItem* coordLineX;
    QGraphicsLineItem* coordLineY;
    QVector<GridLineItem* > coordLinesX;
    QVector<GridLineItem* > coordLinesY;
    QGraphicsTextItem* text;
    Arrow* arrow;
    StatusScene status = StatusScene::settingPreyStart;
    GenRectSide side = GenRectSide::noSide;
    QPointF anchor = QPointF(0, 0); // Point of Math coordinates which won't move due to zoom transformsations
    QPointF sCoordCenter; // Point of the center of Math coords in scene coords
    const double baseUnit{50.}; // Pixels per 1 coord unit
    double unit{baseUnit}; // Pixels per 1 coord unit
    double mouseSF = 1;
    double sceneSF = 1;
};

#endif // MYQGRAPCHICSVIEW_H
