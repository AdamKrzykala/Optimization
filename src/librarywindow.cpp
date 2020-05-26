#include "librarywindow.h"
#include <QDebug>

LibraryWindow::LibraryWindow(QWidget *parent) : QDialog(parent)
{
    fillPicList();
    this->f1List = new QListWidget;

    QObject::connect(f1List, &QListWidget::currentRowChanged,
                     this, &LibraryWindow::on_ItemF1Selected);

    addFunctions(f1List);

    QLabel *f1Label = new QLabel("Function:");

    QPushButton *okButton = new QPushButton("OK");
    okButton->setMinimumSize(100,40);
    okButton->setMaximumSize(100,40);

    pix1 = new QLabel;
    pix1->setMinimumSize(200,200);

    QPixmap pix;
    if(pix.load(":/res/resources/images/empty.png")){
        pix = pix.scaled(pix1->sizeHint(), Qt::KeepAspectRatio);
        pix1->setPixmap(pix);
    }else qDebug()<<"nope";

    QObject::connect(okButton, &QPushButton::clicked,
                     this, &LibraryWindow::sendFunctionToMain);

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(f1Label,0,0);
    mainLayout->addWidget(f1List,0,1);
    mainLayout->addWidget(pix1,0,2);
    mainLayout->addWidget(okButton,2,1,1,1,Qt::AlignHCenter);

    f1List->setCurrentRow(0);

    this->setMinimumWidth(800);
    this->setLayout(mainLayout);
}

void LibraryWindow::addFunctions(QListWidget *temp_list)
{
    temp_list->addItem("[FONSECA-FLEMING]\n"
                       "f1 = 1-exp(-(x1-(1/sqrt(4)))^2-(x2-(1/sqrt(4)))^2-(x3-(1/sqrt(4)))^2-(x4-(1/sqrt(4)))^2)\n"
                       "f2 = 1-exp(-(x1+(1/sqrt(4)))^2-(x2+(1/sqrt(4)))^2-(x3+(1/sqrt(4)))^2-(x4+(1/sqrt(4)))^2)");
    temp_list->item(0)->setBackground(Qt::lightGray);

    temp_list->addItem("[KURSAWE]\n"
                       "f1 = (-10*exp(-0.2*sqrt(x1^2+x2^2)))+(-10*exp(-0.2*sqrt(x2^2+x3^2)))\n"
                       "f2 = (abs(x1)^(0.8)+5*sin(x1^3))+(abs(x2)^(0.8)+5*sin(x2^3))+(abs(x3)^(0.8)+5*sin(x3^3))");

    temp_list->addItem("[SHAFFER]\n"
                       "f1 = x1^2\n"
                       "f2 = (x1-2)^2");

    temp_list->item(2)->setBackground(Qt::lightGray);

    temp_list->addItem("[POLONI]\n"
                       "f1 = 1+(0.5*sin(1)-2*cos(1)+sin(2)-1.5*cos(2)-0.5*sin(x1)+2*cos(x1)-sin(x2)+1.5*cos(x2))^2+(1.5*sin(1)-cos(1)+2*sin(2)-0.5*cos(2)-1.5*sin(x1)+cos(x1)-2*sin(x2)+0.5*cos(x2))^2\n"
                       "f2 = (x1+3)^2+(x2+1)^2");

    temp_list->addItem("[ZITZLER1]\n"
                       "f1 = x1\n"
                       "f2 = (1+9/29*x2+9/29*x3+9/29*x4+9/29*x5)*(1-(x1/(1+9/29*x2+9/29*x3+9/29*x4+9/29*x5))^(1/2))");

    temp_list->item(4)->setBackground(Qt::lightGray);

    temp_list->addItem("[ZITZLER2]\n"
                       "f1 = x1\n"
                       "f2 = (1+9/29*x2+9/29*x3+9/29*x4+9/29*x5)*(1-(x1/(1+9/29*x2+9/29*x3+9/29*x4+9/29*x5))^2)");

    temp_list->addItem("[ZITZLER3]\n"
                       "f1 = x1\n"
                       "f2 = (1+9/29*x2+9/29*x3+9/29*x4+9/29*x5)*(1-(x1/(1+9/29*x2+9/29*x3+9/29*x4+9/29*x5))^(1/2)*sin(10*3.1415*x1))");
}

