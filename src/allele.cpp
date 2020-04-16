#include "allele.h"

Allele::Allele(Parameters params, QObject *parent) : QObject(parent)
{
    this->_params = params;
}

Population Allele::initPopulation( QMap<QString, T> &params, QVector<QPair<double,double>> borders )
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

Population Allele::binToPopulation( QVector<QPair<QString, int>> temp_population, QVector<QPair<double,double>> borders)
{
    Population decoded_population;

    for( int i = 0 ; i < temp_population.size(); i++ )
    {
        QString chromosome_b2 = temp_population.at(i).first;
        int bits = temp_population.at(i).second;

        bool con_flag;                                      // flag of conversion from binary to decimal
        QVector<T> chromosome_b10;

        int j = 0;

        while(1)
        {
            QString gene_b2 = chromosome_b2.mid(0, bits);
            chromosome_b2.remove(0, bits);
            qlonglong gene = gene_b2.toLongLong(&con_flag, 2);

            if(!con_flag) throw QString("Conversion from binary to longlong was not succesful");

            T temp_gene = (gene/pow(10,4))+borders.at(j).first;
            chromosome_b10.append(temp_gene);

            if(!chromosome_b2.size()) break;
            ++j;
        }
    decoded_population.append(chromosome_b10);
    }
    return decoded_population;
}

QVector<QPair<QString, int>> Allele::populationToBin( Population population, QVector<QPair<double,double>> borders)
{
    int res = 4;                                     // coding resolution
    int b = -1;
    QVector<QPair<QString, int>> temp_population;

    for (auto i : borders)
    {
        int new_b = ceil(log2((i.second - i.first)*(pow(10,res)) + 1 ));
        if( new_b > 64 ) throw QString("Binary size overflow");         // throwing exception if cannot convert in given limit

        if ( b < new_b) b = new_b;                                      // finding biggest needed quantity of bits
    }

    for( int i = 0; i < population.size(); i++ )
    {
        QString chromosome;
        for( int j = 0; j < (population.at(i).size()); j++ )
        {
            QString temp_gen;
            qlonglong temp_val;

            temp_val = static_cast<qlonglong>((population.at(i).at(j)-borders.at(j).first)*(static_cast<double>(pow(10,res))));
            temp_gen.setNum(temp_val, 2);

            int loop_length = b - temp_gen.size();
            for(int k = 0; k < loop_length; k++ )
            {
                temp_gen.prepend('0');
            }
            chromosome.append(temp_gen);
        }
        temp_population.append(QPair<QString,int>(chromosome,b));
    }

    return temp_population;
}

