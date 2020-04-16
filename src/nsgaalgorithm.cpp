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
    this->genetic_functions = new Allele(params);
    //Initial Population Creating
    this->_current = this->genetic_functions->initPopulation(this->_params,this->_borders);
    //Start optimization task
    this->NSGA_MainLoop();
 }

void NSGAalgorithm::NSGA_MainLoop(void)
{
    int do_iter = this->_params["Lg"];
    while(do_iter)
    {
        //Main Process
        --do_iter;
    }
}
