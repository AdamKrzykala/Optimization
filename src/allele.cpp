#include "allele.hpp"

Math_Parser Parser;

// --------------------------------------------------------------------

Individual initOneIndividual(int genotypeLength,
                             int fenotypeLength,
                             int functionAmount) {

    Individual newMember;

    newMember.Genotypes_Size = genotypeLength;
    newMember.Fenotypes_Size = fenotypeLength;
    newMember.Goals_Size = functionAmount;

    newMember.Genotypes = new string[ genotypeLength ];
    newMember.Fenotypes = new float[ fenotypeLength ];
    newMember.Goals     = new float[ functionAmount ];

    newMember.Fitness = 0;
    newMember.Drawn_Probability = 0;

    return newMember;
}

// --------------------------------------------------------------------

void Individual_Genotypes_Decoding(Individual *singleIndividual,
                                   vector<float> minValues,
                                   vector<float> maxValues)
{

    string s = "";
    unsigned long long x = 0;
    float d = 0;

    for(int i = 0; i < singleIndividual->Genotypes_Size; ++i) {

        s = singleIndividual->Genotypes[i];

        for (string::const_iterator i = s.begin(); i != s.end(); ++i) {
            x = (x << 1) + (*i - '0');
        }

        memcpy(&d, &x, sizeof(float));

        float min = minValues[i];
        float max = maxValues[i];

        if(d > max) {

            d = max;
            singleIndividual->Fenotypes[i] = d;
            Individual_Fenotypes_Coding(singleIndividual);
            continue;
        }
        else if(d < min) {

            d = min;
            singleIndividual->Fenotypes[i] = d;
            Individual_Fenotypes_Coding(singleIndividual);
            continue;
        }
        else if( isnan(d) ) {

            d = min;
            singleIndividual->Fenotypes[i] = d;
            Individual_Fenotypes_Coding(singleIndividual);
            continue;
        }

        singleIndividual->Fenotypes[i] = d;
    }
}

// --------------------------------------------------------------------

void Individual_Fenotypes_Coding(Individual *singleIndividual) {

    string s = "";
    float d = 0;

    for (int i = 0; i < singleIndividual->Fenotypes_Size; ++i) {

        d = singleIndividual->Fenotypes[i];

        s = bitset<sizeof d * 8>( *(long unsigned int*)(&d) ).to_string();
        singleIndividual->Genotypes[i] = s;
    }
}

// --------------------------------------------------------------------

Descendant *Individual_Crossing(Individual i1,
                                Individual i2,
                                int pe,
                                vector<float> search_domain_min,
                                vector<float> search_domain_max) {

    Descendant *descendant = new Descendant();
    descendant->firstDescendant = initOneIndividual( i1.Genotypes_Size,
                                                     i1.Fenotypes_Size,
                                                     i1.Goals_Size );

    descendant->secondDescendant = initOneIndividual( i1.Genotypes_Size,
                                                      i1.Fenotypes_Size,
                                                      i1.Goals_Size );

    int Rand_Propability_Temp = rand() % 100;

    if(Rand_Propability_Temp <= pe) {

        string Genotype1_Temp;
        string Genotype2_Temp;

        string New_Genotype_Temp1;
        string New_Genotype_Temp2;

        int Rand_Temp = rand() % ( i1.Genotypes_Size * ( 8 * sizeof(float) ) );

        for(int i = 0; i < i1.Genotypes_Size && i < i2.Genotypes_Size; ++i) {

            New_Genotype_Temp1.clear();
            New_Genotype_Temp2.clear();

            Genotype1_Temp = i1.Genotypes[i];
            Genotype2_Temp = i2.Genotypes[i];

            for(int j = 0; j < (int)( 8 * sizeof(float) ); ++j ) {

                if (i < Rand_Temp) {

                    New_Genotype_Temp1 += Genotype1_Temp[j];
                    New_Genotype_Temp2 += Genotype2_Temp[j];
                }
                else {

                    New_Genotype_Temp1 += Genotype2_Temp[j];
                    New_Genotype_Temp2 += Genotype1_Temp[j];
                }
            }

            descendant->firstDescendant.Genotypes[i] = New_Genotype_Temp1;
            descendant->secondDescendant.Genotypes[i] = New_Genotype_Temp2;

            Individual_Genotypes_Decoding(&descendant->firstDescendant,
                                          search_domain_min,
                                          search_domain_max);

            Individual_Genotypes_Decoding(&descendant->secondDescendant,
                                          search_domain_min,
                                          search_domain_max);
        }
    }
    else {

        descendant->firstDescendant = i1;
        descendant->secondDescendant = i2;
    }

    return descendant;
}

