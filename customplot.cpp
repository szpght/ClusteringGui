#include "customplot.h"

CustomPlot::CustomPlot()
{
    xAxis->setLabel("x");
    yAxis->setLabel("y");
}


QCPGraph* CustomPlot::_newGraph(int index)
{
	auto newGraph = addGraph();
	auto color = QColor(0x87 * index % 256, 0xf * index % 256, 0x57 * index % 256);
	newGraph->setLineStyle(QCPGraph::lsNone);
	newGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, color, color, 12));
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
    clearGraphs();

    // create graph for each cluster
    for (int i = 0; i < model->K; ++i)
    {
		_newGraph(i);
    }

    // add points to graphs
    for (int i = 0; i < model->Data.size(); ++i)
    {
        int cluster = model->Clusters[i];
        auto currentGraph = graph(cluster);
        auto point = model->Data[i];
        currentGraph->addData(point.X(), point.Y());
    }

	_fixAxes();
    replot();
}
