#include "nsgaalgorithm.h"

NSGAalgorithm::NSGAalgorithm(QVector< QPair< double, double >> borders,
                             QMap< QString, T > params,
                             QMap< int, QString > functions,
                             QObject *parent) : QObject(parent)
{
    this->_params = params;
    this->_borders = borders;
    this->function1 = new FunctionParser(functions[1]);
    this->function2 = new FunctionParser(functions[2]);
    this->genetic_functions = new Allele();
    this->_current = this->genetic_functions->initPopulation(this->_params,this->_borders);
    QVector<QPair<QString, int>>  binPop;
    binPop = this->genetic_functions->populationToBin(this->_current,this->_borders);
    qDebug() <<"Finished";
}
