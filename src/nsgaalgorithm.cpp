#include "nsgaalgorithm.h"

NSGAalgorithm::NSGAalgorithm(QVector<QPair<double,double>> borders,
                             QMap<QString,T> params,
                             QMap<int,QString> functions,
                             QObject *parent) : QObject(parent)
{
    this->params = params;
    this->function1 = new FunctionParser(functions[1]);
    this->function2 = new FunctionParser(functions[2]);

    //GENERATING INITIAL POPULATION
    QVector<T> temp_vect(this->params["n"], 0.0);
    QVector<QVector<T>>temp_population(this->params["Lp"], temp_vect);
    this->population = temp_population;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    for(int j = 0; j < this->params["n"]; j++){
        std::uniform_real_distribution<> dis(borders[j].first,borders[j].second);
            for (int i = 0; i < this->params["Lp"]; i++) {
                this->population[i][j] = dis(gen);
            }
    }
    //-----------------------------
}
