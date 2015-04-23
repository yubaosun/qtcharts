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

import QtQuick 2.0
import QtCharts 2.0

ChartView {
    title: "configuring dynamically"
    id: chartView
    property int index: 0

    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            switch (index) {
            case 0:
                lineSeries.axisX.max = 6;
                lineSeries.axisY.max = 6;
                break;
            case 1:
                scatterSeries.axisX.max = 10;
                scatterSeries.axisY.max = 10;
                break;
            default:
                chartView.axisX().max = 4;
                chartView.axisY().max = 4;
            }
            index = (index + 1) % 3;
        }
    }

    LineSeries {
        id: lineSeries
        name: "line series"
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1; y: 1 }
        XYPoint { x: 2; y: 2 }
        XYPoint { x: 3; y: 3 }
        XYPoint { x: 4; y: 4 }
    }

    ScatterSeries {
        id: scatterSeries
        name: "scatter series"
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 0.5; y: 1 }
        XYPoint { x: 1; y: 2 }
        XYPoint { x: 1.5; y: 3 }
        XYPoint { x: 2; y: 4 }
        XYPoint { x: 1; y: 1 }
        XYPoint { x: 2; y: 2 }
        XYPoint { x: 3; y: 3 }
        XYPoint { x: 4; y: 4 }
    }
}
