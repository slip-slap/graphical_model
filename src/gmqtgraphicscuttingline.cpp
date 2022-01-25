#include "gmqtgraphicscuttingline.h"
#include <QPen>
GMQtGraphicsCuttingLine::GMQtGraphicsCuttingLine()
{

}

GMQtGraphicsCuttingLine::GMQtGraphicsCuttingLine(GMQtGraphicScene *stock_graphics_scene)
{
    stock_graphics_scene->addItem(this);
}

void GMQtGraphicsCuttingLine::AppendQPoint(QPoint point)
{
    m_qpoints.append(point);
}

QVector<QPoint> GMQtGraphicsCuttingLine::getQpoints() const
{
    return m_qpoints;
}

void GMQtGraphicsCuttingLine::ClearPoint()
{
    m_qpoints.clear();
}


QRectF GMQtGraphicsCuttingLine::boundingRect() const
{
    return QRectF(0,0,1,1);
}

void GMQtGraphicsCuttingLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                     QWidget *widget)
{
    QPen pen(Qt::green);
    QVector<qreal> pattern{3,3};
    pen.setDashPattern(pattern);
    painter->setPen(pen);
    painter->drawPolyline(QPolygonF(m_qpoints));

}
