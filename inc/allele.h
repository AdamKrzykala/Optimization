#ifndef ALLELE_H
#define ALLELE_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QDebug>

#include <random>
#include <iostream>
#include <cmath>

#include <limits.h>
#include "functionparser.h"

//Population, parameters and borders typedef
    typedef QMap< QString, double > Adaptation;
    typedef QMap< QString, T > Parameters;
    typedef QVector< QPair< double, double >> Borders;

//Structures for decymal Population
    typedef QVector< T > Genotype;
    typedef QPair< Genotype, Adaptation > Individual;
    typedef QVector< Individual > Population;

//Structures for binary Population
    typedef QPair< QString, int > GenotypeBin;
    typedef QPair< GenotypeBin, Adaptation > IndividualBin;
    typedef QVector< IndividualBin > PopulationBin;

typedef struct descendant{
    IndividualBin _descendantOne;
    IndividualBin _descendantTwo;
} Descendant;

typedef struct populationCoefficients{
    QVector<QVector<int>> dominated;
    QVector<int> counters;
} PopulationCoefficients;

struct FunctionIndicator{
    int index;
    double function_value;

    friend bool operator< (const FunctionIndicator &a, const FunctionIndicator &b)
    {
        return a.function_value < b.function_value;
    }
};

class Allele : public QObject
{
    Q_OBJECT
public:
    explicit    Allele(Parameters _params, QObject *parent = nullptr);

    Population      initPopulation( Borders borders);

    PopulationBin   populationToBin( Population population,
                                     Borders borders);
    Population      binToPopulation( PopulationBin populationBin,
                                     Borders borders );
    PopulationBin   crossing(PopulationBin parentPopulation);
    PopulationBin   mutation(PopulationBin offspringPopulation);

    Descendant      cross2Parents( IndividualBin firstParent,
                                   IndividualBin secondParent );
    IndividualBin   choose1Parent( PopulationBin parentPopulation);

    Population      offspringPopulation( Population parentPopulation,
                                         Borders borders);
    Population      frontedPopulation( Population t_population, FunctionParser &f1, FunctionParser &f2 );
    Population      calculateCrowding( Population &t_population, FunctionParser &f1, FunctionParser &f2 );


private:
    Parameters _params;

};

#endif // ALLELE_H
