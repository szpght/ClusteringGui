#include "viewmodel.h"

ViewModel::ViewModel()
{
    Program.Data(&Data);
    Program.Clusters(&Clusters);
}

void ViewModel::addPoint(double x, double y)
{
    Data.push_back(DataPoint(x, y));
    Clusters.push_back(0);
}

void ViewModel::setK(int k)
{
    K = k;
    Program.K(k);
}
