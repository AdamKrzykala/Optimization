#ifndef OPTIMIZATIONMAINWINDOW_H
#define OPTIMIZATIONMAINWINDOW_H

#include <QMainWindow>
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
};

#endif // OPTIMIZATIONMAINWINDOW_H
