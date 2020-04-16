#include "optimizationmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OptimizationMainWindow startWindow;
    startWindow.showMaximized();

    return a.exec();
}
