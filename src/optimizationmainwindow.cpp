#include "optimizationmainwindow.h"
#include "ui_optimizationmainwindow.h"

OptimizationMainWindow::OptimizationMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OptimizationMainWindow)
{
    ui->setupUi(this);
    this->statusBar()->showMessage("Nondominated sorting genetic Algorithm II - multiobject nonlinear optimization problem");
    this->userConnections();
    this->parser = new FunctionParser;
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
