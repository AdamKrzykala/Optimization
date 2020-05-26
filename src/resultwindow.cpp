#include "resultwindow.h"
#include "ui_resultwindow.h"

ResultWindow::ResultWindow(QMap<QString,int> params, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResultWindow)
{
    ui->setupUi(this);
    this->_params = params;
    this->history = QVector<QVector<QPointF>>(this->_params["Lg"],
            QVector<QPointF>(this->_params["Lp"],
                             QPointF(0,0)));

    this->chart = new QChart();
    this->chart->setTitle("Aktualna populacja");
    this->chartView = new QChartView(this->chart);
    this->chartView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    this->chartView->setMinimumHeight(600);
    this->chartView->setVisible(false);
    ui->elapsed->setDisabled(true);
    ui->verticalLayout_2->addWidget(this->chartView,0,0);
    this->setScatterPlot(0);
    ui->incr->setVisible(false);
    ui->decr->setVisible(false);
    ui->StartButton->setEnabled(false);
}

ResultWindow::~ResultWindow()
{
    delete ui;
}

void ResultWindow::actualizeParams(QMap<QString, int> newParams)
{
    this->_params = newParams;
}

void ResultWindow::setScatterPlot(int it)
{
    this->chartView->chart()->removeAllSeries();
    this->chartView->setVisible(true);
    QScatterSeries *series = new QScatterSeries();
    series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series->setMarkerSize(10);
    for (int i = 0; i < this->_params["Lp"]; i++){
        *series << this->history.at(it).at(i);
    }
    this->chartView->chart()->addSeries(series);
    this->chartView->chart()->createDefaultAxes();
}

void ResultWindow::handleFinishedProcess()
{
    QMessageBox msgBox;
    msgBox.setText("PROCESS FINISHED");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Discard);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Ok:
        msgBox.hide();
        ui->incr->setVisible(true);
        ui->decr->setVisible(true);
        ui->elapsed->setStyleSheet("color: rgb(245, 121, 0)");
        ui->iteration->setStyleSheet("color: rgb(245, 121, 0)");
        ui->StartButton->setEnabled(true);
        break;

    case QMessageBox::Discard:
        this->close();
        break;
    }
}

void ResultWindow::setProgressBar(int it)
{
    this->actualStep = it;
    ui->iteration->setText(QString::number( it + 1 ));
    ui->progressBar->setValue((int)((it+1)*100)/this->_params["Lg"]);
}

void ResultWindow::setStartTimer()
{
    this->startTime = QTime::currentTime();
}

void ResultWindow::setTimer()
{

    ui->elapsed->setText(QString::number(this->startTime.secsTo(QTime::currentTime())));
}

void ResultWindow::setActualPopulation(Allele newPopulation)
{
    float y1, y2;
    for (int i = 0; i < newPopulation.Population_Get_Size(); i++){
        y1 = newPopulation.Get_goal_value(i,0);
        y2 = newPopulation.Get_goal_value(i,1);
        history[this->actualStep][i] = QPointF(y1,y2);
    }
    this->setScatterPlot(this->actualStep);
}

void ResultWindow::on_StartButton_clicked()
{
    if (ui->StartButton->text() == "QUIT"){
        this->close();
    }
}

void ResultWindow::on_decr_clicked()
{
    int current = ui->iteration->text().toInt();
    if ((current-1) > 0){
        ui->iteration->setText(QString("%1").arg(current-1));
    }
}

void ResultWindow::on_incr_clicked()
{
    int current = ui->iteration->text().toInt();
    if ((current) < this->history.size()){
        ui->iteration->setText(QString("%1").arg(current+1));
    }
}

void ResultWindow::on_iteration_textChanged(const QString &arg1)
{
    if (!(ui->iteration->text() == "") &&
         (ui->iteration->text().toInt() >= 1) &&
         (ui->iteration->text().toInt() <= this->history.size())){
        this->setScatterPlot(ui->iteration->text().toInt()-1);
    }
}
