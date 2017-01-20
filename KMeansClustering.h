#pragma once
#include "stdafx.h"
#include "DataPoint.h"

using DataVector = std::vector<DataPoint>;
using IntVector = std::vector<int>;

class KMeansClustering
{
private:
    int _k = 1;
	DataVector _data, _centroids;
	IntVector _clusters, _oldClusters;

public:
	// data accesors
	int K() const;
	void K(int k);
	const DataVector & Data() const;
	void Data(DataVector data);
	const DataVector & Centroids() const;
	const IntVector & Clusters() const;

	// business logic
	void Init();
	bool NextStep();

private:
	void determineCentroids();
	DataVector getCleanCentroids() const;
	void assignToClusters();
};
