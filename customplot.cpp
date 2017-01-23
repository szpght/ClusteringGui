#include "customplot.h"
#include "mainwindow.h"
#include <cstdlib>

CustomPlot::CustomPlot(QWidget* parent) : QCustomPlot(parent)
{
    xAxis->setLabel("x");
    yAxis->setLabel("y");
}


QColor CustomPlot::_color(int index)
{
    return QColor(0x87 * index % 256, 0xf * index % 256, 0x57 * index % 256);
}


QCPGraph* CustomPlot::_newGraph(int index)
{
    auto newGraph = addGraph();
    auto color = _color(index);
    newGraph->setLineStyle(QCPGraph::lsNone);
    newGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, color, color, 8));
    newGraph->setPen(QPen(color));
    return newGraph;
}


QCPGraph* CustomPlot::_newPathGraph(int index)
{
    auto newGraph = addGraph();
    auto color = _color(index);
    newGraph->setLineStyle(QCPGraph::lsLine);
    newGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, color, color, 12));
    newGraph->setPen(QPen(color));
    return newGraph;
}


void CustomPlot::_fixAxes()
{
    rescaleAxes();
    _addAxisMargin(xAxis);
    _addAxisMargin(yAxis);
}


void CustomPlot::_addAxisMargin(QCPAxis *axis)
{
    auto range = axis->range();
    range.lower -= 1;
    range.upper += 1;
    axis->setRange(range);
}


void CustomPlot::UpdatePlot()
{
    int graphIndex = 0;
    clearGraphs();

    // create graph for each cluster
    for (; graphIndex < model->K; ++graphIndex)
    {
        _newGraph(graphIndex);
    }

    // add points to graphs
    for (int i = 0; i < model->Data.size(); ++i)
    {
        int cluster = model->Clusters[i];
        auto currentGraph = graph(cluster);
        auto point = model->Data[i];
        currentGraph->addData(point.X(), point.Y());
    }

    // add paths
    auto & groupPaths = model->GroupPaths;

    // case with only one step
    if (groupPaths.size() == 1)
    {
        for (int i = 0; i < model->K; ++i)
        {
            auto newGraph = _newPathGraph(i);
            auto point = groupPaths[0][i];
            graph(graphIndex + i)->addData(point.X(), point.Y());
        }
    }
    // with more than one point a graph is needed for every step
    else
    {
        for (int i = 0; i + 1< groupPaths.size(); ++i)
        {
            for (int j = 0; j < model->K; ++j)
            {
                auto newGraph = _newPathGraph(j);
                newGraph->setLineStyle(QCPGraph::lsLine);
                auto point1 = groupPaths[i][j];
                auto point2 = groupPaths[i + 1][j];
                newGraph->addData(point1.X(), point1.Y());
                newGraph->addData(point2.X(), point2.Y());
            }
        }
    }

    if (model->FixedAxes)
    {
        xAxis->setRange(model->rangeXMin, model->rangeXMax);
        yAxis->setRange(model->rangeYMin, model->rangeYMax);
    }
    else
    {
        _fixAxes();
        auto xRange = xAxis->range();
        auto yRange = yAxis->range();
        model->rangeXMin = xRange.lower;
        model->rangeXMax = xRange.upper;
        model->rangeYMin = yRange.lower;
        model->rangeYMax = yRange.upper;
    }
    setAntialiasedElements(QCP::aeAll);
    replot();
}


void CustomPlot::mousePressEvent(QMouseEvent *ev)
{
    double x = xAxis->pixelToCoord(ev->x());
    double y = yAxis->pixelToCoord(ev->y());
    model->Data.push_back(DataPoint(x, y));
    model->Clusters.push_back(rand() % model->K);
    auto mainWindow = (MainWindow*) this->parent()->parent();
    mainWindow->updatePlot();
}
