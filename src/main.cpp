#include "optimizationmainwindow.h"
#include "allele.h"
#include <QApplication>
#include <QDebug>
#include <QMap>
#include <QPair>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OptimizationMainWindow startWindow;
    startWindow.showMaximized();

    Allele al;
    Population pop;
    Population new_pop;
    QVector<QPair<QString, int>> binPop;


    QMap<QString, T> params;
    QVector<QPair<double,double>> borders;
    for (int i = 0; i< 5 ; i++)
    {
        QPair<double, double> in(-100000,100000);
        borders.append(in);
    }

    params.insert("Lp", 2);
    params.insert("n", 5);
    pop = al.initPopulation(params, borders);

    qDebug() << pop;

    try {
        binPop = al.populationToBin(pop, borders);
    } catch (QString w) {
        qDebug()<<w;
    }
    try {
        new_pop = al.binToPopulation(binPop, borders);

    } catch (QString w) {
        qDebug()<<w;
    }

    qDebug() << new_pop;
    return a.exec();
}
