#include "nsgaalgorithm.h"

NSGAalgorithm::NSGAalgorithm(QVector<QPair<double,double>> borders,
                             QMap<QString,T> params,
                             QMap<int,QString> functions,
                             QObject *parent) : QObject(parent)
{
    this->function1 = new FunctionParser(functions[1]);
    this->function2 = new FunctionParser(functions[2]);
    //GENERATING INITIAL POPULATION
}
