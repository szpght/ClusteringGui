#include "stdafx.h"
#include "KMeansClustering.h"
using namespace std;

// TODO usunac
KMeansClustering::KMeansClustering()
{
	_data = new DataVector;
	_clusters = new IntVector;
}


int KMeansClustering::K() const
{
	return _k;
}

void KMeansClustering::K(int k)
{
	if (k <= 0)
	{
		throw string("incorrect number of clusters");
	}
	_k = k;
}

const DataVector & KMeansClustering::Data() const
{
	return *_data;
}

void KMeansClustering::Data(DataVector *data)
{
    _data = data;
}

const DataVector& KMeansClustering::Centroids() const
{
	return _centroids;
}

const IntVector& KMeansClustering::Clusters() const
{
	return *_clusters;
}

void KMeansClustering::Clusters(IntVector *clusters)
{
    _clusters = clusters;
}

void KMeansClustering::Init()
{
	//if (_data->size() < _k)
	//	throw string("there cannot be more clusters than points");

	// if centroid not present, use corresponding data point as centroid
	_centroids.clear();
	for (int i = 0; i < _k; ++i)
	{
		_centroids.push_back((*_data)[i]);
	}

	_clusters->resize(_data->size());

	assignToClusters();
}

bool KMeansClustering::NextStep()
{
	_oldClusters = *_clusters;

	// make sure that number of clusters corresponds with number of points
	_clusters->resize(_data->size(), 0);

	
	determineCentroids();
	assignToClusters();

    return _oldClusters != *_clusters;
}

void KMeansClustering::determineCentroids()
{
	_centroids = getCleanCentroids();
	vector<int> sumElements;
	sumElements.resize(_k, 0);

	for (int i = 0; i < _data->size(); ++i)
	{
		int centroidIndex = (*_clusters)[i];
		auto & centroid = _centroids[centroidIndex];
		double newX = centroid.X() + (*_data)[i].X();
		double newY = centroid.Y() + (*_data)[i].Y();
		centroid = DataPoint(newX, newY);
		++sumElements[centroidIndex];
	}

	for (int i = 0; i < _k; ++i)
	{
		auto & centroid = _centroids[i];
		int z = sumElements[i];
        if (z)
        {
            centroid.X(centroid.X() / z);
            centroid.Y(centroid.Y() / z);
        }

	}
}

DataVector KMeansClustering::getCleanCentroids() const
{
	vector<DataPoint> v;
	v.resize(_k, DataPoint(0, 0));
	return v;
}

void KMeansClustering::assignToClusters()
{
	// for every point, assign it
	for (int i = 0; i < (*_data).size(); ++i)
	{
		// for every centroid calculate distance
		vector<double> distances(_k);
		for (int j = 0; j < _k; ++j)
		{
			double dx = (*_data)[i].X() - _centroids[j].X();
			double dy = (*_data)[i].Y() - _centroids[j].Y();
			distances[j] = dx*dx + dy*dy;
		}
		auto minDistance = min_element(distances.begin(), distances.end());
		(*_clusters)[i] = distance(distances.begin(), minDistance);
	}
}
