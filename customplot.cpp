#include "customplot.h"
#include "mainwindow.h"

CustomPlot::CustomPlot(QWidget* parent) : QCustomPlot(parent)
{
    xAxis->setLabel("x");
    yAxis->setLabel("y");
}


QCPGraph* CustomPlot::_newGraph(int index, QCPScatterStyle::ScatterShape shape)
{
    auto newGraph = addGraph();
    auto color = QColor(0x87 * index % 256, 0xf * index % 256, 0x57 * index % 256);
    newGraph->setLineStyle(QCPGraph::lsNone);
    newGraph->setScatterStyle(QCPScatterStyle(shape, color, color, 12));
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
        _newGraph(graphIndex, QCPScatterStyle::ssCircle);
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
    // create graph for every path
    for (int i = 0; i < model->K; ++i)
    {
        auto newGraph = _newGraph(graphIndex + i, QCPScatterStyle::ssSquare);
        newGraph->setLineStyle(QCPGraph::lsLine);
        for (int j = 0; j < model->GroupPaths.size(); ++j)
        {
            auto point = model->GroupPaths[j][i];
            graph(graphIndex + i)->addData(point.X(), point.Y());
        }
    }
    /*for (auto path : model->GroupPaths)
    {
        auto newGraph = _newGraph(graphIndex, QCPScatterStyle::ssSquare);
        graphIndex += 1;
        newGraph->setLineStyle(QCPGraph::lsLine);
        _addPointsToGraph(newGraph, path);
    }*/

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
    replot();
}


void CustomPlot::_addPointsToGraph(QCPGraph *graph, DataVector points)
{
    for (auto point : points)
    {
        graph->addData(point.X(), point.Y());
    }
}


void CustomPlot::mousePressEvent(QMouseEvent *ev)
{
    double x = xAxis->pixelToCoord(ev->x());
    double y = yAxis->pixelToCoord(ev->y());
    model->Data.push_back(DataPoint(x, y));
    model->Clusters.push_back(0);
    auto mainWindow = (MainWindow*) this->parent()->parent();
    mainWindow->updatePlot();
}
