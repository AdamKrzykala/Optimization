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
    temp_list->addItem("[Funkcja Binha-Korna]\n"
                       "f1 = 4*x1^4+4*x2^2\n"
                       "f2 = (x1-5)^2+(x2-5)^2");
    temp_list->item(0)->setBackground(Qt::lightGray);

    temp_list->addItem("[Funkcja Changkonga-Haimesa]\n"
                       "f1 = 2+(x1-2)^2+(x2-1)^2\n"
                       "f2 = 9*x1-(x2-1)^2");
    temp_list->addItem("[Funkcja Schaffera]\n"
                       "f1 = x1^2\n"
                       "f2 = (x1-2)^2");
    temp_list->item(2)->setBackground(Qt::lightGray);

    temp_list->addItem("[Funkcja CTP1]\n"
                       "f1 = x1\n"
                       "f2 = (1+x2)*exp(-x/(1+x2))");
    temp_list->addItem("[Problem Constr-Ex]\n"
                       "f1 = x1\n"
                       "f2 = (1+x2)/x1");
    temp_list->item(4)->setBackground(Qt::lightGray);

    temp_list->addItem("[Funkcja testowa nr.4]\n"
                       "f1 = x1^2-x2\n"
                       "f2 = -0.5*x1-x2-1");
}

void LibraryWindow::fillPicList()
{
    this->listPic.append(":/res/resources/images/empty.png");
    this->listPic.append(":/res/resources/images/f1.png");
    this->listPic.append(":/res/resources/images/f2.png");
    this->listPic.append(":/res/resources/images/f3.png");
    this->listPic.append(":/res/resources/images/f4.png");
    this->listPic.append(":/res/resources/images/f5.png");
    this->listPic.append(":/res/resources/images/f6.png");
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

