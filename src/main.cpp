#include "optimizationmainwindow.h"
#include "nsgaalgorithm.h"
#include "functionparser.h"
#include "allele.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    OptimizationMainWindow startWindow;
//    startWindow.showMaximized();

//    return a.exec();

    FunctionParser f1(QString("x1^2+x2^3+x3+x4+x5"));
    FunctionParser f2(QString("x1^4+x2+x3+x4+x5"));

    Parameters param;
    param["n"]=5;
    param["Lp"]=10;
    Allele all(param);

        Borders bord;
    for( int i(0); i<5; ++i)
    {
        bord.push_back(QPair<double, double>(-1000,1000));
    }

    Population fuckme;
    fuckme = all.initPopulation(bord);
    qDebug()<<fuckme.size();
    fuckme = all.frontedPopulation(fuckme, f1, f2);
    qDebug()<<fuckme.size();

    return 0;
}
