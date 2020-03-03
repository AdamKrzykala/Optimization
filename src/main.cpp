#include "optimizationmainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OptimizationMainWindow startWindow;
    startWindow.show();

    return a.exec();
}
