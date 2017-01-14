#include "mainwindow.h"
#include <QApplication>
#include "chartview.h"
#include "stdafx.h"
#include  "DataPoint.h"
#include "KMeansClustering.h"
using namespace std;


int main(int argc, char *argv[])
{
    vector<DataPoint> data =
    {
        DataPoint(1, 1),
        DataPoint(2, 1),
        DataPoint(4, 3),
        DataPoint(5, 4)
    };
    KMeansClustering program;
    program.Data(data);
    program.K(2);
    program.Init();
    bool s1 = program.NextStep();
    bool s2 = program.NextStep();


    QApplication a(argc, argv);
    //ChartView c;
    MainWindow w(0);


    //w.setCentralWidget(&c);
    w.show();

    return a.exec();
}
