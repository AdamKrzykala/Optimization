#ifndef ALLELE_H
#define ALLELE_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QDebug>

#include <random>
#include <iostream>
#include <cmath>

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
    QString _descendantOne;
    QString _descendantTwo;
} Descendant;

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
//    PopulationBin   crossing(PopulationBin parentPopulation);
//    PopulationBin   mutation(PopulationBin offspringPopulation);

//    Descendant      cross2Parents( QString firstParent, QString secondParent, T cross_lvl );
//    QString         mutateOne( QString chosenOne, double pm);

private:
    Parameters _params;

};

#endif // ALLELE_H
