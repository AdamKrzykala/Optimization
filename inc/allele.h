#ifndef ALLELE_H
#define ALLELE_H

#include <QObject>
#include <QMap>
#include <QVector>

#include <random>
#include <iostream>
#include <cmath>

#include "functionparser.h"

typedef QVector<QVector<T>> Population;

class Allele : public QObject
{
    Q_OBJECT
public:
    explicit    Allele(QObject *parent = nullptr);

    Population                    initPopulation( QMap<QString,T> params, QVector<QPair<double,double>> borders );
    QVector<QPair<QString, int>>  populationToBin( Population population, double lLimit, double rLimit );
    Population                    binToPopulation( QVector<QPair<QString, int>> temp_population, double lLimit, double rLimit );
signals:

public slots:
};

#endif // ALLELE_H
