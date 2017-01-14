#pragma once
#include "KMeansClustering.h"

class ViewModel
{
public:
    int K;
    DataVector Data;
    IntVector Clusters;
    std::vector<DataVector> GroupPaths;
};
