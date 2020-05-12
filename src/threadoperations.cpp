#include "threadoperations.h"

std::mutex mtx1;
std::mutex mtx2;

bool checkIfTheSame(const Individual i1, const Individual i2)
{
    for (int i = 0; i < i1.first.size(); i++){
        if (i1.first[i] != i2.first[i]) return false;
    }
    return true;
}

void threadOperations::parallelFunction1()
{
    //Population populationToComputing = this->t_population;

    Population localPopulation = this->t_population;
    int pop_size = localPopulation.size();
    while(1){
        int i = 0;
        mtx1.lock();
        i = this->iteration;
        if (i >= pop_size) {
            mtx1.unlock();
            break;
        }
        this->iteration++;
        mtx1.unlock();

        double f1i = this->f1->getValue( localPopulation.at(i).first);
        double f2i = this->f2->getValue( localPopulation.at(i).first);

        //Individual basicIndividual = this->t_population.at(i);
        for(int j = i; j < pop_size; ++j){

            if( j != i){
                double f1j = this->f1->getValue( localPopulation.at(j).first);
                double f2j = this->f2->getValue( localPopulation.at(j).first);


                if( ((f1i <= f1j)  and
                     (f2i <= f2j)) and
                    ((f1i <  f1j)  or
                     (f2i <  f2j)) )
                {
                    mtx2.lock();
                    this->dominated[i].append(j);
                    this->counters[j]++;
                    mtx2.unlock();
                }
                else
                {
                    mtx2.lock();
                    this->dominated[j].append(i);
                    this->counters[i]++;
                    mtx2.unlock();
                }

            }

        }
    }
}

void threadOperations::parallelFunction2()
{
    //Population populationToComputing = this->t_population;

    Population localPopulation = this->t_population;
    int pop_size = localPopulation.size();
    while(1){
        int i = 0;
        mtx1.lock();
        i = this->iteration;
        if (i >= pop_size) {
            mtx1.unlock();
            break;
        }
        this->iteration++;
        mtx1.unlock();

        double f1i = this->f3->getValue( localPopulation.at(i).first);
        double f2i = this->f4->getValue( localPopulation.at(i).first);

        //Individual basicIndividual = this->t_population.at(i);
        for(int j = i; j < pop_size; ++j){

            if( j != i){
                double f1j = this->f3->getValue( localPopulation.at(j).first);
                double f2j = this->f4->getValue( localPopulation.at(j).first);

                if( ((f1i <= f1j)  and
                     (f2i <= f2j)) and
                    ((f1i <  f1j)  or
                     (f2i <  f2j)) )
                {
                    mtx2.lock();
                    this->dominated[i].append(j);
                    this->counters[j]++;
                    mtx2.unlock();
                }
                else
                {
                    mtx2.lock();
                    this->dominated[j].append(i);
                    this->counters[i]++;
                    mtx2.unlock();
                }
            }

        }
    }
}

void threadOperations::parallelFunction3()
{
    //Population populationToComputing = this->t_population;

    Population localPopulation = this->t_population;
    int pop_size = localPopulation.size();
    while(1){
        int i = 0;
        mtx1.lock();
        i = this->iteration;
        if (i >= pop_size) {
            mtx1.unlock();
            break;
        }
        this->iteration++;
        mtx1.unlock();

        double f1i = this->f5->getValue( localPopulation.at(i).first);
        double f2i = this->f6->getValue( localPopulation.at(i).first);

        //Individual basicIndividual = this->t_population.at(i);
        for(int j = i; j < pop_size; ++j){

            if( j != i){
                double f1j = this->f5->getValue( localPopulation.at(j).first);
                double f2j = this->f6->getValue( localPopulation.at(j).first);

                if( ((f1i <= f1j)  and
                     (f2i <= f2j)) and
                    ((f1i <  f1j)  or
                     (f2i <  f2j)) )
                {
                    mtx2.lock();
                    this->dominated[i].append(j);
                    this->counters[j]++;
                    mtx2.unlock();
                }
                else
                {
                    mtx2.lock();
                    this->dominated[j].append(i);
                    this->counters[i]++;
                    mtx2.unlock();
                }
            }

        }
    }
}

void threadOperations::parallelFunction4()
{
    //Population populationToComputing = this->t_population;

    Population localPopulation = this->t_population;
    int pop_size = localPopulation.size();
    while(1){
        int i = 0;
        mtx1.lock();
        i = this->iteration;
        if (i >= pop_size) {
            mtx1.unlock();
            break;
        }
        this->iteration++;
        mtx1.unlock();

        double f1i = this->f7->getValue( localPopulation.at(i).first);
        double f2i = this->f8->getValue( localPopulation.at(i).first);

        //Individual basicIndividual = this->t_population.at(i);
        for(int j = i; j < pop_size; ++j){

            if( j != i){
                double f1j = this->f7->getValue( localPopulation.at(j).first);
                double f2j = this->f8->getValue( localPopulation.at(j).first);

                if( ((f1i <= f1j)  and
                     (f2i <= f2j)) and
                    ((f1i <  f1j)  or
                     (f2i <  f2j)) )
                {
                    mtx2.lock();
                    this->dominated[i].append(j);
                    this->counters[j]++;
                    mtx2.unlock();
                }
                else
                {
                    mtx2.lock();
                    this->dominated[j].append(i);
                    this->counters[i]++;
                    mtx2.unlock();
                }
            }

        }
    }
}


threadOperations::threadOperations(Population t_population,
                                   QMap<int, QString> functionsPostures)
{
    this->pop_size = t_population.size();
    this->dominated = QVector<QVector<int>>(this->pop_size,QVector<int>(0));
    this->counters = QVector<int>(this->pop_size,0);
    this->t_population = t_population;
    this->f1 = new FunctionParser(functionsPostures[1]);
    this->f2 = new FunctionParser(functionsPostures[2]);
    this->f3 = new FunctionParser(functionsPostures[1]);
    this->f4 = new FunctionParser(functionsPostures[2]);
    this->f5 = new FunctionParser(functionsPostures[1]);
    this->f6 = new FunctionParser(functionsPostures[2]);
    this->f7 = new FunctionParser(functionsPostures[1]);
    this->f8 = new FunctionParser(functionsPostures[2]);

    this->iteration = 0;
}
