#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <QtCharts/QScatterSeries>
#include <cmath>
#include <fstream>

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
    ui->groupNumberEdit->setText(QString::number(model->K));
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
        model->setK(k);
        updatePlot();
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

void MainWindow::clearPlot()
{
    model->Clusters.clear();
    model->Data.clear();
    model->GroupPaths.clear();
    updatePlot();
}

void MainWindow::on_aboutAction_triggered()
{
    auto msg = QString(
                "Program dzieli podany zbiór dwuwymiarowych punktów na klastry "
                "za pomocą algorytmu k-means clustering. Możliwe jest śledzenie "
                "krok po kroku jak zmienia się położenie centroidów oraz przydział "
                "punktów do klastrów po każdej iteracji algorytmu, a także "
                "wczytywanie i zapisywanie danych do pliku.\n\n"
                "Copyrigth Paweł Pietrasz 2017\n"
                "Licencja GNU GPL 3");
    QMessageBox::information(this, "O programie", msg);
}

void MainWindow::on_stepBtn_clicked()
{
    static bool lastResult = true;
    auto & program = model->Program;
    bool result = program.NextStep();
    if (result || lastResult)
    {
        model->GroupPaths.push_back(program.Centroids());
        updatePlot();
    }
    if (!result)
    {
        QMessageBox::information(this, "Koniec", "Osiągnięto ostateczny wynik");
    }
    lastResult = result;
}

void MainWindow::on_calculateBtn_clicked()
{
    auto & program = model->Program;
    bool result;
    do
    {
        result = program.NextStep();
        model->GroupPaths.push_back(program.Centroids());
        updatePlot();
    } while (result);
}

void MainWindow::on_newCalculationBtn_clicked()
{
    model->setK(model->K);
    plot->UpdatePlot();
}

void MainWindow::on_openAction_triggered()
{
    auto fileName = QFileDialog::getOpenFileName(this, "Dane do wczytania", "", "Text files (*.txt)");
    std::ifstream file(qPrintable(fileName));
    if (!file.is_open())
    {
        QMessageBox::critical(this, "Błąd", "Nie udało się otworzyć pliku");
        return;
    }

    clearPlot();
    double x, y;
    while (file >> x >> y)
    {
        model->addPoint(x, y);
    }
    updatePlot();
}
