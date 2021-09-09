#ifndef GRAPHICSNODE_H
#define GRAPHICSNODE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <string>
#include <QGraphicsSceneMouseEvent>
#include "stocknodeinterface.h"

class GMQtGraphicsNode: public QGraphicsItem
{
public:
    GMQtGraphicsNode();
    GMQtGraphicsNode(std::string title);
    GMQtGraphicsNode(StockNodeInterface* stock_node_interface,std::string title);

public:
    double GetNodeStartX();
    double GetNodeStartY();
    double GetNodeEndX();
    double GetNodeEndY();


public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    void InitUI();
private:
    std::string m_title;
    StockNodeInterface* m_stock_node_interface;
    double m_node_start_x;
    double m_node_start_y;
    double m_node_end_x;
    double m_node_end_y;
};

#endif // GRAPHICSNODE_H
