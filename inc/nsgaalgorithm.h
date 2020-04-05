#ifndef NSGAALGORITHM_H
#define NSGAALGORITHM_H

#include <QMainWindow>
#include <QObject>
#include <QVector>
#include <QDebug>
#include <QPair>
#include <QMap>
#include <random>

#include "allele.h"
//#include "functionparser.h"

class NSGAalgorithm : public QObject
{
    Q_OBJECT
public:
    explicit NSGAalgorithm(QVector<QPair<double,double>>,QMap<QString,T>,QMap<int,QString>, QObject *parent = nullptr);

signals:

public slots:

private:
    FunctionParser *function1;
    FunctionParser *function2;
    Population _current;
    QMap<QString,T> _params;

};

#endif // NSGAALGORITHM_H
