#include "nsgaalgorithm.h"
#include "ui_nsgaalgorithm.h"
#include <ctime>
NSGAalgorithm::NSGAalgorithm(Borders borders,
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
    this->_parentPopulation = this->genetic_functions->initPopulation(this->_borders);
    NSGA_MainLoop();
}

NSGAalgorithm::~NSGAalgorithm()
{
    delete ui;
}

Population NSGAalgorithm::ConcatenatePopulation( Population p1, Population p2 )
{
    Population outputPopulation;
    for (int i = 0; i < p1.size(); i++){
        outputPopulation.append(p1[i]);
    }
    for (int i = 0; i < p2.size(); i++){
        outputPopulation.append(p2[i]);
    }
    return outputPopulation;
}

void NSGAalgorithm::NSGA_MainLoop(void)
{
    int do_iter = this->_params["Lg"];
    std::clock_t start;
       double duration;

       start = std::clock(); // get current time
    while(do_iter)
    {
    //Main Process
        qDebug() << "Iteration: " << this->_params["Lg"] - do_iter + 1;
        //Creating offspring population
        qDebug() << "-----Creating offspring population";
        this->_offspringPopulation = this->genetic_functions->offspringPopulation(this->_parentPopulation,
                                                                                  this->_borders);
        //Concatenating parent population and offspring population
        qDebug() << "-----Concatenating parent and offspring population";
        Population processPopulation = this->ConcatenatePopulation(this->_parentPopulation,this->_offspringPopulation);
        //Creating fronted population
        qDebug() << "-----Creating fronts";
        Population frontedPopulation = this->genetic_functions->frontedPopulation(processPopulation, *this->function1, *this->function2, this->_borders);
        //Calculate crowding in each front
        this->_parentPopulation.clear();
        this->_offspringPopulation.clear();
        qDebug() << "-----Calcualte crowding distances";
        this->_parentPopulation = this->genetic_functions->calculateCrowding(frontedPopulation, *this->function1, *this->function2);
        --do_iter;
    }

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    qDebug() << "Operation took "<< duration << "seconds";
    qDebug() <<"x:"<< _parentPopulation.last();
    qDebug() <<"f1 value: "<<this->function1->getValue(_parentPopulation.first().first);
    qDebug() <<"f2 value: "<<this->function2->getValue(_parentPopulation.first().first);
}
