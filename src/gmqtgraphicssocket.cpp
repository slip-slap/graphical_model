#include "gmqtgraphicssocket.h"
#include <QGraphicsSceneMouseEvent>
#include <iostream>
GMQtGraphicSocket::GMQtGraphicSocket()
{
    this->InitUI();
}

GMQtGraphicSocket::GMQtGraphicSocket(GMSocketInterface *stock_socket)
{
    this->InitUI();
    this->m_stock_socket_interface = stock_socket;
}

GMSocketInterface *GMQtGraphicSocket::GetStockSocketInterface()
{
    return m_stock_socket_interface;
}

void GMQtGraphicSocket::InitUI()
{
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}


QRectF GMQtGraphicSocket::boundingRect() const
{
    return QRectF(0,0,20,20);
}

void GMQtGraphicSocket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QColor(Qt::red));
    painter->setBrush(QColor(Qt::red));
    if(this->isSelected()){
        painter->setPen(QColor(Qt::yellow));
        painter->drawEllipse(0,0,21,21);
    }
    painter->drawEllipse(0,0,20,20);
}

