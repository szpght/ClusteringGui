#pragma once
#include "chartview.h"
#include <QMainWindow>
#include "customplot.h"
#include "viewmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_exitAction_triggered();

private:
    Ui::MainWindow *ui;
    void setupChart();
    CustomPlot *plot;
    ViewModel *model;
    void drawPlot(ViewModel *viewModel);
    bool valueFromEdit(QLineEdit *edit, int *value);
    bool valueFromEdit(QLineEdit *edit, double *value);
    void badValueError();

public slots:
    void newPointFromField();
    void setGroupNumberFromField();
};

