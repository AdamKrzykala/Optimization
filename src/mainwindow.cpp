#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

// -------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    srand( (unsigned int)( time(NULL) ) );

    this->NSGA_params.insert("n", 5);
    this->NSGA_params.insert("Lp", 1000);
    this->NSGA_params.insert("Lg", 10);
    this->NSGA_params.insert("pe", 90);
    this->NSGA_params.insert("pm", 1);

    this->Niche_Radius = 0.1;
    this->Sigma = 1;
    Pinit = new Allele;

    connect(ui->actionQuit, &QAction::triggered, qApp, &QApplication::quit);
    connect(&this->watcher, SIGNAL(finished()), this, SLOT(handleFinishedProcess()));
}

void MainWindow::handleFinishedProcess()
{
   timer->stop();
}

// -------------------------------------------------------------------------

MainWindow::~MainWindow() {

    delete Pinit;
    delete ui;
}

// -------------------------------------------------------------------------

void Do_NSGA_Algorithm(MainWindow *mw) {

    mw->NSGA_Algorithm_Run();
}
// -------------------------------------------------------------------------

void MainWindow::NSGA_Algorithm_Run() {

    int iter = 0;

    this->Nsga_Algorithm_Handler.initPopulation(*Pinit, Niche_Radius);

    while( iter < this->NSGA_params["Lg"] ) {

        this->Nsga_Algorithm_Handler.NSGA_Algorithm();

        //EMITTING DATA FOR CURRENT PLOT, PROGRESS BAR, TIME
        //Emit for progress bar
        emit progessBarSignal(iter);
        emit actualPopulationSignal(this->Nsga_Algorithm_Handler.NSGA_Get_Actual_Population());
        iter++;
    }
}


// -------------------------------------------------------------------------

void MainWindow::on_TaskDImensionNumber_valueChanged(int arg1)
{
    if (arg1 == 1){
        ui->min1->setEnabled(true);
        ui->max1->setEnabled(true);
        ui->min1->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max1->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min2->setEnabled(false);
        ui->max2->setEnabled(false);
        ui->min2->setStyleSheet("color: rgb(85, 87, 83)");
        ui->max2->setStyleSheet("color: rgb(85, 87, 83)");
        ui->min3->setEnabled(false);
        ui->max3->setEnabled(false);
        ui->min3->setStyleSheet("color: rgb(85, 87, 83)");
        ui->max3->setStyleSheet("color: rgb(85, 87, 83)");
        ui->min4->setEnabled(false);
        ui->max4->setEnabled(false);
        ui->min4->setStyleSheet("color: rgb(85, 87, 83)");
        ui->max4->setStyleSheet("color: rgb(85, 87, 83)");
        ui->min5->setEnabled(false);
        ui->max5->setEnabled(false);
        ui->min5->setStyleSheet("color: rgb(85, 87, 83)");
        ui->max5->setStyleSheet("color: rgb(85, 87, 83)");
    }
    if (arg1 == 2){
        ui->min1->setEnabled(true);
        ui->max1->setEnabled(true);
        ui->min1->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max1->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min2->setEnabled(true);
        ui->max2->setEnabled(true);
        ui->min2->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max2->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min3->setEnabled(false);
        ui->max3->setEnabled(false);
        ui->min3->setStyleSheet("color: rgb(85, 87, 83)");
        ui->max3->setStyleSheet("color: rgb(85, 87, 83)");
        ui->min4->setEnabled(false);
        ui->max4->setEnabled(false);
        ui->min4->setStyleSheet("color: rgb(85, 87, 83)");
        ui->max4->setStyleSheet("color: rgb(85, 87, 83)");
        ui->min5->setEnabled(false);
        ui->max5->setEnabled(false);
        ui->min5->setStyleSheet("color: rgb(85, 87, 83)");
        ui->max5->setStyleSheet("color: rgb(85, 87, 83)");
    }
    if (arg1 == 3){
        ui->min1->setEnabled(true);
        ui->max1->setEnabled(true);
        ui->min1->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max1->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min2->setEnabled(true);
        ui->max2->setEnabled(true);
        ui->min2->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max2->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min3->setEnabled(true);
        ui->max3->setEnabled(true);
        ui->min3->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max3->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min4->setEnabled(false);
        ui->max4->setEnabled(false);
        ui->min4->setStyleSheet("color: rgb(85, 87, 83)");
        ui->max4->setStyleSheet("color: rgb(85, 87, 83)");
        ui->min5->setEnabled(false);
        ui->max5->setEnabled(false);
        ui->min5->setStyleSheet("color: rgb(85, 87, 83)");
        ui->max5->setStyleSheet("color: rgb(85, 87, 83)");
    }
    if (arg1 == 4){
        ui->min1->setEnabled(true);
        ui->max1->setEnabled(true);
        ui->min1->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max1->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min2->setEnabled(true);
        ui->max2->setEnabled(true);
        ui->min2->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max2->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min3->setEnabled(true);
        ui->max3->setEnabled(true);
        ui->min3->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max3->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min4->setEnabled(true);
        ui->max4->setEnabled(true);
        ui->min4->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max4->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min5->setEnabled(false);
        ui->max5->setEnabled(false);
        ui->min5->setStyleSheet("color: rgb(85, 87, 83)");
        ui->max5->setStyleSheet("color: rgb(85, 87, 83)");
    }
    if (arg1 == 5){
        ui->min1->setEnabled(true);
        ui->max1->setEnabled(true);
        ui->min1->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max1->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min2->setEnabled(true);
        ui->max2->setEnabled(true);
        ui->min2->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max2->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min3->setEnabled(true);
        ui->max3->setEnabled(true);
        ui->min3->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max3->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min4->setEnabled(true);
        ui->max4->setEnabled(true);
        ui->min4->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max4->setStyleSheet("color: rgb(255, 255, 255)");
        ui->min5->setEnabled(true);
        ui->max5->setEnabled(true);
        ui->min5->setStyleSheet("color: rgb(255, 255, 255)");
        ui->max5->setStyleSheet("color: rgb(255, 255, 255)");
    }
}

