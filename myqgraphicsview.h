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
#include <QObject>

#define PI 3.1415926535

enum class GenRectSide {noSide, topSide, rightSide, botSide, leftSide};
enum class StatusScene {settingPreyStart, settingPreyEnd, settingPreyVelocity, disabled, draggingGenRect, animationMode};
class MyQGraphicsView : public QGraphicsView
{
    Q_OBJECT
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
    void setResizeDueToOnOptionsButtonClicked(bool b) {resizeDueToOnOptionsButtonClicked = b;}
    void clear();
    void backAction();
    void textCoords(double x, double y);
    void createYerp(QPointF);
    /*Prey can be created by loading from file, by random generation or manually via mouse.
    In first two cases Prey is created with all its parameters (start, end, alpha, etc...) known.
    Despite of it, by mouse Prey is created only with its start position, so there is no full info about Prey at the creation moment.*/
    void createPreyOnFullInfo(QPointF, QPointF, double);
    void zoomGraphics(double);
    void translateGraphics(QPointF);
    void transformViewToOptimal();
    void preyTransform(Prey*, QPointF);
    void yerpTransform(Yerp*, QPointF);
    QVector<Prey* > prey;
    QVector<Yerp* > yerp;
    QTimer* timer4Animation;
    QGraphicsScene* scene;
    QGraphicsRectItem* genRect;

signals:
    void preyWasCreatedOrDestroyed();
    void yerpWasCreatedOrDestroyed();

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
    QVector<GridLineItem* > coordVerticalLines;
    QVector<GridLineItem* > coordHorizontalLines;
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
    bool resizeDueToOnOptionsButtonClicked = false;
};

#endif // MYQGRAPCHICSVIEW_H
