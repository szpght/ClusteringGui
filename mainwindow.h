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

    void on_groupNumberBtn_clicked();

    void on_groupNumberEdit_returnPressed();

    void on_addPointBtn_clicked();

    void on_newX_returnPressed();

    void on_newY_returnPressed();

private:
    Ui::MainWindow *ui;
    void setupChart();
    CustomPlot *plot;
    ViewModel *model;
    void drawPlot(ViewModel *viewModel);
    bool valueFromEdit(QLineEdit *edit, int *value);
    bool valueFromEdit(QLineEdit *edit, double *value);
    void badValueError();
    void setGroupNumberFromField();
    void newPointFromField();
};

