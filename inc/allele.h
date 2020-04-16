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
typedef QMap<QString,T> Parameters;
typedef QVector< QPair< double, double >> Borders;

class Allele : public QObject
{
    Q_OBJECT
public:
    explicit    Allele(Parameters _params, QObject *parent = nullptr);

    Population                    initPopulation( QMap<QString, T> &params, QVector<QPair<double,double>> borders );
    QVector<QPair<QString, int>>  populationToBin( Population population, QVector<QPair<double,double>> borders);
    Population                    binToPopulation( QVector<QPair<QString, int>> temp_population, QVector<QPair<double,double>> borders );

private:
    Parameters _params;
};

#endif // ALLELE_H