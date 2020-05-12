#include "librarywindow.h"
#include <QDebug>

LibraryWindow::LibraryWindow(QWidget *parent) : QDialog(parent)
{  
    fillPicList();
    this->f1List = new QListWidget;
    this->f2List = new QListWidget;

    QObject::connect(f1List, &QListWidget::currentRowChanged,
                     this, &LibraryWindow::on_ItemF1Selected);
    QObject::connect(f2List, &QListWidget::currentRowChanged,
                     this, &LibraryWindow::on_ItemF2Selected);

    addFunctions(f1List);
    addFunctions(f2List);

    QLabel *f1Label = new QLabel("Function 1:");
    QLabel *f2Label = new QLabel("Function 2:");

    QPushButton *okButton = new QPushButton("OK");
    okButton->setMinimumSize(100,40);
    okButton->setMaximumSize(100,40);

    pix1 = new QLabel;
    pix1->setMinimumSize(200,200);
    pix2 = new QLabel;
    pix2->setMinimumSize(200,200);

    QPixmap pix;
    if(pix.load(":/res/resources/images/empty.png")){
        pix = pix.scaled(pix1->sizeHint(), Qt::KeepAspectRatio);
        pix1->setPixmap(pix);
        pix2->setPixmap(pix);
    }else qDebug()<<"nope";

    QObject::connect(okButton, &QPushButton::clicked,
                     this, &LibraryWindow::sendFunctionToMain);

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(f1Label,0,0);
    mainLayout->addWidget(f2Label,1,0);
    mainLayout->addWidget(f1List,0,1);
    mainLayout->addWidget(f2List,1,1);
    mainLayout->addWidget(pix1,0,2);
    mainLayout->addWidget(pix2,1,2);
    mainLayout->addWidget(okButton,2,1,1,1,Qt::AlignHCenter);

    f1List->setCurrentRow(0);
    f2List->setCurrentRow(0);

    this->setMinimumWidth(800);
    this->setLayout(mainLayout);
}

void LibraryWindow::addFunctions(QListWidget *temp_list)
{
    temp_list->addItem("[Funkcja z czterema minimami lokalnymi]\n"
                       "x1^4+x2^4-0.62*x1^2-0.62*x2^2");
    temp_list->item(0)->setBackground(Qt::lightGray);

    temp_list->addItem("[Funkcja Rosenbrocka'a]\n"
                       "100*(x2-x1^2)^2+(1-x1)^2");
    temp_list->addItem("[Funkcja Zangwill'a]\n"
                       "(x1-x2+x3)^2+(-x1+x2+x3)^2+(x1+x2-x3)^2");
    temp_list->item(2)->setBackground(Qt::lightGray);

    temp_list->addItem("[Funkcja Goldensteina-Price'a]\n"
                       "(1+(x1+x2+1)^2*(19-14*x1+3*x1^2-14*x2+6*x1*x2+3*x2^2))*(30+(2*x1-3*x2)^2*(18-32*x1+12*x1^2+48*x2-36*x1*x2+27*x2^2))");

    temp_list->addItem("[Funkcja celu szczególnie przeznaczona do testowaniaalgorytmów genetycznych]\n"
                       "exp(-2*log(2)*(x-0.08)^2/0.854^2)*sin(5*pi*(x^0.75-0.05)^6)");
    temp_list->item(4)->setBackground(Qt::lightGray);

    temp_list->addItem("[Zmodyfikowana funkcja Himmelblau’a]\n"
                       "(x1^2+x2-11)^2+(x1+x2^2-7)^2-200");
    temp_list->addItem("[Funkcja testowa Geem’a]\n"
                       "4*x1^2-2.1*x1^4+(x1^6/3)+x1*x2=4*x2^2+4*x2^4");
    temp_list->item(6)->setBackground(Qt::lightGray);

    temp_list->addItem("[Dwa minima i dwa maksima w II i IV ćwiartce układu współrzędnych]\n"
                       "sin(x1)*sin(x2)*exp(-(x1^2+x2^2))");
    temp_list->addItem("[Jedno minimum i jedno maksimum]\n"
                       "x1*exp(-(x1^2+x2^2))");
    temp_list->item(8)->setBackground(Qt::lightGray);

    temp_list->addItem("[Funkcja celu szczególnie przeznaczona do testowaniaalgorytmów genetycznych]\n"
                       "sin(5.1*pi*x+0.5)^6");
    temp_list->addItem("[F1 dla f. Birtha-Korna]\n"
                       "4*x1^2+4*x2^2");
    temp_list->item(10)->setBackground(Qt::lightGray);

    temp_list->addItem("[F2 dla f. Birtha-Korna]\n"
                       "(x1-5)^2+(x2-5)^2");
}

void LibraryWindow::fillPicList()
{
    this->listPic.append(":/res/resources/images/empty.png");
    this->listPic.append(":/res/resources/images/f1.png");
    this->listPic.append(":/res/resources/images/f2.png");
    this->listPic.append(":/res/resources/images/empty.png");
    this->listPic.append(":/res/resources/images/f4.png");
    this->listPic.append(":/res/resources/images/f5.png");
    this->listPic.append(":/res/resources/images/f6.png");
    this->listPic.append(":/res/resources/images/f7.png");
    this->listPic.append(":/res/resources/images/f8.png");
    this->listPic.append(":/res/resources/images/f9.png");
    this->listPic.append(":/res/resources/images/f10.png");
    this->listPic.append(":/res/resources/images/empty.png");
    this->listPic.append(":/res/resources/images/empty.png");

}

void LibraryWindow::sendFunctionToMain()
{
    if(this->f1List->selectedItems().empty())
    {
        emit ok_clicked("",
                        this->f2List->currentItem()->text().split("\n").at(1));
    }else if(this->f2List->selectedItems().empty())
    {
        emit ok_clicked(this->f1List->currentItem()->text().split("\n").at(1),
                        "");
    }else if(!(this->f1List->selectedItems().empty() and this->f2List->selectedItems().empty()))
    {
        emit ok_clicked(this->f1List->currentItem()->text().split("\n").at(1),
                        this->f2List->currentItem()->text().split("\n").at(1));
    }
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

void LibraryWindow::on_ItemF2Selected(int itemRow)
{
    QPixmap pix;
    QString filename = listPic.at(itemRow+1);

    if(pix.load(filename)){
        pix = pix.scaled(pix1->sizeHint(), Qt::KeepAspectRatio);
        pix2->setPixmap(pix);
    }
}
