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

#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H

#include <QtWidgets/QWidget>

class InspectorWidget : public QWidget
{
public:
    InspectorWidget();
    ~InspectorWidget();

private:
    QIcon getColorIcon(const QColor& color,const QSize &size) const;

};

#endif
