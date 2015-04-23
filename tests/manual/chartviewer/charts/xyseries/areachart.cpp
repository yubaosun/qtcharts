/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include "charts.h"
#include <QtCharts/QChart>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLineSeries>

class AreaChart: public Chart
{
public:
    QString name() { return QObject::tr("AreaChart"); }
    QString category()  { return QObject::tr("XYSeries"); }
    QString subCategory() { return QString::null; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Area chart");

        // The lower series initialized to zero values
        QLineSeries *lowerSeries = 0;
        QString name("Series ");
        int nameIndex = 0;
        for (int i(0); i < table.count(); i++) {
            QLineSeries *upperSeries = new QLineSeries(chart);
            for (int j(0); j < table[i].count(); j++) {
                Data data = table[i].at(j);
                if (lowerSeries) {
                    const QList<QPointF>& points = lowerSeries->points();
                    upperSeries->append(QPointF(j, points[i].y() + data.first.y()));
                } else {
                    upperSeries->append(QPointF(j, data.first.y()));
                }
            }
            QAreaSeries *area = new QAreaSeries(upperSeries, lowerSeries);
            area->setName(name + QString::number(nameIndex));
            nameIndex++;
            chart->addSeries(area);
            chart->createDefaultAxes();
            lowerSeries = upperSeries;
        }
        return chart;
    }
};

DECLARE_CHART(AreaChart)

