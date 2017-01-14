#include "chartview.h"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>
#include <windows.h>
#pragma comment (lib, "User32.lib")


ChartView::ChartView(QWidget *parent) :
    QChartView(new QChart(), parent)
{
    QScatterSeries *series0 = new QScatterSeries();
    series0->setName("scatter1");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(15.0);

    QScatterSeries *series1 = new QScatterSeries();
    series1->setName("scatter2");
    series1->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    series1->setMarkerSize(15.0);

    auto *series2 = new QLineSeries();
    series2->setName("scatter3");

    auto *series3 = new QScatterSeries();
    series3->setName("punkty dla linii");
    //series2->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    //series2->setMarkerSize(15.0);

    series0->append(0, 6);
    series0->append(2, 4);
    series0->append(3, 8);
    series0->append(7, 4);
    series0->append(10, 5);
    series0->append(5, 6);

    *series1 << QPointF(1, 1) << QPointF(3, 3) << QPointF(7, 6) << QPointF(8, 3) << QPointF(10, 2);

    *series2 << QPointF(5, 5) << QPointF(5, 8);

    *series3 << QPointF(5, 5) << QPointF(5, 8);







    /*QPainterPath starPath;
    starPath.moveTo(30, 15);
    for (int i = 1; i < 5; ++i) {
        starPath.lineTo(15 + 15 * qCos(0.8 * i * Pi),
                        15 + 15 * qSin(0.8 * i * Pi));
    }
    starPath.closeSubpath();

    QImage star(30, 30, QImage::Format_ARGB32);
    star.fill(Qt::transparent);

    QPainter painter(&star);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QRgb(0xf6a625));
    painter.setBrush(painter.pen().color());
    painter.drawPath(starPath);

    series2->setBrush(star);
    */

    /*QColor lel;
    lel.setBlue(255);
    series2->setColor(lel);

    series3->setColor(lel);
    setRenderHint(QPainter::Antialiasing);

    chart()->addSeries(series3);/*



    /*QList<QLegendMarker *> markers = chart()->legend()->markers(series2);
    for (int i = 0; i < markers.count(); i++)
        markers.at(i)->setBrush(painter.pen().color());*/

    chart()->addSeries(series0);
    chart()->addSeries(series1);
    chart()->addSeries(series2);
    chart()->setTitle("LEL");
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);
}

void ChartView::xd()
{
    auto lel = new QScatterSeries;
    *lel << QPointF(-5, -5) << QPointF(-1, -1);
    lel->setName("scatterXD");
    lel->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    lel->setMarkerSize(25.0);
    chart()->addSeries(lel);
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    auto pos = event->pos();
}
