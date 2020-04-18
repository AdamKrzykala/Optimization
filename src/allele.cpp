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

Descendant Allele::cross2Parents(IndividualBin firstParent, IndividualBin secondParent)
{
    double cross_prob = this->_params["Pe"];
    GenotypeBin firstParentGenotype = firstParent.first;
    GenotypeBin secondParentGenotype = secondParent.first;
    if (firstParentGenotype.second != secondParentGenotype.second)
        throw QString ("Unexpected dimension");
    int allelDimension = firstParentGenotype.second;


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis( 0, 1 );

    Descendant newDescendant;
    static Adaptation temp_adaptation;
    temp_adaptation.insert("rank",0.0);
    temp_adaptation.insert("crowding",0.0);
    newDescendant._descendantOne = IndividualBin(firstParentGenotype,temp_adaptation);
    newDescendant._descendantTwo = IndividualBin(secondParentGenotype,temp_adaptation);
    for (int i = 0; i < firstParentGenotype.first.size()/allelDimension; i++)
    {
        int start_pos = i*allelDimension+1;
        if(dis(gen) < cross_prob){
            newDescendant._descendantOne.first.first.replace(start_pos,
                                                             allelDimension,
                                                             secondParentGenotype.first.mid(start_pos,allelDimension));
        }
        if(dis(gen) < cross_prob){
            newDescendant._descendantTwo.first.first.replace(start_pos,
                                                             allelDimension,
                                                             firstParentGenotype.first.mid(start_pos,allelDimension));
        }
    }
    return newDescendant;
}

//Tournament Selection Function
IndividualBin   Allele::choose1Parent( PopulationBin parentPopulation)
{
    IndividualBin temp_parent;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis( 0, parentPopulation.size() );
    IndividualBin firstCandidate = parentPopulation[floor(dis(gen))];
    IndividualBin secondCandidate = parentPopulation[floor(dis(gen))];

    if (firstCandidate.second["rank"] > secondCandidate.second["rank"])
        return firstCandidate;
    else if (firstCandidate.second["rank"] < secondCandidate.second["rank"])
        return secondCandidate;
    else {
        if (firstCandidate.second["crowding"] > secondCandidate.second["crowding"])
            return firstCandidate;
        else if (firstCandidate.second["crowding"] < secondCandidate.second["crowding"])
            return secondCandidate;
    }
    return firstCandidate;
}

//Crossing Function
PopulationBin Allele::crossing(PopulationBin parentPopulation)
{
    PopulationBin tempPopulation;
    while(tempPopulation.size() != parentPopulation.size())
    {
        IndividualBin firstParent = this->choose1Parent( parentPopulation );
        IndividualBin secondParent = this->choose1Parent( parentPopulation );
        Descendant descendant = this->cross2Parents( firstParent, secondParent );
        tempPopulation.append(firstParent);
        tempPopulation.append(secondParent);
        tempPopulation.append(descendant._descendantOne);
        tempPopulation.append(descendant._descendantTwo);
    }
    return tempPopulation;
}

PopulationBin Allele::mutation(PopulationBin tempPopulation)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis( 0, 1 );
    for (PopulationBin::iterator it = tempPopulation.begin();
         it != tempPopulation.end(); ++it){
        for (int i = 0; i < it->first.first.size(); i++){
            if (dis(gen) < this->_params["Pm"]){
                if (it->first.first.at(i) == "0")
                    it->first.first.replace(i,1,"1");
                else
                    it->first.first.replace(i,1,"0");
            }
        }
    }
    return tempPopulation;
}

Population Allele::offspringPopulation( Population parentPopulation,
                                        Borders borders)
{
    PopulationBin populationBin = this->populationToBin( parentPopulation,
                                                         borders);
    PopulationBin crossedPopulation = this->crossing( populationBin );
    PopulationBin mutatedPopulation = this->mutation( crossedPopulation );
    Population offspringPopulation = this->binToPopulation( mutatedPopulation,
                                                            borders);
    return offspringPopulation;
}
