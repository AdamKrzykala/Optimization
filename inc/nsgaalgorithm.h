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
    explicit NSGAalgorithm(QVector<QPair<double,double>>,
                            QMap<QString,T>,
                            QMap<int,QString>,
                            QWidget *parent = 0);
    ~NSGAalgorithm();

    void NSGA_MainLoop(void);

private:
    Ui::NSGAalgorithm *ui;
    FunctionParser *function1;
    FunctionParser *function2;
    Allele *genetic_functions;
    Population _current;
    Parameters _params;
    Borders _borders;
};

#endif // NSGAALGORITHM_H
