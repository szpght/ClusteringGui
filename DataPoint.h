
#pragma once
class DataPoint
{
private:
	double _x, _y;

public:
	DataPoint();
	DataPoint(double x, double y);
	double X();
	double Y();
	void X(double x);
	void Y(double y);
};
