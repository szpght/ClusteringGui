#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <QtCharts/QScatterSeries>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plot = new CustomPlot;
    ui->gridLayout->addWidget(plot);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    DataVector data, path;
    data.push_back(DataPoint(2, 1));
    data.push_back(DataPoint(1, 2));
    data.push_back(DataPoint(1, 3));
    path.push_back(DataPoint(1.5, 0));
	path.push_back(DataPoint(4, 4));
    IntVector clusters;
    clusters.push_back(0);
    clusters.push_back(1);
    clusters.push_back(2);
    clusters.push_back(3);
    clusters.push_back(3);
    ViewModel model;
    model.Data = data;
    model.Clusters = clusters;
    model.K = 3;
	model.GroupPaths.push_back(path);
    plot->model = &model;
    plot->UpdatePlot();
}
