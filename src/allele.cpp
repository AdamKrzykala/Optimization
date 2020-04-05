#include "allele.h"

Allele::Allele(QObject *parent) : QObject(parent)
{

}

Population Allele::initPopulation( QMap<QString, T> params, QVector<QPair<double,double>> borders )
{
    QVector<T> temp_vect(params["n"], 0.0);
    QVector<QVector<T>>temp_population(params["Lp"], temp_vect);

    std::random_device rd;                                              //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());                                             //Standard mersenne_twister_engine seeded with rd()

    for(int j = 0; j < params["n"]; j++){
        std::uniform_real_distribution<> dis(borders[j].first,borders[j].second);
            for (int i = 0; i < params["Lp"]; i++) {
                temp_population[i][j] = dis(gen);
            }
    }

    return temp_population;
}

Population Allele::binToPopulation( QVector<QPair<QString, int>> temp_population, double lLimit, double rLimit )
{
    Population decoded_population; //QVector<QVector<T>>

    for( auto i : temp_population )
    {
        bool con_flag;                          // flag of conversion form binary to decimal
        QString chromosome_b2 = i.first;
        QVector<T> chromosome_b10;

        while(1)
        {
            qlonglong gene = chromosome_b2.remove(0,i.second-1).toLongLong(&con_flag, 10);

            T temp_gene = ((rLimit - lLimit)*gene)/(2^(i.second)-1)+lLimit;
            chromosome_b10.append(temp_gene);

            if(!chromosome_b2.size()) break;
        }
    decoded_population.append(chromosome_b10);

    }
    return decoded_population;
}

QVector<QPair<QString, int>> populationToBin( Population population, double lLimit, double rLimit)
{
    // qulonglong = uint_64_t -> max - 18446744073709551615

    int res = 4;                                                // coding resolution
    int b = ceil(log2((rLimit - lLimit)*(10^res) + 1 ));        // number of needed bits

    if( b > 64 ) throw "Binary size overflow";                  // throwing exception if cannot code in given limit

    QVector<QPair<QString, int>> temp_population;

    for( int i = 0; i < population.size(); i++ )
    {
        QString chromosome;
        for( int j = 0; i < population[i].size(); j++ )
        {
            QString temp_gen;
            qlonglong temp_val;

            temp_val = static_cast<qlonglong>(population[i].at(j)*(10^res));
            temp_gen.setNum(temp_val, 2);

            int loop_length = b - temp_gen.size();
            for(int k = 0; k < loop_length; k++ )
            {
                temp_gen.prepend('0');
            }

            chromosome.append(temp_gen);
        }
        temp_population[i].first = chromosome;
        temp_population[i].second = b;
    }

    return temp_population;
}

