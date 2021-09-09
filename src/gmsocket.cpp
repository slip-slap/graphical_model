#include <sstream>
#include "gmsocket.h"
#include "json/json.hpp"

GMSocket::GMSocket(GMScene* scene)
{
    m_gmqt_graphics_socket = new GMQtGraphicSocket(this);
    m_gm_scene = scene;

}

GMSocket::GMSocket(GMNode* parent, int pos)
{
    m_gm_id = GMScene::GenerateIDforGMObject();
    m_gmqt_graphics_socket = new GMQtGraphicSocket(this);
    m_position = pos;
    m_gm_node = parent;
    this->SetPosition(parent->GetAnchor(pos));
    m_gm_scene = parent->GetGMScene();
    m_gm_scene->AddSocket(this);

}


GMQtGraphicSocket *GMSocket::GetStockGraphicsSocket()
{
    return m_gmqt_graphics_socket;
}

QPointF GMSocket::GetSocketPosition()
{
    return m_gmqt_graphics_socket->mapToScene(0,0);
}

void GMSocket::SetStockNode(StockNodeInterface *stock_node)
{
    m_gmqt_node_ptr = stock_node;
}


void GMSocket::AddRelatedEdge(StockEdgeInterface *stock_edge_ptr)
{
    m_gmqt_edge_interface_vec.push_back(stock_edge_ptr);
}

std::vector<StockEdgeInterface *> GMSocket::GetAllRelatedEdge()
{
    return m_gmqt_edge_interface_vec;
}

StockNodeInterface *GMSocket::GetStockNode()
{
    return m_gmqt_node_ptr;
}


void GMSocket::SetPosition(std::pair<double, double> pos)
{
    m_gmqt_graphics_socket->setPos(QPointF(pos.first, pos.second));
    m_gmqt_graphics_socket->update();
}

void GMSocket::SetIdentifier(int identifier)
{
    m_gm_id = identifier;
}

int GMSocket::GetPosition()
{
    return m_position;
}

void GMSocket::SetLocalPosition(int pos)
{
    m_position = pos;
}

void GMSocket::SetParentItem(QGraphicsItem *parent)
{
    m_gmqt_graphics_socket->setParentItem(parent);
    m_gmqt_graphics_socket->update();
}


std::string GMSocket::serialize()
{
    nlohmann::json js;
    js["id"] = m_gm_id;
    js["position"] = m_position;
    nlohmann::json json_related_edge;
    for(auto i:m_gmqt_edge_interface_vec){
        GMEdge* gm_edge = static_cast<GMEdge*>(i);
        nlohmann::json js_temp1; js_temp1["id"] = gm_edge->GetGMID(); json_related_edge.push_back(js_temp1);
    }
    js["connected_edges"] = json_related_edge;
    return js.dump();
}

GMObject* GMSocket::deserialize(std::string data)
{
    std::stringstream ss; ss<<data;
    nlohmann::json js; ss>>js;
    m_gm_id = js["id"];
    m_position = js["position"];
    m_gm_scene->AddSocket(this);
    return nullptr;
}

const int &GMSocket::GetGMID() const
{
    return m_gm_id;
}

