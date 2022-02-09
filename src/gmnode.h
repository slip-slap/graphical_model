#ifndef STOCKNODE_H
#define STOCKNODE_H


#include "gmsocketinterface.h"
#include "stocknodeinterface.h"
#include "gmqtgraphicsnode.h"
#include "gmscene.h"
#include <QGraphicsScene>
#include <string>

#include "gmobject.h"
#include "gmserializable.h"

enum POSITION {NORTH_ANCHOR, SOUTH_ANCHOR, EAST_ANCHOR, WEST_ANCHOR};

class GMNode: public StockNodeInterface, public GMSerializable
{
public:
    GMNode(GMScene* scene);
    GMNode(GMScene* scene, int placeholder);
    GMNode(GMScene* scene, std::string title);

    GMQtGraphicsNode* GetStockGraphicsNode();
    GMScene* GetGMScene();

    void RemoveNode();
    GMSocketInterface* GetGMSocket(int pos);
    void SetStockNodePosition(QPointF pos);

    void UpdateConnectedEdge() override;
    QPointF GetStockNodePosition() override;


public:
    std::pair<double, double> GetNorthAnchor();
    std::pair<double, double> GetSouthAnchor();
    std::pair<double, double> GetWestAnchor();
    std::pair<double, double> GetEastAnchor();
    std::pair<double, double> GetAnchor(int pos);
    const int& GetGMID() const;

    const std::vector<int>& GetRelatedSocketId() const;
    void SetAnchor(GMSocketInterface* anchor);


public:
    std::string serialize() override;
    GMObject* deserialize(std::string str) override;
    friend std::ostream& operator<<(std::ostream& out, const GMNode& obj);
private:
    GMQtGraphicsNode* m_gmqt_graphics_node;
    GMSocketInterface* m_gm_north_anchor=nullptr;
    GMSocketInterface* m_gm_south_anchor=nullptr;
    std::vector<int> m_related_socket_ids;
    GMScene* m_gm_scene;
    int m_id;
};

#endif // STOCKNODE_H
