#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <QtCharts/QScatterSeries>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plot = ui->plot;
    model = new ViewModel;
    plot->model = model;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exitAction_triggered()
{
    qApp->quit();
}


void MainWindow::on_groupNumberBtn_clicked()
{
    setGroupNumberFromField();
}


void MainWindow::on_groupNumberEdit_returnPressed()
{
    setGroupNumberFromField();
}


void MainWindow::setGroupNumberFromField()
{
    int k;
    if (setValueFromEdit(ui->groupNumberEdit, &k) && k > 0)
    {
        model->K = k;
    }
    else
    {
        badValueError();
    }
}


bool MainWindow::setValueFromEdit(QLineEdit *edit, int *value)
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


bool MainWindow::setValueFromEdit(QLineEdit *edit, double *value)
{
    bool ok;
    int result = edit->text().toDouble(&ok);
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
