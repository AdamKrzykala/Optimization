#include "optimizationmainwindow.h"
#include "ui_optimizationmainwindow.h"

OptimizationMainWindow::OptimizationMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OptimizationMainWindow)
{
    ui->setupUi(this);
    this->parser = new FunctionParser;
}

OptimizationMainWindow::~OptimizationMainWindow()
{
    delete ui;
}
