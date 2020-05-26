#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QThread>
#include <QCloseEvent>
#include <QTime>
#include <QTimer>
#include <qtconcurrentrun.h>
#include <QFutureWatcher>
#include <QApplication>
#include <qmetatype.h>

#include "librarywindow.h"
#include "resultwindow.h"
#include "NSGA.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    ResultWindow *pareto;

    //FUTURE AND WATCHER
    QFuture<void> Algorithm_Thread;
    QFutureWatcher<void> watcher;
    //----------------------------

    Allele *Pinit;
    Allele A_NonDom;
    Allele A_Dom;

    QMap<QString,int> NSGA_params;

    double Niche_Radius;
    double Sigma;

    NSGA Nsga_Algorithm_Handler;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer *timer = new QTimer(this);

protected:
    inline void closeEvent(QCloseEvent* event) override {
        //What happens when user exit
        QMainWindow::closeEvent(event);
    }

signals:
    void progessBarSignal(int);
    void timerStartSignal();
    void actualPopulationSignal(Allele);

private slots:

    void on_TaskDImensionNumber_valueChanged(int arg1);

    void on_Set_Task_Button_clicked();

    //Settting parameters for algorithm
    void on_Lp_textChanged(const QString &arg1);
    void on_pe_textChanged(const QString &arg1);
    void on_pm_textChanged(const QString &arg1);
    void on_Lg_textChanged(const QString &arg1);
    void on_niche_radius_textChanged(const QString &arg1);

    void on_sigma_textChanged(const QString &arg1);

    void on_FunctionLibrary_clicked();

    void on_nsgaii_true_toggled(bool checked);

    void on_nsga_true_toggled(bool checked);

    void handleFinishedProcess(void);

public slots:

    void on_libraryOkLibraryButton_clicked(QString, QString, int,
                                           QVector<double>,
                                           QVector<double>);
    void NSGA_Algorithm_Run();
};

#endif // MAINWINDOW_H
