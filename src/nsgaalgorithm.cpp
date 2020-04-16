#include "nsgaalgorithm.h"
#include "ui_nsgaalgorithm.h"

NSGAalgorithm::NSGAalgorithm(QVector< QPair< double, double >> borders,
                               QMap< QString, T > params,
                               QMap< int, QString > functions,
                               QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NSGAalgorithm)
{
    ui->setupUi(this);
    this->_params = params;
    this->_borders = borders;
    this->function1 = new FunctionParser(functions[1]);
    this->function2 = new FunctionParser(functions[2]);
    this->genetic_functions = new Allele(params);
    //Initial Population Creating
    this->_current = this->genetic_functions->initPopulation(this->_params,this->_borders);
}

NSGAalgorithm::~NSGAalgorithm()
{
    delete ui;
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
