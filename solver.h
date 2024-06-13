#ifndef SOLVER_H
#define SOLVER_H

#include <QObject>

class Solver : public QObject
{
    Q_OBJECT
public:
    Solver(QObject *parent = nullptr) : QObject(parent)
    { }

signals:

};

#endif // SOLVER_H
