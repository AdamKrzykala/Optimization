#ifndef NSGAALGORITHM_H
#define NSGAALGORITHM_H

#include <QMainWindow>
#include <QObject>
#include <QVector>
#include <QDebug>
#include <QPair>
#include <QMap>
#include <random>
#include "allele.h"
//#include "functionparser.h"

namespace Ui {
class NSGAalgorithm;
}

class NSGAalgorithm : public QMainWindow
{
    Q_OBJECT

public:
    explicit NSGAalgorithm( Borders,
                            QMap<QString,T>,
                            QMap<int,QString>,
                            QWidget *parent = 0);
    virtual ~NSGAalgorithm();

    Population ConcatenatePopulation(Population,Population);

    void NSGA_MainLoop(void);

private:
    Ui::NSGAalgorithm *ui;
    FunctionParser *function1;
    FunctionParser *function2;
    Allele *genetic_functions;
    Population _parentPopulation;
    Population _offspringPopulation;
    Population _concatenatedPopulation;
    Parameters _params;
    Borders _borders;
};

#endif // NSGAALGORITHM_H