void MainWindow::on_Set_Task_Button_clicked()
{
    delete Pinit;
    Pinit = new Allele;

    int n = ui->TaskDImensionNumber->value();
    Pinit->Population_Set_Parameters(n, this->NSGA_params["Lp"], this->NSGA_params["pe"], this->NSGA_params["pm"]);

    Pinit->Population_Set_Goal_Function( ui->function1->text().toStdString() );
    Pinit->Population_Set_Goal_Function( ui->function2->text().toStdString() );

    double init_min = numeric_limits<double>::max();
    double init_max = numeric_limits<double>::min();

    QVector<QDoubleSpinBox*> table_min = {ui->min1, ui->min2, ui->min3, ui->min4, ui->min5};
    QVector<QDoubleSpinBox*> table_max = {ui->max1, ui->max2, ui->max3, ui->max4, ui->max5};

    for(int i = 0; i < n; ++i) {

        double min = table_min.at(i)->value();
        double max = table_max.at(i)->value();

        Pinit->Population_Set_Search_Domain(min, max);
        if( min <= init_min ) {

            init_min = min;
        }

        if( max >= init_max ) {

            init_max = max;
        }
    }

    //Init first Population
    Pinit->initPopulation(init_min, init_max);

    //Init Pareto Window
    this->pareto = new ResultWindow(this->NSGA_params);
    this->pareto->actualizeParams(this->NSGA_params);
    qRegisterMetaType<Allele>("Allele");
    connect(this,SIGNAL(actualPopulationSignal(Allele)), this->pareto, SLOT(setActualPopulation(Allele)));
    connect(&this->watcher, SIGNAL(finished()), this->pareto, SLOT(handleFinishedProcess()));
    connect(this, SIGNAL(progessBarSignal(int)), this->pareto, SLOT(setProgressBar(int)));
    connect(this, SIGNAL(timerStartSignal()), this->pareto, SLOT(setStartTimer()));
    connect(this->timer, SIGNAL(timeout()), this->pareto, SLOT(setTimer()));
    this->pareto->showMaximized();

    //Start of algorithm
    Algorithm_Thread = QtConcurrent::run( Do_NSGA_Algorithm, this );
    this->watcher.setFuture(Algorithm_Thread);
    emit timerStartSignal();
    timer->start();
}

