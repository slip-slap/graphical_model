#ifndef STOCKNODEINTERFACE_H
#define STOCKNODEINTERFACE_H
#include <QPointF>

class StockNodeInterface
{
public:
    virtual void UpdateConnectedEdge()=0;
    virtual QPointF GetStockNodePosition()=0;
};
#endif // STOCKNODEINTERFACE_H
