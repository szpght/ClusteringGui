#pragma once
#include "stdafx.h"
#include "DataPoint.h"

using DataVector = std::vector<DataPoint>;
using IntVector = std::vector<int>;

class KMeansClustering
{
private:
    int _k = 2;
    DataVector _centroids, *_data = nullptr;
    IntVector _oldClusters, *_clusters = nullptr;

public:
    // data accesors
    int K() const;
    void K(int k);
    const DataVector & Data() const;
    void Data(DataVector *data);
    void Clusters(IntVector *clusters);
    const DataVector & Centroids() const;
    const IntVector & Clusters() const;

    // business logic
    bool NextStep();

private:
    void determineCentroids();
    DataVector getCleanCentroids() const;
    void assignToClusters();
};