void LibraryWindow::fillPicList()
{
    this->listPic.append(":/res/resources/images/empty.png");
    this->listPic.append(":/res/resources/images/f1.jpg");
    this->listPic.append(":/res/resources/images/f2.jpg");
    this->listPic.append(":/res/resources/images/f3.png");
    //this->listPic.append(":/res/resources/images/f5.png");
}

void LibraryWindow::sendFunctionToMain()
{
    QString currentFunction = this->f1List->currentItem()->text().split("\n").at(0);
    if (currentFunction == "[FONSECA-FLEMING]") {
        QVector<double> min = {-4,-4,-4,-4};
        QVector<double> max = { 4, 4, 4, 4};
        int taskDim = 4;
        emit ok_clicked(this->f1List->currentItem()->text().split("\n").at(1).split(" ").at(2),
                        this->f1List->currentItem()->text().split("\n").at(2).split(" ").at(2),
                        taskDim,min,max);
        this->close();
    }
    if (currentFunction == "[ZITZLER1]") {
        QVector<double> min = {0,0,0,0,0};
        QVector<double> max = {1,1,1,1,1};
        int taskDim = 5;
        emit ok_clicked(this->f1List->currentItem()->text().split("\n").at(1).split(" ").at(2),
                        this->f1List->currentItem()->text().split("\n").at(2).split(" ").at(2),
                        taskDim,min,max);
        this->close();
    }

    if (currentFunction == "[ZITZLER2]") {
        QVector<double> min = {0,0,0,0,0};
        QVector<double> max = {1,1,1,1,1};
        int taskDim = 5;
        emit ok_clicked(this->f1List->currentItem()->text().split("\n").at(1).split(" ").at(2),
                        this->f1List->currentItem()->text().split("\n").at(2).split(" ").at(2),
                        taskDim,min,max);
        this->close();
    }

    if (currentFunction == "[ZITZLER3]") {
        QVector<double> min = {0,0,0,0,0};
        QVector<double> max = {1,1,1,1,1};
        int taskDim = 5;
        emit ok_clicked(this->f1List->currentItem()->text().split("\n").at(1).split(" ").at(2),
                        this->f1List->currentItem()->text().split("\n").at(2).split(" ").at(2),
                        taskDim,min,max);
        this->close();
    }

    if (currentFunction == "[KURSAWE]") {
        QVector<double> min = {-5,-5,-5};
        QVector<double> max = { 5, 5, 5};
        int taskDim = 3;
        emit ok_clicked(this->f1List->currentItem()->text().split("\n").at(1).split(" ").at(2),
                        this->f1List->currentItem()->text().split("\n").at(2).split(" ").at(2),
                        taskDim,min,max);
        this->close();
    }
    if (currentFunction == "[POLONI]") {
        QVector<double> min = {-3.1415,-3.1415};
        QVector<double> max = { 3.1415, 3.1415};
        int taskDim = 2;
        emit ok_clicked(this->f1List->currentItem()->text().split("\n").at(1).split(" ").at(2),
                        this->f1List->currentItem()->text().split("\n").at(2).split(" ").at(2),
                        taskDim,min,max);
        this->close();
    }
    if (currentFunction == "[SHAFFER]") {
        QVector<double> min = {-10};
        QVector<double> max = { 10};
        int taskDim = 1;
        emit ok_clicked(this->f1List->currentItem()->text().split("\n").at(1).split(" ").at(2),
                        this->f1List->currentItem()->text().split("\n").at(2).split(" ").at(2),
                        taskDim,min,max);
        this->close();
    }
}

void LibraryWindow::on_ItemF1Selected(int itemRow)
{
//    QPixmap pix;
//    QString filename = listPic.at(itemRow+1);

//    if(pix.load(filename)){
//        pix = pix.scaled(pix1->sizeHint(), Qt::KeepAspectRatio);
//        pix1->setPixmap(pix);
//    }
}

