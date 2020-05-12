#include "allele.h"
#include <ctime>
#include <thread>
#include <mutex>


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
            Individual(temp_genotype, temp_adaptation));

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
            chromosome_b10.append((double)temp_gene);

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

    //old crossing
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

//    for (int i(0); i < allelDimension; ++i)
//    {
//        if(dis(gen) <= cross_prob){
//            newDescendant._descendantOne.first.first.replace(i, 1, firstParentGenotype.first.at(i));
//            newDescendant._descendantTwo.first.first.replace(i, 1, secondParentGenotype.first.at(i));
//        }else{
//            newDescendant._descendantOne.first.first.replace(i, 1, secondParentGenotype.first.at(i));
//            newDescendant._descendantTwo.first.first.replace(i, 1, firstParentGenotype.first.at(i));
//        }
//    }
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

bool checkIfAdjusted(const Individual &i1, const Borders &borders)
{
    Genotype tempGenotype = i1.first;
    for (int i = 0; i < tempGenotype.size(); i++){
        if (tempGenotype[i] < borders[i].first){
            return false;
        }
        if (tempGenotype[i] > borders[i].second){
            return false;
        }
    }
    return true;
}

bool compareCrowding(const Individual &i1, const Individual &i2)
{
    return i1.second["crowding"] > i2.second["crowding"];
}

int secondMinValue(QVector<int> counters)
{
    int minValue = std::numeric_limits<int>::max();
    for (int i = 0; i < counters.size(); i++){
        if (counters[i] < minValue && counters[i] != -1){
            minValue = counters[i];
        }
    }
    return minValue;
}

Population Allele::frontedPopulation(Population t_population, FunctionParser &f1, FunctionParser &f2, Borders borders)
{
    int pop_size = t_population.size();
    //Calculating counters and dominated objects for each element of population
    Population fronted_population;

    //Calculating dependanties
    threadOperations *threadProcess = new threadOperations(t_population,f1,f2);
    std::thread tw1 = threadProcess->parallelFunctionThread();
    std::thread tw2 = threadProcess->parallelFunctionThread();
    std::thread tw3 = threadProcess->parallelFunctionThread();
    std::thread tw4 = threadProcess->parallelFunctionThread();

    tw1.join();
    tw2.join();
    tw3.join();
    tw4.join();

    QVector<QVector<int>> dominated = threadProcess->returnDominated();
    QVector<int> counters = threadProcess->returnCounters();
    delete threadProcess;

    int front = 1;
    int last_front_size = 0;
    int minValue = 0;

    //Calculating fronts and taking exact amount of fronts
    while(1)
    {
        last_front_size = fronted_population.size();
        minValue = secondMinValue(counters);
        for(int i = 0; i < pop_size; ++i)
        {
            if(counters[i] == minValue){
                if (checkIfAdjusted(t_population[i], borders)){
                    fronted_population.append(t_population[i]);
                    fronted_population.last().second["rank"] = front;
                    fronted_population.last().second["crowding"] = 0.0;
                }

                for( auto j : dominated[i]){
                                    --counters[j];
                                }

                counters[i] = -1;
            }
        }
        front++;
        if(fronted_population.size() >= (t_population.size()/2)) break;
    }

    //Assertion due to a mutation to rebuild
    //assert(fronted_population.size() >= (t_population.size()/2) && "Too small population due to a mutation");

    Population last_front(fronted_population.mid(last_front_size));
    if(fronted_population.size() > t_population.size()/2)
    {
        Population temp_pop = calculateCrowding(last_front, f1, f2);
        std::sort(temp_pop.begin(),temp_pop.end(),compareCrowding);
        int j = 0;
        for( int i = last_front_size; i < pop_size/2; ++i)
        {
            fronted_population.replace(i, temp_pop[j]);
            ++j;
        }

        fronted_population.remove( pop_size/2 , fronted_population.size() - (t_population.size()/2) );
    }

    return fronted_population;
    }


Population Allele::calculateCrowding(Population &t_population, FunctionParser &f1, FunctionParser &f2)
{
    Population OutputPopulation;
    //Creating vector of fronts -- the size = number of crowding distance main loops
    QVector<int> fronts;
    auto assignFront = [&](const Individual& singleIndividual) {
        int temp_rank = singleIndividual.second["rank"];
        if (std::find(fronts.begin(), fronts.end(), temp_rank) == fronts.end()) {
            fronts.append(temp_rank);
        }
    };
    std::for_each(t_population.begin(),t_population.end(),assignFront);
    int frontsIter = fronts.size();

    //Main Loop of Crowding Distance for each front
    int mainLoopIter = 0;
    while (mainLoopIter < frontsIter) {
        //Numbe of front -- fronts[mainLoopIter];
        //Getting all of elements in current front fronts[mainLoopIter]
        Population currentFront;
        for (int i = 0; i < t_population.size(); i++){
            if (t_population[i].second["rank"] == fronts[mainLoopIter]){
                currentFront.append(t_population[i]);
            }
        }
        //Now currentFront holds all of Individuals from one front
        //Getting values of function1 for current front
        QVector<FunctionIndicator> functionValues1;
        for(int i = 0; i < currentFront.size(); ++i)
        {
            FunctionIndicator oneFunc;
            oneFunc.index = i;
            oneFunc.function_value = f1.getValue(currentFront[i].first);
            functionValues1.append(oneFunc);
        }

        QVector<FunctionIndicator> functionValues2;
        for(int i = 0; i < currentFront.size(); ++i)
        {
            FunctionIndicator oneFunc;
            oneFunc.index = i;
            oneFunc.function_value = f2.getValue(currentFront[i].first);
            functionValues2.append(oneFunc);
        }

        // sorting non-descending order all calculated values
        std::sort(functionValues1.begin(), functionValues1.end());
        std::sort(functionValues2.begin(), functionValues2.end());

        //Crowding distance for min value f1 to inf set
        currentFront[functionValues1.first().index].second["crowding"] = INFINITY;
        //Crowding distance for min value f2 to inf set
        currentFront[functionValues2.first().index].second["crowding"] = INFINITY;

        double delta1 = functionValues1.last().function_value - functionValues1.first().function_value;
        double delta2 = functionValues2.last().function_value - functionValues2.first().function_value;

        // calculating crowding for first function; indexes witgout margin values
        for(int i = 1; i < currentFront.size()-1; ++i)
        {
            if (!(delta1 == 0)){
                currentFront[functionValues1[i].index].second["crowding"] = currentFront[functionValues1[i].index].second["crowding"]
                        + (functionValues1[i+1].function_value-functionValues1[i-1].function_value)/delta1;
            }
            if (!(delta2 == 0)){
                currentFront[functionValues2[i].index].second["crowding"] = currentFront[functionValues2[i].index].second["crowding"]
                        + (functionValues2[i+1].function_value-functionValues2[i-1].function_value)/delta2;
            }
        }


        //Sorting is not urgent
        //Copying to output population
        for (int i = 0; i < currentFront.size(); i++){
            OutputPopulation.append(currentFront[i]);
        }
        //Clearing currentFront for next Loop
        currentFront.clear();
        ++mainLoopIter;
    }
    return OutputPopulation;
}

