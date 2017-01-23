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
    void updatePlot();

private slots:

    void on_exitAction_triggered();

    void on_fixedRangeChBox_clicked(bool checked);

    void on_clearAction_triggered();

    void on_aboutAction_triggered();

    void on_stepBtn_clicked();

    void on_calculateBtn_clicked();

private:
    Ui::MainWindow *ui;
    void setupChart();
    CustomPlot *plot;
    ViewModel *model;
    void drawPlot(ViewModel *viewModel);
    bool valueFromEdit(QLineEdit *edit, int *value);
    bool valueFromEdit(QLineEdit *edit, double *value);
    void badValueError();
    void initializeGui();

public slots:
    void newPointFromField();
    void setGroupNumberFromField();
    void setRanges();
};