// --------------------------------------------------------------------

Individual Individual_Mutation(Individual i1,
                               int m_probability,
                               vector<float> search_domain_min,
                               vector<float> search_domain_max) {

    Individual New_I = initOneIndividual( i1.Genotypes_Size, i1.Genotypes_Size, i1.Goals_Size );

    for(int i = 0; i < i1.Genotypes_Size; ++i) {

        string New_Genotype_Temp;

        for(int j = 0; j < (int)i1.Genotypes[i].length(); ++j) {

            int Rand_Temp = rand() % 100;

            if(Rand_Temp < m_probability) {

                if(i1.Genotypes[i][j] == '0') New_Genotype_Temp += '1';
                else New_Genotype_Temp += '0';
            }
            else {

                New_Genotype_Temp += i1.Genotypes[i][j];
            }
        }

        New_I.Genotypes[i] = New_Genotype_Temp;
        Individual_Genotypes_Decoding(&New_I, search_domain_min, search_domain_max);
    }

    return New_I;
}

// --------------------------------------------------------------------

float Individual_Adaptation(Individual i1, string adaptation_function) {

    float Adaptation;

    Parser.Math_Parser_Add_Expression(adaptation_function);

    for (int i = 0; i < i1.Fenotypes_Size; ++i) {

        Parser.Math_Parser_Add_Variable("x" + to_string(i+1), i1.Fenotypes[i]);
    }

    Parser.Math_Parser_Calculate();

    Adaptation = Parser.Math_Parser_Get_Expression_Value();

    Parser.Math_Parser_Clear_Expression();

    return Adaptation;
}

// --------------------------------------------------------------------

bool operator > (Individual i1, Individual i2) {

    for(int i = 0; i < i1.Goals_Size && i < i2.Goals_Size; ++i) {

        if( i1.Goals[i] < i2.Goals[i] ) {

            return false;
        }
        else if( i1.Goals[i] == i2.Goals[i] ) {

            for(int j = i + 1; j < i1.Goals_Size && j < i2.Goals_Size; ++j) {

                if( i1.Goals[j] <= i2.Goals[j] ) {

                    return false;
                }
            }
        }
    }

    return true;
}

// --------------------------------------------------------------------

Allele::Allele() {

}

// --------------------------------------------------------------------

Allele::~Allele() {

    Individuals.clear();
    border_max.clear();
    border_min.clear();
    Goal_Functions.clear();
}

// --------------------------------------------------------------------

void Allele::initPopulation(float min, float max) {

    min *= 10000;
    max *= 10000;

    for(int i = 0; i < this->_params["Lp"]; ++i) {

        Individual I_Temp = initOneIndividual( Size, Size, Population_Get_Goal_Functions_Number() );

        for (int j = 0; j < Size; j++) {
            float Fenotype_Rand = (rand() % (int)max) + (int)min;
            I_Temp.Fenotypes[j] = Fenotype_Rand / 10000;
        }
        Individual_Fenotypes_Coding(&I_Temp);
        Individuals.append(I_Temp);
    }
}

// --------------------------------------------------------------------

void Allele::Population_Set_Search_Domain(float min, float max) {

    border_min.push_back(min);
    border_max.push_back(max);
}

// --------------------------------------------------------------------

void Allele::Population_Set_Goal_Function(string goal_function) {

    Goal_Functions.push_back(goal_function);
}

// --------------------------------------------------------------------

string Allele::Population_Get_Goal_Function(int index) {

    if( index < (int)Goal_Functions.size() ) {

        return Goal_Functions[index];
    }
    else {

        return 0;
    }
}

// --------------------------------------------------------------------

void Allele::Population_Set_Individual(Individual i1) {

    Individuals.append(i1);
}

// --------------------------------------------------------------------

Individual Allele::Population_Get_Individual(int index) {

    return Individuals[index];
}

// --------------------------------------------------------------------

void Allele::Population_Set_Fitness(float fitness, int index) {

    Individuals[index].Fitness = fitness;
}

// --------------------------------------------------------------------

void Allele::Population_Adaptation_Update() {

    for(int i = 0; i < (int)Individuals.size(); ++i) {

        Individual I_Temp = Individuals[i];

        for(int j = 0; j < (int)Goal_Functions.size(); ++j) {

            string Goal_Function_Temp = Goal_Functions[j];

            float adaptation = Individual_Adaptation(I_Temp, Goal_Function_Temp);
            Individuals[i].Goals[j] = adaptation;
        }
    }
}

