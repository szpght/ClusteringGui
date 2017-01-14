#include "customplot.h"

CustomPlot::CustomPlot()
{
    xAxis->setLabel("x");
    yAxis->setLabel("y");
}


void CustomPlot::UpdatePlot()
{
    clearGraphs();

    // create graph for each cluster
    for (int i = 0; i < model->K; ++i)
    {
        auto newGraph = addGraph();
        auto color = QColor(0x87 * i % 256, 0xf * i % 256, 0x57 * i % 256);
        newGraph->setLineStyle(QCPGraph::lsNone);
        //newGraph->setBrush(QBrush(color, Qt::SolidPattern));
        newGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, color, color, 12));
        newGraph->setPen(QPen(color));
    }

    // add points to graphs
    for (int i = 0; i < model->K; ++i)
    {
        int cluster = model->Clusters[i];
        auto currentGraph = graph(cluster);
        auto point = model->Data[i];
        currentGraph->addData(point.X(), point.Y());
    }

    rescaleAxes();
    auto range = xAxis->range();
    range.lower = floor(range.lower -1);
    range.upper = ceil(range.upper + 1);
    xAxis->setRange(range);

    range = yAxis->range();
    range.lower = floor(range.lower - 1);
    range.upper = ceil(range.upper + 1);
    yAxis->setRange(range);
    replot();
}
