#include "mainwindow.h"
#include <QApplication>
#include "chartview.h"
#include "stdafx.h"
#include  "DataPoint.h"
#include "KMeansClustering.h"
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(0);
    w.show();
    return a.exec();
}
