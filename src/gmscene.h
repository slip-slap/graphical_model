#ifndef GMScene_H
#define GMScene_H

#include <QGraphicsScene>
#include <vector>
#include <map>
#include "stocksceneinterface.h"
#include "stocknodeinterface.h"
#include "stockedgeinterface.h"
#include "gmsocketinterface.h"
#include "gmobject.h"
#include "gmserializable.h"

class GMScene: public GMSerializable
{

public:
    GMScene();
    static int id;
    static int GenerateIDforGMObject();
    void AddNode(StockNodeInterface* gm_node);
    void AddEdge(StockEdgeInterface* gm_edge);
    void RemoveNode(StockNodeInterface* gm_node);
    void RemoveEdge(StockEdgeInterface* gm_edge);
    void AddSocket(GMSocketInterface* gm_socket);
    void RemoeSocket(GMSocketInterface* gm_socket);
    void RemoveAllEdges();
    void RemoveAllNodes();
    void RemoveAllSockets();
    void ClearScene();
    void DisplayMap();
    std::vector<StockNodeInterface*> GetStockNodesVector();
    std::vector<StockEdgeInterface*> GetStockEdgesVector();
    QGraphicsScene *GetGraphicsScenePtr();

public:
    std::string serialize() override;
    GMObject* deserialize(std::string str) override;
    const int& GetGMID() const;

private:
    QGraphicsScene* m_stock_graphics_scene=nullptr;
    std::vector<StockNodeInterface*> m_stock_node_container;
    std::vector<StockEdgeInterface*> m_stock_edge_container;
    std::vector<GMSocketInterface*>  m_gm_socket_container;
    std::map<int, GMObject*> m_id_qmobject_map;
    int m_gm_id;
};

#endif // GMScene_H
