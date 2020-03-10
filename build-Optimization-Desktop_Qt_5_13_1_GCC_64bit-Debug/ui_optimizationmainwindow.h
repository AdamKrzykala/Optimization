/********************************************************************************
** Form generated from reading UI file 'optimizationmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIMIZATIONMAINWINDOW_H
#define UI_OPTIMIZATIONMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptimizationMainWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OptimizationMainWindow)
    {
        if (OptimizationMainWindow->objectName().isEmpty())
            OptimizationMainWindow->setObjectName(QString::fromUtf8("OptimizationMainWindow"));
        OptimizationMainWindow->resize(400, 300);
        menuBar = new QMenuBar(OptimizationMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        OptimizationMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OptimizationMainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        OptimizationMainWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(OptimizationMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        OptimizationMainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OptimizationMainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        OptimizationMainWindow->setStatusBar(statusBar);

        retranslateUi(OptimizationMainWindow);

        QMetaObject::connectSlotsByName(OptimizationMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *OptimizationMainWindow)
    {
        OptimizationMainWindow->setWindowTitle(QCoreApplication::translate("OptimizationMainWindow", "OptimizationMainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OptimizationMainWindow: public Ui_OptimizationMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIMIZATIONMAINWINDOW_H
