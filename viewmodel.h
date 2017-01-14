#pragma once
#include <vector>
#include "KMeansClustering.h"

class ViewModel
{
public:
    DataVector Data;
    IntVector Groups;
    std::vector<DataVector> GroupPaths;
};
