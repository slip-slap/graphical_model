#ifndef STOCKEDGE_H
#define STOCKEDGE_H

#include "gmqtgraphicsscene.h"
#include "gmsocketinterface.h"
#include "gmqtgraphicsedge.h"
#include "gmscene.h"
#include "stockedgeinterface.h"
#include "gmobject.h"
#include "gmserializable.h"

class GMEdge: public StockEdgeInterface, public GMSerializable
{
public:
    GMEdge(GMScene* scene, GMSocketInterface* start_socket, GMSocketInterface* end_socket);
    GMEdge(GMScene* scene, QPointF start, QPointF end);
    GMEdge(GMScene* scene, GMNode* node1, int pos1, GMNode* node2, int pos2);
    GMEdge(GMScene* scene);
    void SetTarget(QPointF des);
    std::pair<double, double> GetSource();
    std::pair<double, double> GetTarget();
    void UpdatePositions() override;
    void RemoveEdge();
    void ConnectGMNodes(GMScene* scene, GMNode* node1, int pos1, GMNode* node2, int pos2);

public:
    const int& GetStartSocketId() const;
    const int& GetEndSocketId() const;
    void SetStartAndEndSocket(GMSocketInterface* start, GMSocketInterface* end);

public:
    std::string serialize() override;
    GMObject* deserialize(std::string str) override;
    const int& GetGMID() const;


private:
    GMScene* m_gm_scene=nullptr;
    GMSocketInterface* m_start_socket=nullptr;
    GMSocketInterface* m_end_socket=nullptr;
    GMQtGraphicsEdge* m_gmqt_edge=nullptr;
    int m_start_socket_id;
    int m_end_stock_id;
    int m_id;

};

#endif // STOCKEDGE_H
