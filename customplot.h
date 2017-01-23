#pragma once
#include "qcustomplot.h"
#include "viewmodel.h"

class CustomPlot : public QCustomPlot
{
public:
    CustomPlot(QWidget* parent);
    ViewModel *model;

    void UpdatePlot();
    QColor _color(int index);
    QCPGraph* _newGraph(int index);
    QCPGraph* _newPathGraph(int index);
    void _fixAxes();
    void _addAxisMargin(QCPAxis *axis);
    void _addPointsToGraph(QCPGraph *graph, DataVector points);
    void mousePressEvent(QMouseEvent *event);
};
