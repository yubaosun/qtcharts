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

#include <private/xlogydomain_p.h>
#include <private/qabstractaxis_p.h>
#include <QtCharts/QLogValueAxis>
#include <QtCore/QtMath>
#include <cmath>

QT_CHARTS_BEGIN_NAMESPACE

XLogYDomain::XLogYDomain(QObject *parent)
    : AbstractDomain(parent),
      m_logLeftY(0),
      m_logRightY(1),
      m_logBaseY(10)
{
}

XLogYDomain::~XLogYDomain()
{
}

void XLogYDomain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    bool axisXChanged = false;
    bool axisYChanged = false;

    adjustLogDomainRanges(minY, maxY);

    if (!qFuzzyIsNull(m_minX - minX) || !qFuzzyIsNull(m_maxX - maxX)) {
        m_minX = minX;
        m_maxX = maxX;
        axisXChanged = true;
        if(!m_signalsBlocked)
            emit rangeHorizontalChanged(m_minX, m_maxX);
    }

    if (!qFuzzyIsNull(m_minY - minY) || !qFuzzyIsNull(m_maxY - maxY)) {
        m_minY = minY;
        m_maxY = maxY;
        axisYChanged = true;
        qreal logMinY = std::log10(m_minY) / std::log10(m_logBaseY);
        qreal logMaxY = std::log10(m_maxY) / std::log10(m_logBaseY);
        m_logLeftY = logMinY < logMaxY ? logMinY : logMaxY;
        m_logRightY = logMinY > logMaxY ? logMinY : logMaxY;
        if (!m_signalsBlocked)
            emit rangeVerticalChanged(m_minY, m_maxY);
    }

    if (axisXChanged || axisYChanged)
        emit updated();
}

void XLogYDomain::zoomIn(const QRectF &rect)
{
    storeZoomReset();
    qreal dx = spanX() / m_size.width();
    qreal maxX = m_maxX;
    qreal minX = m_minX;

    maxX = minX + dx * rect.right();
    minX = minX + dx * rect.left();

    qreal logLeftY = m_logRightY - rect.bottom() * (m_logRightY - m_logLeftY) / m_size.height();
    qreal logRightY = m_logRightY - rect.top() * (m_logRightY - m_logLeftY) / m_size.height();
    qreal leftY = qPow(m_logBaseY, logLeftY);
    qreal rightY = qPow(m_logBaseY, logRightY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    setRange(minX, maxX, minY, maxY);
}

void XLogYDomain::zoomOut(const QRectF &rect)
{
    storeZoomReset();
    qreal dx = spanX() / rect.width();
    qreal maxX = m_maxX;
    qreal minX = m_minX;

    minX = maxX - dx * rect.right();
    maxX = minX + dx * m_size.width();

    const qreal factorY = m_size.height() / rect.height();
    qreal newLogMinY = m_logLeftY + (m_logRightY - m_logLeftY) / 2 * (1 - factorY);
    qreal newLogMaxY = m_logLeftY + (m_logRightY - m_logLeftY) / 2 * (1 + factorY);
    qreal leftY = qPow(m_logBaseY, newLogMinY);
    qreal rightY = qPow(m_logBaseY, newLogMaxY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    setRange(minX, maxX, minY, maxY);
}

void XLogYDomain::move(qreal dx, qreal dy)
{
    qreal x = spanX() / m_size.width();
    qreal maxX = m_maxX;
    qreal minX = m_minX;

    if (dx != 0) {
        minX = minX + x * dx;
        maxX = maxX + x * dx;
    }

    qreal stepY = dy * (m_logRightY - m_logLeftY) / m_size.height();
    qreal leftY = qPow(m_logBaseY, m_logLeftY + stepY);
    qreal rightY = qPow(m_logBaseY, m_logRightY + stepY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    setRange(minX, maxX, minY, maxY);
}

QPointF XLogYDomain::calculateGeometryPoint(const QPointF &point, bool &ok) const
{
    const qreal deltaX = m_size.width() / (m_maxX - m_minX);
    const qreal deltaY = m_size.height() / qAbs(m_logRightY - m_logLeftY);

    qreal x = (point.x() - m_minX) * deltaX;
    qreal y(0);
    if (point.y() > 0) {
        y = (std::log10(point.y()) / std::log10(m_logBaseY)) * -deltaY - m_logLeftY * -deltaY + m_size.height();
        ok = true;
    } else {
        y = m_size.height();
        qWarning() << "Logarithms of zero and negative values are undefined.";
        ok = false;
    }
    return QPointF(x, y);
}

QVector<QPointF> XLogYDomain::calculateGeometryPoints(const QList<QPointF> &vector) const
{
    const qreal deltaX = m_size.width() / (m_maxX - m_minX);
    const qreal deltaY = m_size.height() / qAbs(m_logRightY - m_logLeftY);

    QVector<QPointF> result;
    result.resize(vector.count());

    for (int i = 0; i < vector.count(); ++i) {
        if (vector[i].y() > 0) {
            qreal x = (vector[i].x() - m_minX) * deltaX;
            qreal y = (std::log10(vector[i].y()) / std::log10(m_logBaseY)) * -deltaY - m_logLeftY * -deltaY + m_size.height();
            result[i].setX(x);
            result[i].setY(y);
        } else {
            qWarning() << "Logarithms of zero and negative values are undefined.";
            return QVector<QPointF>();
        }
    }
    return result;
}

QPointF XLogYDomain::calculateDomainPoint(const QPointF &point) const
{
    const qreal deltaX = m_size.width() / (m_maxX - m_minX);
    const qreal deltaY = m_size.height() / qAbs(m_logRightY - m_logLeftY);
    qreal x = point.x() / deltaX + m_minX;
    qreal y = qPow(m_logBaseY, m_logLeftY + (m_size.height() - point.y()) / deltaY);
    return QPointF(x, y);
}

bool XLogYDomain::attachAxis(QAbstractAxis *axis)
{
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if (logAxis && logAxis->orientation() == Qt::Vertical) {
        QObject::connect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleVerticalAxisBaseChanged(qreal)));
        handleVerticalAxisBaseChanged(logAxis->base());
    }
    return  AbstractDomain::attachAxis(axis);
}

bool XLogYDomain::detachAxis(QAbstractAxis *axis)
{
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if (logAxis && logAxis->orientation() == Qt::Vertical)
        QObject::disconnect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleVerticalAxisBaseChanged(qreal)));

    return AbstractDomain::detachAxis(axis);
}

