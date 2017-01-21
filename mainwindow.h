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

private:
    Ui::MainWindow *ui;
    void setupChart();
    CustomPlot *plot;
    ViewModel *model;
    void drawPlot(ViewModel *viewModel);
    bool setValueFromEdit(QLineEdit *edit, int *value);
    bool setValueFromEdit(QLineEdit *edit, double *value);
    void badValueError();
    void setGroupNumberFromField();
};

