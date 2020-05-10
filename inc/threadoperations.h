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
                     FunctionParser&,
                     FunctionParser&);

    void parallelFunction();

    std::thread parallelFunctionThread() {
        return std::thread(&threadOperations::parallelFunction, this);
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
    FunctionParser *f1;
    FunctionParser *f2;
    int iteration;
};

#endif // THREADOPERATIONS_H
