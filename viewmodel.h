#pragma once
#include "KMeansClustering.h"
#include "settings.h"

class ViewModel
{
public:
    int K = 1;
    DataVector Data;
    IntVector Clusters;
    std::vector<DataVector> GroupPaths;
    KMeansClustering Program;
    bool FixedAxes = Settings::FixedAxes;
    double rangeXMin = Settings::RangeXMin;
    double rangeXMax = Settings::RangeXMax;
    double rangeYMin = Settings::RangeYMin;
    double rangeYMax = Settings::RangeYMax;

    ViewModel();
    void addPoint(double x, double y);
};
