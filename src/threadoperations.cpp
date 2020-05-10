#include "threadoperations.h"

std::mutex mtx;

inline bool checkIfTheSame(const Individual &i1, const Individual &i2)
{
    for (int i = 0; i < i1.first.size(); i++){
        if (i1.first[i] != i2.first[i]) return false;
    }
    return true;
}

void threadOperations::parallelFunction()
{
    while(1){
        mtx.lock();
        int i = this->iteration;
        if (i >= pop_size) {
            mtx.unlock();
            break;
        }
        this->iteration++;
        mtx.unlock();

        for(int j = i; j < pop_size; ++j){
            if( j != i && (!checkIfTheSame(this->t_population.at(i),this->t_population.at(j)))){
                double f1i = f1->getValue( this->t_population.at(i).first);
                double f1j = f1->getValue( this->t_population.at(j).first);
                double f2i = f2->getValue( this->t_population.at(i).first);
                double f2j = f2->getValue( this->t_population.at(j).first);

                if( ((f1i <= f1j)  and
                     (f2i <= f2j)) and
                    ((f1i <  f1j)  or
                     (f2i <  f2j)) )
                {
                    mtx.lock();
                    this->dominated[i].append(j);
                    this->counters[j]++;
                    mtx.unlock();
                }
                else
                {
                    mtx.lock();
                    this->dominated[j].append(i);
                    this->counters[i]++;
                    mtx.unlock();
                }
            }
        }
    }
}

threadOperations::threadOperations(Population t_population,
                                   FunctionParser &f1,
                                   FunctionParser &f2)
{
    this->pop_size = t_population.size();
    this->dominated = QVector<QVector<int>>(this->pop_size,QVector<int>(0));
    this->counters = QVector<int>(this->pop_size,0);
    this->t_population = t_population;
    this->f1 = &f1;
    this->f2 = &f2;
    this->iteration = 0;
}
