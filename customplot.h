#pragma once
#include "qcustomplot.h"
#include "viewmodel.h"

class CustomPlot : public QCustomPlot
{
public:
    CustomPlot();
    ViewModel *model;

    void UpdatePlot();
	QCPGraph* _newGraph(int index, QCPScatterStyle::ScatterShape shape);
	void _fixAxes();
	void _addAxisMargin(QCPAxis *axis);
	void _addPointsToGraph(QCPGraph *graph, DataVector points);
};
