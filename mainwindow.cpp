#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <QtCharts/QScatterSeries>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initializeGui();
}


void MainWindow::initializeGui()
{
    plot = ui->plot;
    model = new ViewModel;
    plot->model = model;
    updatePlot();
}


void MainWindow::updatePlot()
{
    plot->UpdatePlot();
    ui->fixedRangeChBox->setChecked(model->FixedAxes);
    ui->minXEdit->setText(QString::number(model->rangeXMin));
    ui->maxXEdit->setText(QString::number(model->rangeXMax));
    ui->minYEdit->setText(QString::number(model->rangeYMin));
    ui->maxYEdit->setText(QString::number(model->rangeYMax));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exitAction_triggered()
{
    qApp->quit();
}


void MainWindow::setGroupNumberFromField()
{
    int k;
    if (valueFromEdit(ui->groupNumberEdit, &k) && k > 0)
    {
        model->K = k;
    }
    else
    {
        badValueError();
    }
}


bool MainWindow::valueFromEdit(QLineEdit *edit, int *value)
{
    bool ok;
    int result = edit->text().toInt(&ok);
    if (!ok)
    {
        badValueError();
        return false;
    }
    *value = result;
    return true;
}


bool MainWindow::valueFromEdit(QLineEdit *edit, double *value)
{
    bool ok;
    double result = edit->text().toDouble(&ok);
    if (!ok)
    {
        badValueError();
        return false;
    }
    *value = result;
    return true;
}


void MainWindow::badValueError()
{
    QMessageBox::critical(nullptr, "Błąd", "Niepoprawna wartość");
}


void MainWindow::newPointFromField()
{
    double x, y;
    if (valueFromEdit(ui->newX, &x) && valueFromEdit(ui->newY, &y))
    {
        model->addPoint(x, y);
        updatePlot();
    }
}


void MainWindow::on_fixedRangeChBox_clicked(bool checked)
{
    model->FixedAxes = checked;
    updatePlot();
}


void MainWindow::setRanges()
{
    double minX, minY, maxX, maxY;
    if (
        valueFromEdit(ui->minXEdit, &minX) &&
        valueFromEdit(ui->maxXEdit, &maxX) &&
        valueFromEdit(ui->minYEdit, &minY) &&
        valueFromEdit(ui->maxYEdit, &maxY)
    )
    {
        model->rangeXMin = minX;
        model->rangeXMax = maxX;
        model->rangeYMin = minY;
        model->rangeYMax = maxY;
        model->FixedAxes = true;
        updatePlot();
    }
}
