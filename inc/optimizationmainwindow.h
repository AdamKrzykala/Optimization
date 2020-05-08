#ifndef OPTIMIZATIONMAINWINDOW_H
#define OPTIMIZATIONMAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QPair>
#include <QtMath>
#include <QMap>
#include "authors.h"
#include "nsgaalgorithm.h"
#include "librarywindow.h"

template <class Key, class T> class QMap;

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
    NSGAalgorithm *optimizationTask;

protected:
    inline void closeEvent(QCloseEvent* event) override {
        QMainWindow::closeEvent(event);
    }
    void userConnections();

private slots:
    void on_actionAuthors_triggered();
    void on_DimButton_clicked();
    void on_AlgorithmStartButton_clicked();
    void on_FunctionLibraryButton_clicked();

public slots:
    void on_libraryOkLibraryButton_clicked(QString, QString);
};

#endif // OPTIMIZATIONMAINWINDOW_H
