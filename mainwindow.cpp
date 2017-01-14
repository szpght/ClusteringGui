#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <QtCharts/QScatterSeries>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupPlot();

}

void MainWindow::setupPlot()
{
    plot = new QCustomPlot;
    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");
    plot->rescaleAxes(true);

    ui->gridLayout->addWidget(plot);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    DataVector data;
    data.push_back(DataPoint(2, 1));
    data.push_back(DataPoint(1, 2));
    ViewModel model;
    model.Data = data;
    drawPlot(&model);
}


void MainWindow::drawPlot(ViewModel *viewModel)
{
    plot->clearGraphs();

    // plotting data
    plot->addGraph();
    auto data = plot->graph(0);

    data->setLineStyle(QCPGraph::lsNone);
    data->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPeace, 10));
    data->setPen(QPen(QColor(0x87, 0xf, 0x57)));

    for (DataPoint & point : viewModel->Data)
    {
        data->addData(point.X(), point.Y());
    }


    plot->rescaleAxes();
    auto range = plot->xAxis->range();
    range.lower = floor(range.lower -1);
    range.upper = ceil(range.upper + 1);
    plot->xAxis->setRange(range);

    range = plot->yAxis->range();
    range.lower = floor(range.lower - 1);
    range.upper = ceil(range.upper + 1);
    plot->yAxis->setRange(range);
    plot->replot();
}
