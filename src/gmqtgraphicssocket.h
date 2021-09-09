#ifndef GRAPHICSSOCKET_H
#define GRAPHICSSOCKET_H

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>

#include "gmsocketinterface.h"

class GMQtGraphicSocket:public QGraphicsItem
{
public:
    GMQtGraphicSocket();
    GMQtGraphicSocket(GMSocketInterface* stock_socket);
    GMSocketInterface* GetStockSocketInterface();

private:
    void InitUI();

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
private:
    GMSocketInterface* m_stock_socket_interface;
};

#endif // GRAPHICSSOCKET_H
