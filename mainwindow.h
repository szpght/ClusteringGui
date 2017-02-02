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

    void on_aboutAction_triggered();

    void on_stepBtn_clicked();

    void on_calculateBtn_clicked();

    void on_newCalculationBtn_clicked();

    void on_openAction_triggered();

    void on_saveAction_triggered();

    void on_savePlotAction_triggered();

private:
    Ui::MainWindow *ui;
    CustomPlot *plot;
    ViewModel *model;
    QIntValidator *groupNumberValidator;
    QDoubleValidator *doubleValidator;
    bool valueFromEdit(QLineEdit *edit, int *value);
    bool valueFromEdit(QLineEdit *edit, double *value);
    void badValueError();
    void initializeGui();
    void initializeGroupsLabel();
    void initializeValidation();
    void updateModel();

public slots:
    void newPointFromField();
    void setGroupNumberFromField();
    void setRanges();
    void clearPlot();
};

