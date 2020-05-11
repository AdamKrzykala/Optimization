#ifndef NSGAALGORITHM_H
#define NSGAALGORITHM_H

#include <QMainWindow>
#include <QtCharts/qscatterseries.h>
#include <QtCharts/qchartview.h>
#include <QObject>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QPair>
#include <QMap>
#include <random>
#include "allele.h"
//#include "functionparser.h"

using namespace QtCharts;

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
    void setScatterPlot(int);

private slots:
    void on_pushButton_clicked();

    void on_decrementation_clicked();

    void on_iterationScreen_textChanged(const QString &arg1);

    void on_incrementation_clicked();

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
    QVector<QVector<QPointF>> history;

    QChart *chart;
    QChartView *chartView = new QChartView();
};

#endif // NSGAALGORITHM_H
