#ifndef Allele_hpp
#define Allele_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <QDebug>
#include <cstdlib>
#include <bitset>
#include "Math_Parser.hpp"

using namespace std;

// --------------------------------------------------------------------

typedef struct {

    int Genotypes_Size;
    int Fenotypes_Size;
    int Goals_Size;

    string        *Genotypes;
    float *Fenotypes;
    float *Goals;

    float Fitness;
    float Drawn_Probability;

} Individual;

typedef struct {

    Individual firstDescendant;
    Individual secondDescendant;

} Descendant;

Individual initOneIndividual(int, int, int);

void Individual_Genotypes_Decoding(Individual *i1,
                                   vector<float>,
                                   vector<float> );

void Individual_Fenotypes_Coding(Individual*);

Descendant *Individual_Crossing(Individual,
                                Individual,
                                int,
                                vector<float>,
                                vector<float> );

Individual  Individual_Mutation(Individual,
                                int,
                                vector<float>,
                                vector<float> );

float Individual_Adaptation(Individual,
                                    string);

bool operator > (const Individual,
                 const Individual );

typedef QVector<Individual> Population;
typedef QVector<string>     Functions;

// ------------------------------------

class Allele {

private:

    // Private variables
    QMap<QString,double> _params;
    int Size;

    Population Individuals;
    Population NonDom_Individuals;
    Population Dom_Individuals;

    Functions Goal_Functions;

    vector<float> border_min;
    vector<float> border_max;

protected:

public:

    // Public methods
    Allele();
    ~Allele();
    //Population init
    void Population_Set_Parameters(int size,
                                   int Lp,
                                   int pe,
                                   int pm) {

        this->_params.insert("Lp", Lp);
        this->_params.insert("pe", pe);
        this->_params.insert("pm", pm);
        Size = size;
    }
    //Individual init
    void initPopulation(float min, float max);

    vector<float> get_min() {

        return border_min;
    }

    vector<float> get_max() {

        return border_max;
    }

    //Rekombinacja genetyczna
    Allele Population_Recombination();
    Allele Selection(int);

    Allele Population_Get_Non_Dominated();

    Allele Population_Get_Dominated();

    void Population_Set_Search_Domain(float,
                                      float);

    void Population_Adaptation_Update();

    void Population_Set_Goal_Function(string);

    string Population_Get_Goal_Function(int);

    void Population_Set_Individual(Individual);

    Individual Population_Get_Individual(int);

    void Population_Set_Adaptation(float,
                                   int);

    void Population_Set_Fitness(float,
                                int);

    void Population_Clear() {

        Individuals.clear();
    }

    int Population_Get_Size() {

        return (int)( Individuals.size() );
    }

    int Population_Get_Goal_Functions_Number() {

        return (int)( Goal_Functions.size() );
    }

    float Get_goal_value(int member,
                                 int func_number){
        return Individuals[member].Goals[func_number];
    }

    float Population_Get_Min_Fitness() {

        float min = numeric_limits<float>::max();

        for(int i = 0; i < (int)Individuals.size(); ++i) {

            if( Individuals[i].Fitness <= min ) {

                min = Individuals[i].Fitness;
            }
        }
        return min;
    }

    void Population_Remove_Individual(int index) {

        Individuals.erase(Individuals.begin() + index);
    }

    Allele Population_Delete_Return_NonDom();
};

// --------------------------------------------------------------------

#endif /* Allele_hpp */
