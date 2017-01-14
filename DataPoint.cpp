#include "stdafx.h"
#include "DataPoint.h"
using namespace std;

DataPoint::DataPoint(double x, double y)
{
	_x = x;
	_y = y;
}


DataPoint::DataPoint()
{
	_x = _y = 0;
}


double DataPoint::X()
{
	return _x;
}


double DataPoint::Y()
{
	return _y;
}


void DataPoint::X(double x)
{
	if (!isfinite(x))
	{
		throw string("value not finite");
	}
	_x = x;
}


void DataPoint::Y(double y)
{
	if (!isfinite(y))
	{
		throw string("value not finite");
	}
	_y = y;
}
