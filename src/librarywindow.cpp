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
                       "f1 = 1-exp(-((x1-1/sqrt(4))^2+(x2-1/sqrt(4))^2+(x3-1/sqrt(4))^2+(x4-1/sqrt(4))^2))\n"
                       "f2 = 1-exp(-((x1+1/sqrt(4))^2+(x2+1/sqrt(4))^2+(x3+1/sqrt(4))^2+(x4+1/sqrt(4))^2))");
    temp_list->item(0)->setBackground(Qt::lightGray);

    temp_list->addItem("[KURSAWE]\n"
                       "f1 = (-10*exp(-0.2*sqrt(x1^2+x2^2)))+(-10*exp(-0.2*sqrt(x2^2+x3^2)))\n"
                       "f2 = (abs(x1)^(0.8)+5*sin(x1^3))+(abs(x2)^(0.8)+5*sin(x2^3))+(abs(x3)^(0.8)+5*sin(x3^3))");

    temp_list->addItem("[SHAFFER]\n"
                       "f1 = x1^2\n"
                       "f2 = (x1-2)^2");
    temp_list->item(2)->setBackground(Qt::lightGray);


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
    emit ok_clicked(this->f1List->currentItem()->text().split("\n").at(1).split(" ").at(2),
                    this->f1List->currentItem()->text().split("\n").at(2).split(" ").at(2) );
    this->close();
}

void LibraryWindow::on_ItemF1Selected(int itemRow)
{
    QPixmap pix;
    QString filename = listPic.at(itemRow+1);

    if(pix.load(filename)){
        pix = pix.scaled(pix1->sizeHint(), Qt::KeepAspectRatio);
        pix1->setPixmap(pix);
    }
}