// --------------------------------------------------------------------

Allele Allele::Population_Recombination() {

    Allele New_Population;
    New_Population.Population_Set_Parameters(Size, this->_params["Lp"], this->_params["pe"], this->_params["pm"]);
    New_Population.Goal_Functions       = Goal_Functions;
    New_Population.border_min           = border_min;
    New_Population.border_max           = border_max;

    Descendant *descendant = new Descendant();
    Individual Temp_i, Temp_j, Temp_k, Temp_l;

    int PSize = (int)Individuals.size();

    int Temp_Rand_1 = 0;
    int Temp_Rand_2 = 0;

    for(int i = 0; i < PSize / 2; ++i) {

        // Step 1: Crossover
        Temp_Rand_1 = 0;
        Temp_Rand_2 = 0;

        do {

            Temp_Rand_1 = rand() % Individuals.size();
            Temp_Rand_2 = rand() % Individuals.size();

        } while( Temp_Rand_1 == Temp_Rand_2 );

        Temp_i = Individuals[Temp_Rand_1];
        Temp_j = Individuals[Temp_Rand_2];

        if( Temp_Rand_1 > Temp_Rand_2 ) {

            Individuals.erase(Individuals.begin() + Temp_Rand_1);
            Individuals.erase(Individuals.begin() + Temp_Rand_2);
        }
        else {

            Individuals.erase(Individuals.begin() + Temp_Rand_2);
            Individuals.erase(Individuals.begin() + Temp_Rand_1);
        }

        descendant = Individual_Crossing(Temp_i, Temp_j, this->_params["pe"], border_min, border_max);
        Temp_k = descendant->firstDescendant;
        Temp_l = descendant->secondDescendant;

        // Step 2: Mutation
        Temp_k = Individual_Mutation(Temp_k,this->_params["pm"], border_min, border_max);
        Temp_l = Individual_Mutation(Temp_l,this->_params["pm"], border_min, border_max);

        // Step 3: Add childs to new population
        New_Population.Individuals.append(Temp_k);
        New_Population.Individuals.append(Temp_l);
    }

    delete [] descendant;

    return New_Population;
}

// --------------------------------------------------------------------

Allele Allele::Selection(int tournamentGroupSize) {

    Allele temp_population;
    temp_population.Population_Set_Parameters(Size, this->_params["Lp"], this->_params["pe"], this->_params["pm"]);
    temp_population.Goal_Functions      = Goal_Functions;
    temp_population.border_min          = border_min;
    temp_population.border_max          = border_max;

    temp_population.Population_Clear();

    Population newGroup;
    Individual bestFromGroup = initOneIndividual( Size, Size, Population_Get_Goal_Functions_Number() );

    for(int i = 0; i < Population_Get_Size(); ++i) {

        newGroup.clear();

        for(int j = 0; j < tournamentGroupSize; ++j) {

            int i = rand() % Population_Get_Size();

            newGroup.append( Individuals[i] );
        }
        //Setting minimum value for best member
        bestFromGroup.Fitness = numeric_limits<float>::min();

        for(int k = 0; k < (int)newGroup.size(); ++k ) {

            if( newGroup[k].Fitness >= bestFromGroup.Fitness) bestFromGroup = newGroup[k];
        }

        temp_population.Population_Set_Individual( bestFromGroup );
    }

    return temp_population;
}
// --------------------------------------------------------------------

Allele Allele::Population_Delete_Return_NonDom() {

    Allele Non_Dominated;
    Non_Dominated.Population_Set_Parameters( Size, this->_params["Lp"], this->_params["pe"], this->_params["pm"]);
    Non_Dominated.Goal_Functions        = Goal_Functions;
    Non_Dominated.border_min            = border_min;
    Non_Dominated.border_max            = border_max;

    Non_Dominated.Population_Clear();

    Population Dom_Individuals;

    for(int i = 0; i < (int)Individuals.size(); ++i) {

        Individual I_Temp = Individuals[i];

        bool isNonDom = true;

        for(int j = 0; j < (int)Individuals.size(); ++j) {

            Individual J_Temp = Individuals[j];

            if( I_Temp > J_Temp ) {

                isNonDom = false;
                break;
            }
        }

        if( isNonDom ) {

            Non_Dominated.Population_Set_Individual( I_Temp );
        }
        else {

            Dom_Individuals.append( I_Temp );
        }
    }

    Individuals = Dom_Individuals;

    return Non_Dominated;
}
