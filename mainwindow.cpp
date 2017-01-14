#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <QtCharts/QScatterSeries>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    plot = new QCustomPlot;
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
    plot->addGraph();
    auto graph = plot->graph(0);

    for (DataPoint & point : viewModel->Data)
    {
        graph->addData(point.X(), point.Y());
    }
    plot->replot();
}
