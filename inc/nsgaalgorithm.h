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
    explicit NSGAalgorithm(QVector<QPair<double,double>>,
                           QMap<QString,T>,
                           QMap<int,QString>,
                           QObject *parent = nullptr);

    virtual ~NSGAalgorithm(){
        delete this->function1;
        delete this->function2;
        delete this->genetic_functions;
    }
    void NSGA_MainLoop(void);

signals:

public slots:

private:
    FunctionParser *function1;
    FunctionParser *function2;
    Allele *genetic_functions;
    Population _current;
    Parameters _params;
    Borders _borders;
};

#endif // NSGAALGORITHM_H
