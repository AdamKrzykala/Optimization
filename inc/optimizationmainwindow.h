#ifndef OPTIMIZATIONMAINWINDOW_H
#define OPTIMIZATIONMAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "authors.h"

#include "functionparser.h"

namespace Ui {
class OptimizationMainWindow;
}

class OptimizationMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OptimizationMainWindow(QWidget *parent = 0);
    ~OptimizationMainWindow();

private:
    Ui::OptimizationMainWindow *ui;
    FunctionParser *parser;

protected:
    void closeEvent(QCloseEvent* event) override {
        QMainWindow::closeEvent(event);
    }
    void userConnections();

private slots:
    void on_actionAuthors_triggered();
    void on_DimButton_clicked();
};

#endif // OPTIMIZATIONMAINWINDOW_H
