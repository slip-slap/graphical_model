#ifndef GRAPHICSEDGE_H
#define GRAPHICSEDGE_H

#include <QGraphicsPathItem>
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include "gmscene.h"


class GMQtGraphicsEdge: public QGraphicsPathItem
{
public:
    GMQtGraphicsEdge();


public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void SetSource(QPointF source);
    void SetTarget(QPointF target);
    QPointF GetSource();
    QPointF GetTarget();

private:
    QPointF m_source;
    QPointF m_target;
};

#endif // GRAPHICSEDGE_H
