#include "nsgaalgorithm.h"
#include "ui_nsgaalgorithm.h"
#include <ctime>
NSGAalgorithm::NSGAalgorithm(Borders borders,
                               QMap< QString, T > params,
                               QMap< int, QString > functions,
                               QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NSGAalgorithm)
{
    ui->setupUi(this);
    this->_params = params;
    this->_borders = borders;
    this->function1 = new FunctionParser(functions[1]);
    this->function2 = new FunctionParser(functions[2]);
    this->genetic_functions = new Allele(params);
    QVector<QPointF> temp = QVector<QPointF>(this->_params["Lp"],QPointF(0,0));
    this->history = QVector<QVector<QPointF>>(this->_params["Lg"],temp);
    //Initial Population Creating
    this->_parentPopulation = this->genetic_functions->initPopulation(this->_borders);
    this->chart = new QChart();
    this->chartView = new QChartView(this->chart);
    this->chartView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    this->chartView->setMinimumHeight(600);
    this->chartView->setVisible(false);
    ui->verticalLayout_2->addWidget(this->chartView,0,0);
}

NSGAalgorithm::~NSGAalgorithm()
{
    delete ui;
}

Population NSGAalgorithm::ConcatenatePopulation( Population p1, Population p2 )
{
    Population outputPopulation;
    for (int i = 0; i < p1.size(); i++){
        outputPopulation.append(p1[i]);
    }
    for (int i = 0; i < p2.size(); i++){
        outputPopulation.append(p2[i]);
    }
    return outputPopulation;
}

inline double my_clock(void) {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (1.0e-6*t.tv_usec + t.tv_sec);
}

void NSGAalgorithm::NSGA_MainLoop(void)
{
    int do_iter = this->_params["Lg"];
    ui->progressBar->setValue(0);
    double start_time, end_time, duration;
    start_time = my_clock();
    while(do_iter)
    {
    //Main Process
        //qDebug() << "Iteration: " << this->_params["Lg"] - do_iter + 1;
        //Creating offspring population
        //qDebug() << "-----Creating offspring population";
        this->_offspringPopulation = this->genetic_functions->offspringPopulation(this->_parentPopulation,
                                                                                  this->_borders);
        //Concatenating parent population and offspring population
        //qDebug() << "-----Concatenating parent and offspring population";
        Population processPopulation = this->ConcatenatePopulation(this->_parentPopulation,this->_offspringPopulation);
        //Creating fronted population
        //qDebug() << "-----Creating fronts";
        Population frontedPopulation = this->genetic_functions->frontedPopulation(processPopulation, *this->function1, *this->function2, this->_borders);
        //Calculate crowding in each front
        //qDebug() << "-----Calcualte crowding distances";
        this->_parentPopulation = this->genetic_functions->calculateCrowding(frontedPopulation, *this->function1, *this->function2);
        int it = this->_params["Lg"] - do_iter;
        for(int i = 0; i < this->_parentPopulation.size(); i++){
            QPointF temp = QPointF(this->function1->getValue(this->_parentPopulation.at(i).first),this->function2->getValue(this->_parentPopulation.at(i).first));
            this->history[it][i] = temp;
        }
        --do_iter;
        ui->progressBar->setValue((int)(this->_params["Lg"]-do_iter)*100/this->_params["Lg"]);
    }
    end_time = my_clock();
    duration = end_time - start_time;
    ui->timeLine->setText(QString::number(duration)+" sek");
    ui->iterationScreen->setText(QString("%1").arg(this->_params["Lg"]));
    setScatterPlot(this->_params["Lg"]-1);
}

void NSGAalgorithm::setScatterPlot(int it)
{
    this->chartView->chart()->removeAllSeries();
    this->chartView->setVisible(true);
    QScatterSeries *series = new QScatterSeries();
    series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series->setMarkerSize(12);
    for (int i = 0; i < this->_parentPopulation.size(); i++){
        *series << this->history.at(it).at(i);
    }
    this->chartView->chart()->addSeries(series);
    this->chartView->chart()->createDefaultAxes();
}

void NSGAalgorithm::on_pushButton_clicked()
{
    NSGA_MainLoop();
}

void NSGAalgorithm::on_decrementation_clicked()
{
    int current = ui->iterationScreen->text().toInt();
    if ((current-1) > 0){
        ui->iterationScreen->setText(QString("%1").arg(current-1));
    }
}

void NSGAalgorithm::on_iterationScreen_textChanged(const QString &arg1)
{

    if (!(ui->iterationScreen->text() == "") &&
         (ui->iterationScreen->text().toInt() >= 1) &&
         (ui->iterationScreen->text().toInt() <= this->history.size())){
        this->setScatterPlot(ui->iterationScreen->text().toInt()-1);
    }
}

void NSGAalgorithm::on_incrementation_clicked()
{
    int current = ui->iterationScreen->text().toInt();
    if ((current) < this->history.size()){
        ui->iterationScreen->setText(QString("%1").arg(current+1));
    }
}