void MainWindow::on_Lp_textChanged(const QString &arg1)
{
    this->NSGA_params["Lp"] = arg1.toInt();
    Pinit->Population_Set_Parameters(this->NSGA_params["n"], this->NSGA_params["Lp"], this->NSGA_params["pe"], this->NSGA_params["pm"]);
}

void MainWindow::on_pe_textChanged(const QString &arg1)
{
    this->NSGA_params["pe"] = (int)arg1.toDouble()*100;
    Pinit->Population_Set_Parameters(this->NSGA_params["n"], this->NSGA_params["Lp"], this->NSGA_params["pe"], this->NSGA_params["pm"]);
}

void MainWindow::on_pm_textChanged(const QString &arg1)
{
    this->NSGA_params["pm"] = (int)arg1.toDouble()*100;
    Pinit->Population_Set_Parameters(this->NSGA_params["n"], this->NSGA_params["Lp"], this->NSGA_params["pe"], this->NSGA_params["pm"]);
}

void MainWindow::on_Lg_textChanged(const QString &arg1)
{
    this->NSGA_params["Lg"] = arg1.toInt();
    Pinit->Population_Set_Parameters(this->NSGA_params["n"], this->NSGA_params["Lp"], this->NSGA_params["pe"], this->NSGA_params["pm"]);
}

void MainWindow::on_niche_radius_textChanged(const QString &arg1)
{
    this->Niche_Radius = arg1.toDouble();
}

void MainWindow::on_sigma_textChanged(const QString &arg1)
{
    this->Sigma = arg1.toDouble();
}


void MainWindow::on_FunctionLibrary_clicked()
{
    LibraryWindow *libWin = new LibraryWindow(this);

    connect(libWin, SIGNAL(ok_clicked(QString, QString, int,
                                      QVector<double>,
                                      QVector<double>)),
            this, SLOT(on_libraryOkLibraryButton_clicked(QString, QString, int,
                                                         QVector<double>,
                                                         QVector<double>)));

    libWin->setAttribute(Qt::WA_DeleteOnClose);
    libWin->setWindowTitle("Function library");
    libWin->exec();
}

void MainWindow::on_libraryOkLibraryButton_clicked(QString f1, QString f2, int taskDim,
                                                   QVector<double> min,
                                                   QVector<double> max)
{
   if(f1.size())  ui->function1->setText(f1);
   if(f2.size())  ui->function2->setText(f2);
   if(taskDim)    ui->TaskDImensionNumber->setValue(taskDim);
   QVector<QDoubleSpinBox*> table_min = {ui->min1, ui->min2, ui->min3, ui->min4, ui->min5};
   QVector<QDoubleSpinBox*> table_max = {ui->max1, ui->max2, ui->max3, ui->max4, ui->max5};
   for (int i = 0; i < taskDim; i++){
       QDoubleSpinBox *temp_min = table_min[i];
       QDoubleSpinBox *temp_max = table_max[i];
       (*temp_min).setValue(min[i]);
       (*temp_max).setValue(max[i]);
   }
}

void MainWindow::on_nsgaii_true_toggled(bool checked)
{
    if(checked) {
        ui->label_24->setVisible(false);
        ui->label_23->setVisible(false);
        ui->sigma->setVisible(false);
        ui->niche_radius->setVisible(false);
    }
}

void MainWindow::on_nsga_true_toggled(bool checked)
{
    if(checked) {
        ui->label_24->setVisible(true);
        ui->label_23->setVisible(true);
        ui->sigma->setVisible(true);
        ui->niche_radius->setVisible(true);
    }
}
