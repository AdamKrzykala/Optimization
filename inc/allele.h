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
typedef QVector<QVector<T>> Population;
typedef QVector<QPair<QString, int>> PopulationBin;
typedef QMap<QString,T> Parameters;
typedef QVector< QPair< double, double >> Borders;

typedef struct descendant{
    QString _descendantOne;
    QString _descendantTwo;
} Descendant;

class Allele : public QObject
{
    Q_OBJECT
public:
    explicit    Allele(Parameters _params, QObject *parent = nullptr);

    Population      initPopulation(QVector<QPair<double,double>> borders);
    PopulationBin   populationToBin( Population population,
                                     QVector<QPair<double,double>> borders);
    Population      binToPopulation( QVector<QPair<QString, int>> temp_population,
                                     QVector<QPair<double,double>> borders );
    PopulationBin   crossing(PopulationBin parentPopulation);
    PopulationBin   mutation(PopulationBin offspringPopulation);

    Descendant      cross2Parents( QString firstParent, QString secondParent, T cross_lvl );
    QString         mutateOne( QString chosenOne, double pm);

private:
    Parameters _params;

};

#endif // ALLELE_H
