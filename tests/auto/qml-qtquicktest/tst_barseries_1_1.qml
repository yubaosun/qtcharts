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
import QtTest 1.0
import QtCharts 1.1

Rectangle {
    width: 400
    height: 300

    TestCase {
        id: tc1
        name: "tst_qml-qtquicktest BarSeries 1.1"
        when: windowShown

        function test_properties() {
            compare(barSeries.barWidth, 0.5);
            compare(barSeries.labelsVisible, false);
        }

        function test_append() {
            var setCount = 5;
            var valueCount = 50;
            addedSpy.clear();
            append(setCount, valueCount);

            compare(barSeries.count, setCount);
            for (var k = 0; k < setCount; k++) {
                compare(barSeries.at(k).count, valueCount);
                compare(barSeries.at(k).label, "barset" + k);
            }
            compare(addedSpy.count, setCount);

            barSeries.clear();
            compare(barSeries.count, 0);
        }

        function test_insert() {
            var setCount = 5;
            var valueCount = 50;
            addedSpy.clear();
            append(setCount, valueCount);

            for (var i = 0; i < setCount; i++) {
                var values = [];
                for (var j = 0; j < valueCount; j++)
                    values[j] = Math.random() * 10;
                var set = barSeries.insert(i, "barset" + i, values);
                compare(set.label, "barset" + i);
            }

            compare(barSeries.count, setCount * 2);
            for (var k = 0; k < setCount * 2; k++)
                compare(barSeries.at(k).count, valueCount);
            compare(addedSpy.count, 2 * setCount);

            barSeries.clear();
            compare(barSeries.count, 0);
        }

        function test_remove() {
            var setCount = 5;
            var valueCount = 50;
            removedSpy.clear();
            append(setCount, valueCount);

            for (var k = 0; k < setCount; k++)
                barSeries.remove(barSeries.at(0));

            compare(barSeries.count, 0);
            compare(removedSpy.count, setCount);
        }

        // Not a test function, used by one or more test functions
        function append(setCount, valueCount) {
            for (var i = 0; i < setCount; i++) {
                var values = [];
                for (var j = 0; j < valueCount; j++)
                    values[j] = Math.random() * 10;
                barSeries.append("barset" + i, values);
            }
        }
    }

    ChartView {
        id: chartView
        anchors.fill: parent

        BarSeries {
            axisX: BarCategoriesAxis {}
            axisY: ValuesAxis { min: 0; max: 10 }
            id: barSeries
            name: "bar"

            SignalSpy {
                id: addedSpy
                target: barSeries
                signalName: "barsetsAdded"
            }
            SignalSpy {
                id: removedSpy
                target: barSeries
                signalName: "barsetsRemoved"
            }
        }
    }
}
