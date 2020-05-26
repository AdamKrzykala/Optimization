#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QtCharts/qscatterseries.h>
#include <QtCharts/qchartview.h>
#include <QMap>
#include <QTime>
#include <QMessageBox>
#include <allele.hpp>

namespace Ui {
class ResultWindow;
}

class ResultWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ResultWindow(QMap<QString,int>, QWidget *parent = 0);
    ~ResultWindow();

    void setScatterPlot(int);
    void actualizeParams(QMap<QString,int>);

protected:
    inline void closeEvent(QCloseEvent* event) override {
        //What happens when user exit
        delete this;
        QMainWindow::closeEvent(event);
    }

public slots:
    void handleFinishedProcess();
    void setProgressBar(int);
    void setStartTimer();
    void setTimer();
    void setActualPopulation(Allele);

private slots:
    void on_StartButton_clicked();

    void on_decr_clicked();

    void on_incr_clicked();

    void on_iteration_textChanged(const QString &arg1);

private:
    Ui::ResultWindow *ui;
    QChart *chart;
    QChartView *chartView = new QChartView();
    QMap<QString, int> _params;
    int actualStep;
    QVector<QVector<QPointF>> history;
    QTime startTime;
};

#endif // RESULTWINDOW_H
