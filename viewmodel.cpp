#include "viewmodel.h"

ViewModel::ViewModel()
{
    Program.Data(&Data);
    Program.Clusters(&Clusters);
}

void ViewModel::addPoint(double x, double y)
{
    Data.push_back(DataPoint(x, y));
    Clusters.push_back(rand() % K);
}

void ViewModel::setXRange(double min, double max)
{
	rangeXMin = min;
	rangeXMax = max;
}

void ViewModel::setYRange(double min, double max)
{
	rangeYMin = min;
	rangeYMax = max;
}

void ViewModel::setFixedRange(bool fixedRange)
{
    FixedAxes = fixedRange;
}

void ViewModel::setK(int k)
{
    K = k;
    Program.K(k);
    GroupPaths.clear();
    randomClusters();
}

void ViewModel::randomClusters()
{
    for (auto & cluster : Clusters)
    {
        cluster = rand() % K;
    }
}

bool ViewModel::step()
{
    return false;
}

void ViewModel::cleanAll()
{
}

void ViewModel::cleanGroups()
{
}