void XLogYDomain::handleVerticalAxisBaseChanged(qreal baseY)
{
    m_logBaseY = baseY;
    qreal logMinY = std::log10(m_minY) / std::log10(m_logBaseY);
    qreal logMaxY = std::log10(m_maxY) / std::log10(m_logBaseY);
    m_logLeftY = logMinY < logMaxY ? logMinY : logMaxY;
    m_logRightY = logMinY > logMaxY ? logMinY : logMaxY;
    emit updated();
}

// operators

bool QT_CHARTS_AUTOTEST_EXPORT operator== (const XLogYDomain &domain1, const XLogYDomain &domain2)
{
    return (qFuzzyIsNull(domain1.m_maxX - domain2.m_maxX)
            && qFuzzyIsNull(domain1.m_maxY - domain2.m_maxY)
            && qFuzzyIsNull(domain1.m_minX - domain2.m_minX)
            && qFuzzyIsNull(domain1.m_minY - domain2.m_minY));
}


bool QT_CHARTS_AUTOTEST_EXPORT operator!= (const XLogYDomain &domain1, const XLogYDomain &domain2)
{
    return !(domain1 == domain2);
}


QDebug QT_CHARTS_AUTOTEST_EXPORT operator<<(QDebug dbg, const XLogYDomain &domain)
{
#ifdef QT_NO_TEXTSTREAM
    Q_UNUSED(domain)
#else
    dbg.nospace() << "AbstractDomain(" << domain.m_minX << ',' << domain.m_maxX << ',' << domain.m_minY << ',' << domain.m_maxY << ')' << domain.m_size;
#endif
    return dbg.maybeSpace();
}

#include "moc_xlogydomain_p.cpp"

QT_CHARTS_END_NAMESPACE
