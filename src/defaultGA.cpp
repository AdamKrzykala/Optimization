#include "defaultGA.h"

DefaultGA::DefaultGA(QObject *parent) : QObject(parent)
{

}

post DefaultGA::crossBreedingR(double parentA, double parentB)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);


}
