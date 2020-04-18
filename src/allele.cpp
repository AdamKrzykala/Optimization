#include "allele.h"

Allele::Allele(Parameters params, QObject *parent) : QObject(parent)
{
    this->_params = params;
}

Population Allele::initPopulation(Borders borders )
{
    Genotype temp_genotype(this->_params["n"], 0.0);
    static Adaptation temp_adaptation;
    temp_adaptation.insert("rank",0.0);
    temp_adaptation.insert("crowding",0.0);
    Population temp_population(this->_params["Lp"],
            Individual(temp_genotype,temp_adaptation));

    std::random_device rd;      //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());     //Standard mersenne_twister_engine seeded with rd()

    for(int j = 0; j < this->_params["n"]; j++){
        std::uniform_real_distribution<> dis(borders[j].first,borders[j].second);
            for (int i = 0; i < this->_params["Lp"]; i++) {
                temp_population[i].first[j] = dis(gen);
            }
    }
    return temp_population;
}

PopulationBin Allele::populationToBin( Population population,
                                       Borders borders)
{
    int res = 4;        // coding resolution
    int b = -1;

    PopulationBin encoded_population;

    for (auto i : borders)
    {
        int new_b = ceil(log2((i.second - i.first)*(pow(10,res)) + 1 ));
        if( new_b > 64 ) throw QString("Binary size overflow");     // throwing exception if cannot convert in given limit

        if ( b < new_b) b = new_b;      // finding biggest needed quantity of bits
    }

    for( int i = 0; i < population.size(); i++ )
    {
        Adaptation temp_adaptation = population.at(i).second;
        QString chromosome;
        for( int j = 0; j < (population.at(i).first.size()); j++ )
        {
            QString temp_gen;
            qlonglong temp_val;

            temp_val = static_cast<qlonglong>((population.at(i).first.at(j)-borders.at(j).first)*(static_cast<double>(pow(10,res))));
            temp_gen.setNum(temp_val, 2);

            int loop_length = b - temp_gen.size();
            for(int k = 0; k < loop_length; k++ )
            {
                temp_gen.prepend('0');
            }
            chromosome.append(temp_gen);
        }
        GenotypeBin temp_genotype(chromosome,b);
        encoded_population.append(IndividualBin(temp_genotype,temp_adaptation));
    }

    return encoded_population;
}

Population Allele::binToPopulation( PopulationBin populationBin,
                                    Borders borders)
{
    Population decoded_population;

    for( int i = 0 ; i < populationBin.size(); i++ )
    {
        Adaptation temp_adaptation = populationBin.at(i).second;
        QString chromosome_b2 = populationBin.at(i).first.first;
        int bits = populationBin.at(i).first.second;

        bool con_flag;      // flag of conversion from binary to decimal
        Genotype chromosome_b10;

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
    decoded_population.append(Individual(chromosome_b10,temp_adaptation));
    }
    return decoded_population;
}

//Descendant Allele::cross2Parents( QString firstParent, QString secondParent, T cross_lvl )
//{
//    std::random_device rd;
//    std::mt19937 gen(rd());

//    std::uniform_real_distribution<> dis(0, 1);

//    Descendant des;
//    double s;

//    for( int i = 0 ; i < firstParent.length() ; i++ )
//    {
//        s = dis(gen);
//        if( s <= cross_lvl ){
//            des._descendantOne.append(firstParent.at(i));
//            des._descendantTwo.append(secondParent.at(i));
//        }else
//        {
//            des._descendantOne.append(secondParent.at(i));
//            des._descendantTwo.append(firstParent.at(i));
//        }
//    }

//    return des;
//}

//QString Allele::mutateOne(QString chosenOne, double pm)
//{
//    QString mutatedOne = chosenOne;

//    std::random_device rd;
//    std::mt19937 gen(rd());

//    std::uniform_real_distribution<> dis(0, 1);

//    for( int i = 0 ; i < chosenOne.length(); i++ )
//    {
//        if( dis(gen) <= pm )
//        {
//            if( chosenOne.at(i) == '0'){
//                mutatedOne.replace( i, '1' );
//            }else mutatedOne.replace( i, '0');
//        }
//    }

//    return mutatedOne;
//}

//PopulationBin Allele::crossing(PopulationBin parentPopulation)
//{
//    return parentPopulation;
//}

//PopulationBin Allele::mutation(PopulationBin offspringPopulation)
//{
//    return offspringPopulation;
//}
