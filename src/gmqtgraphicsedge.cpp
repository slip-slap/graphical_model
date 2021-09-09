#include "gmqtgraphicsedge.h"


GMQtGraphicsEdge::GMQtGraphicsEdge():QGraphicsPathItem()
{
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
}


QRectF GMQtGraphicsEdge::boundingRect() const
{
    return QRectF(0,0,200,200);
}

void GMQtGraphicsEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen = QPen(Qt::red);
    pen.setWidth(5);
    painter->setPen(pen);
    painter->setBrush(QBrush(Qt::red));
    QPainterPath path(m_source);
    path.lineTo(m_target);
    painter->drawPath(path);
    if(this->isSelected()){
        pen.setColor(Qt::white);
        painter->setPen(pen);
        painter->drawPath(path);
    }
}

void GMQtGraphicsEdge::SetSource(QPointF source)
{
    m_source = source;
    this->update();
}

void GMQtGraphicsEdge::SetTarget(QPointF target)
{
    m_target = target;
    this->update();
}

QPointF GMQtGraphicsEdge::GetSource()
{
    return m_source;
}

QPointF GMQtGraphicsEdge::GetTarget()
{
    return m_target;
}
