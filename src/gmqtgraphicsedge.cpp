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
    m_path.moveTo(m_source);
    //QPainterPath path(m_source);
    m_path.lineTo(m_target);
    painter->drawPath(m_path);
    if(this->isSelected()){
        pen.setColor(Qt::white);
        painter->setPen(pen);
        painter->drawPath(m_path);
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

bool GMQtGraphicsEdge::isIntersectsWith(QPointF p1, QPointF p2)
{
    QPainterPath* path = new QPainterPath(p1);
    path->lineTo(p2);
    return path->intersects(m_path);
}
