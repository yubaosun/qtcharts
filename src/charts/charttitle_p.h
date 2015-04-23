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

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTTITLE_P_H_
#define CHARTTITLE_P_H_

#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsTextItem>

QT_CHARTS_BEGIN_NAMESPACE

class ChartTitle : public QGraphicsTextItem
{
public:
    ChartTitle(QGraphicsItem *parent = 0);
    ~ChartTitle();
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;
    void setText(const QString &text);
    QString text() const;
    void setGeometry(const QRectF &rect);
private:
    QString m_text;
};

QT_CHARTS_END_NAMESPACE

#endif /* CHARTTITLE_P_H_ */
