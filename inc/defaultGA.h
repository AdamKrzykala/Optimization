#ifndef DEFAULTGA_H
#define DEFAULTGA_H

#include <QObject>
#include <random>
#include <iostream>

typedef struct post{
    double postA;
    double postB;
} post;

class DefaultGA : public QObject
{
    Q_OBJECT
public:
    explicit    DefaultGA(QObject *parent = nullptr);
    post        crossBreedingR( double parentA, double parentB );


signals:

public slots:
};

#endif // DEFAULTGA_H
