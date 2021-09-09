#ifndef STOCKSOCKETINTERFACE_H
#define STOCKSOCKETINTERFACE_H

#include <QGraphicsItem>
#include <QPointF>
#include "stocknodeinterface.h"
#include "stockedgeinterface.h"
#include "gmserializable.h"

class GMSocketInterface: public GMSerializable
{
public:
    virtual QPointF GetSocketPosition()=0;
    virtual QGraphicsItem* GetStockGraphicsSocket()=0;
    virtual void SetStockNode(StockNodeInterface* stock_node_interface)=0;
    virtual void AddRelatedEdge(StockEdgeInterface* stock_edge_interface)=0;
    virtual std::vector<StockEdgeInterface*> GetAllRelatedEdge()=0;
    virtual StockNodeInterface* GetStockNode()=0;

};

#endif // STOCKSOCKETINTERFACE_H
