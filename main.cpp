#include "mainwindow.h"
#include <QApplication>
#include "chartview.h"
#include "stdafx.h"
#include  "DataPoint.h"
#include "KMeansClustering.h"
#include <cstdlib>
#include <ctime>
using namespace std;


int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w(0);
    w.show();
    return a.exec();
}
