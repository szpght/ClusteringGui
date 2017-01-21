#pragma once
#include "KMeansClustering.h"

class ViewModel
{
public:
    int K = 1;
    DataVector Data;
    IntVector Clusters;
    std::vector<DataVector> GroupPaths;
    KMeansClustering program;

    void addPoint(double x, double y);
};
