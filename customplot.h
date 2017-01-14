#pragma once
#include "qcustomplot.h"
#include "viewmodel.h"

class CustomPlot : public QCustomPlot
{
public:
    CustomPlot();
    ViewModel *model;

    void UpdatePlot();
};
