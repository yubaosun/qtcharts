#include "charttheme_p.h"
#include "qchart.h"


//series
#include "barchartseries.h"
#include "stackedbarchartseries.h"
#include "percentbarchartseries.h"
#include "qlinechartseries.h"
//items
#include "axisitem_p.h"
#include "bargroup.h"
#include "stackedbargroup.h"
#include "linechartitem_p.h"
#include "percentbargroup.h"

//themes
#include "chartthemevanilla_p.h"
#include "chartthemeicy_p.h"
#include "chartthemegrayscale_p.h"
#include "chartthemescientific_p.h"


QTCOMMERCIALCHART_BEGIN_NAMESPACE

/* TODO
    case QChart::ChartThemeUnnamed1:
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xff3fa9f5)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xff7AC943)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xffFF931E)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xffFF1D25)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xffFF7BAC)), 2));

        m_gradientStartColor = QColor(QRgb(0xfff3dc9e));
        m_gradientEndColor = QColor(QRgb(0xffafafaf));
*/

ChartTheme::ChartTheme()
{
    m_seriesColor.append(QRgb(0xff000000));
    m_seriesColor.append(QRgb(0xff707070));
    m_gradientStartColor = QColor(QRgb(0xffffffff));
    m_gradientEndColor = QColor(QRgb(0xffafafaf));
}


ChartTheme* ChartTheme::createTheme(QChart::ChartThemeId theme)
{
    switch(theme) {
        case QChart::ChartThemeDefault:
            return new ChartTheme();
        case QChart::ChartThemeVanilla:
            return new ChartThemeVanilla();
        case QChart::ChartThemeIcy:
            return new ChartThemeIcy();
        case QChart::ChartThemeGrayscale:
            return new ChartThemeGrayscale();
        case QChart::ChartThemeScientific:
            return new ChartThemeScientific();
    }
}

void ChartTheme::decorate(QChart* chart)
{
    QLinearGradient backgroundGradient;
    backgroundGradient.setColorAt(0.0, m_gradientStartColor);
    backgroundGradient.setColorAt(1.0, m_gradientEndColor);
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setChartBackgroundBrush(backgroundGradient);
}
//TODO helper to by removed later
void ChartTheme::decorate(ChartItem* item, QChartSeries* series,int count)
{
    switch(series->type())
    {
        case QChartSeries::SeriesTypeLine: {
            QLineChartSeries* s = static_cast<QLineChartSeries*>(series);
            LineChartItem* i = static_cast<LineChartItem*>(item);
            decorate(i,s,count);
            break;
        }
        case QChartSeries::SeriesTypeBar: {
            BarChartSeries* b = static_cast<BarChartSeries*>(series);
            BarGroup* i = static_cast<BarGroup*>(item);
            decorate(i,b,count);
            break;
        }
        case QChartSeries::SeriesTypeStackedBar: {
            StackedBarChartSeries* s = static_cast<StackedBarChartSeries*>(series);
            StackedBarGroup* i = static_cast<StackedBarGroup*>(item);
            decorate(i,s,count);
            break;
        }
        case QChartSeries::SeriesTypePercentBar: {
            PercentBarChartSeries* s = static_cast<PercentBarChartSeries*>(series);
            PercentBarGroup* i = static_cast<PercentBarGroup*>(item);
            decorate(i,s,count);
            break;
        }
        default:
        qDebug()<<"Wrong item to be decorated by theme";
        break;
    }

}

void ChartTheme::decorate(LineChartItem* item, QLineChartSeries* series,int count)
{
    item->setPen(series->pen());
}

void ChartTheme::decorate(BarGroup* item, BarChartSeries* series,int count)
{
    item->addColor(QColor(255,0,0,128));
    item->addColor(QColor(255,255,0,128));
    item->addColor(QColor(0,255,0,128));
    item->addColor(QColor(0,0,255,128));
    item->addColor(QColor(255,128,0,128));
}

void ChartTheme::decorate(StackedBarGroup* item, StackedBarChartSeries* series,int count)
{
    // Add some fugly colors for 5 fist series...
    item->addColor(QColor(255,0,0,128));
    item->addColor(QColor(255,255,0,128));
    item->addColor(QColor(0,255,0,128));
    item->addColor(QColor(0,0,255,128));
    item->addColor(QColor(255,128,0,128));
}

void ChartTheme::decorate(PercentBarGroup* item, PercentBarChartSeries* series,int count)
{
// Add some fugly colors for 5 fist series...
    item->addColor(QColor(255,0,0,128));
    item->addColor(QColor(255,255,0,128));
    item->addColor(QColor(0,255,0,128));
    item->addColor(QColor(0,0,255,128));
    item->addColor(QColor(255,128,0,128));
}


QTCOMMERCIALCHART_END_NAMESPACE
