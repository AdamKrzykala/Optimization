#ifndef THREADOPERATIONS_H
#define THREADOPERATIONS_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QDebug>
#include "functionparser.h"
#include <thread>
#include <mutex>

//Structures for decymal Population
typedef QMap< QString, double > Adaptation;
typedef QVector< T > Genotype;
typedef QPair< Genotype, Adaptation > Individual;
typedef QVector< Individual > Population;


class threadOperations
{

public:
    threadOperations(Population,
                     QMap< int, QString > _functionsPostures);

    void parallelFunction1();
    void parallelFunction2();
    void parallelFunction3();
    void parallelFunction4();

    std::thread parallelFunctionThread1() {
        return std::thread(&threadOperations::parallelFunction1, this);
    }
    std::thread parallelFunctionThread2() {
        return std::thread(&threadOperations::parallelFunction2, this);
    }
    std::thread parallelFunctionThread3() {
        return std::thread(&threadOperations::parallelFunction3, this);
    }
    std::thread parallelFunctionThread4() {
        return std::thread(&threadOperations::parallelFunction4, this);
    }

    QVector<QVector<int>> returnDominated(){
        return this->dominated;
    }
    QVector<int> returnCounters(){
        return this->counters;
    }

private:

    int pop_size;
    QVector<QVector<int>> dominated;
    QVector<int> counters;
    Population t_population;
    QVector<QPair<FunctionParser,FunctionParser>> FunctionContainer;
    FunctionParser *f1;
    FunctionParser *f2;
    FunctionParser *f3;
    FunctionParser *f4;
    FunctionParser *f5;
    FunctionParser *f6;
    FunctionParser *f7;
    FunctionParser *f8;
    int iteration;
};

#endif // THREADOPERATIONS_H
