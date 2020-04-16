#include "optimizationmainwindow.h"
#include "ui_optimizationmainwindow.h"

OptimizationMainWindow::OptimizationMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OptimizationMainWindow)
{
    ui->setupUi(this);
    this->statusBar()->showMessage("Nondominated sorting genetic Algorithm II - multiobject nonlinear optimization problem");
    this->userConnections();
}

void OptimizationMainWindow::userConnections()
{
    connect(ui->actionQuit, &QAction::triggered, qApp, &QApplication::quit);
}

OptimizationMainWindow::~OptimizationMainWindow()
{
    delete ui;
}

void OptimizationMainWindow::on_actionAuthors_triggered()
{
    authors* authorsWindow = new authors();
    authorsWindow->setAttribute(Qt::WA_DeleteOnClose);
    authorsWindow->show();
}

void OptimizationMainWindow::on_DimButton_clicked()
{
    int inputValue = ui->DimInput->value();
    if (inputValue >= 1) {
        ui->n1MaxValue->setText("1000");
        ui->n1MinValue->setText("-1000");
        ui->n1MaxValue->setEnabled(true);
        ui->n1MinValue->setEnabled(true);
    }
    else {
        ui->n1MaxValue->setText("-");
        ui->n1MinValue->setText("-");
        ui->n1MaxValue->setEnabled(false);
        ui->n1MinValue->setEnabled(false);
    }
    if (inputValue >= 2) {
        ui->n2MaxValue->setText("1000");
        ui->n2MinValue->setText("-1000");
        ui->n2MaxValue->setEnabled(true);
        ui->n2MinValue->setEnabled(true);
    }
    else {
        ui->n2MaxValue->setText("-");
        ui->n2MinValue->setText("-");
        ui->n2MaxValue->setEnabled(false);
        ui->n2MinValue->setEnabled(false);
    }
    if (inputValue >= 3) {
        ui->n3MaxValue->setText("1000");
        ui->n3MinValue->setText("-1000");
        ui->n3MaxValue->setEnabled(true);
        ui->n3MinValue->setEnabled(true);
    }
    else {
        ui->n3MaxValue->setText("-");
        ui->n3MinValue->setText("-");
        ui->n3MaxValue->setEnabled(false);
        ui->n3MinValue->setEnabled(false);
    }
    if (inputValue >= 4) {
        ui->n4MaxValue->setText("1000");
        ui->n4MinValue->setText("-1000");
        ui->n4MaxValue->setEnabled(true);
        ui->n4MinValue->setEnabled(true);
    }
    else {
        ui->n4MaxValue->setText("-");
        ui->n4MinValue->setText("-");
        ui->n4MaxValue->setEnabled(false);
        ui->n4MinValue->setEnabled(false);
    }
    if (inputValue >= 5) {
        ui->n5MaxValue->setText("1000");
        ui->n5MinValue->setText("-1000");
        ui->n5MaxValue->setEnabled(true);
        ui->n5MinValue->setEnabled(true);
    }
    else {
        ui->n5MaxValue->setText("-");
        ui->n5MinValue->setText("-");
        ui->n5MaxValue->setEnabled(false);
        ui->n5MinValue->setEnabled(false);
    }
}

void OptimizationMainWindow::on_AlgorithmStartButton_clicked()
{
    QVector<QPair<double,double>> borders;
    QMap<QString, T> params;
    QMap<int,QString> functions;
    params.insert("n",ui->DimInput->value());
    double a, b;
    try
        {
        if(!ui->n1MaxValue->text().isEmpty()) b = ui->n1MaxValue->text().toDouble();
            else if(params["n"] >= 1) throw (QString)("No Max value for first variable");
        if(!ui->n1MinValue->text().isEmpty()) a = ui->n1MinValue->text().toDouble();
            else if(params["n"] >= 1) throw (QString)("No Min value for first variable");
        borders.push_back(QPair<double,double>(a,b));
        if(!ui->n2MaxValue->text().isEmpty()) b = ui->n2MaxValue->text().toDouble();
            else if(params["n"] >= 2) throw (QString)("No Max value for second variable");
        if(!ui->n2MinValue->text().isEmpty()) a = ui->n2MinValue->text().toDouble();
            else if(params["n"] >= 2) throw (QString)("No Min value for second variable");
        borders.push_back(QPair<double,double>(a,b));
        if(!ui->n3MaxValue->text().isEmpty()) b = ui->n3MaxValue->text().toDouble();
            else if(params["n"] >= 3) throw (QString)("No Max value for third variable");
        if(!ui->n3MinValue->text().isEmpty()) a = ui->n3MinValue->text().toDouble();
            else if(params["n"] >= 3) throw (QString)("No Min value for third variable");
        borders.push_back(QPair<double,double>(a,b));
        if(!ui->n4MaxValue->text().isEmpty()) b = ui->n4MaxValue->text().toDouble();
            else if(params["n"] >= 4) throw (QString)("No Max value for fourth variable");
        if(!ui->n4MinValue->text().isEmpty()) a = ui->n4MinValue->text().toDouble();
            else if(params["n"] >= 4) throw (QString)("No Min value for fourth variable");
        borders.push_back(QPair<double,double>(a,b));
        if(!ui->n5MaxValue->text().isEmpty()) b = ui->n5MaxValue->text().toDouble();
            else if(params["n"] >= 5) throw (QString)("No Max value for fifth variable");
        if(!ui->n5MinValue->text().isEmpty()) a = ui->n5MinValue->text().toDouble();
            else if(params["n"] >= 5) throw (QString)("No Min value for fifth variable");
        borders.push_back(QPair<double,double>(a,b));
        if(!ui->LpValue->text().isEmpty()) params.insert("Lp",ui->LpValue->text().toDouble());
            else throw (QString)("No population size Lp");
        if(!ui->LgValue->text().isEmpty()) params.insert("Lg",ui->LgValue->text().toDouble());
            else throw (QString)("No number of generations Lg");
        if(!ui->PmValue->text().isEmpty()) params.insert("Pm",ui->PmValue->text().toDouble());
            else throw (QString)("No mutation probability Pm");
        if(!ui->PeValue->text().isEmpty()) params.insert("Pe",ui->PeValue->text().toDouble());
            else throw (QString)("No crossing probability Pe");
        if(!ui->FirstFunctionString->text().isEmpty()) functions.insert(1,(QString)(ui->FirstFunctionString->text()));
            else throw (QString)("No first function given");
        if(!ui->SecondFunctionString->text().isEmpty()) functions.insert(2,(QString)(ui->SecondFunctionString->text()));
            else throw (QString)("No second function given");
    }
    catch(QString obj)
    {
        QMessageBox::warning(this, "Warning", obj);
        return;
    }
    this->optimizationTask = new NSGAalgorithm(borders,params,functions);
    this->optimizationTask->setAttribute(Qt::WA_DeleteOnClose);
    this->optimizationTask->showMaximized();
    this->optimizationTask->NSGA_MainLoop();
}
