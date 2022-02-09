#include "gmnode.h"
#include "gmsocket.h"
#include <iostream>
#include <string>
#include <sstream>

#include "json/json.hpp"

GMNode::GMNode(GMScene *scene)
{
    m_id = GMScene::GenerateIDforGMObject();
    m_gm_scene = scene;
    m_gmqt_graphics_node = new GMQtGraphicsNode(this,"nothing");
    m_gm_north_anchor= new GMSocket(this, POSITION::NORTH_ANCHOR);
    m_gm_south_anchor= new GMSocket(this, POSITION::SOUTH_ANCHOR);
    GMSocket* gm_socket1 = static_cast<GMSocket*>(m_gm_north_anchor);
    gm_socket1->GetStockGraphicsSocket()->setParentItem(m_gmqt_graphics_node);
    GMSocket* gm_socket2 = static_cast<GMSocket*>(m_gm_south_anchor);
    gm_socket2->GetStockGraphicsSocket()->setParentItem(m_gmqt_graphics_node);

    m_gm_scene->AddNode(this);
}

GMNode::GMNode(GMScene *scene, int placeholder)
{
    m_gm_scene = scene;
    m_gmqt_graphics_node = new GMQtGraphicsNode(this,"nothing");

}

GMNode::GMNode(GMScene *scene, std::string title)
{
    m_id = GMScene::GenerateIDforGMObject();
    m_gm_scene = scene;
    m_gmqt_graphics_node = new GMQtGraphicsNode(this,title);
    m_gm_north_anchor= new GMSocket(this, POSITION::NORTH_ANCHOR);
    m_gm_south_anchor= new GMSocket(this, POSITION::SOUTH_ANCHOR);
    GMSocket* gm_socket1 = static_cast<GMSocket*>(m_gm_north_anchor);
    gm_socket1->GetStockGraphicsSocket()->setParentItem(m_gmqt_graphics_node);
    GMSocket* gm_socket2 = static_cast<GMSocket*>(m_gm_south_anchor);
    gm_socket2->GetStockGraphicsSocket()->setParentItem(m_gmqt_graphics_node);

    m_gm_scene->AddNode(this);
}


GMQtGraphicsNode *GMNode::GetStockGraphicsNode()
{
    return m_gmqt_graphics_node;
}

GMScene *GMNode::GetGMScene()
{
    return m_gm_scene;
}

void GMNode::RemoveNode()
{
}

GMSocketInterface *GMNode::GetGMSocket(int pos)
{
    if(pos == POSITION::NORTH_ANCHOR){
        return m_gm_north_anchor;
    }
    if(pos == POSITION::SOUTH_ANCHOR){
        return m_gm_south_anchor;
    }
    return nullptr;
}


void GMNode::SetStockNodePosition(QPointF pos)
{
    m_gmqt_graphics_node->setPos(pos);
    //GMSocket* gm_socket = static_cast<GMSocket*>(m_gm_north_anchor);
    //std::pair<double, double> pair = this->GetNorthAnchor();
    //gm_socket->SetPosition(pair);
    m_gmqt_graphics_node->update();
}

void GMNode::UpdateConnectedEdge()
{
    std::cout<<"update edges with related socket"<<std::endl;
    if(m_gm_north_anchor!=nullptr){
       //update nodes
       std::vector<StockEdgeInterface*> relatedEdge = m_gm_north_anchor->GetAllRelatedEdge();
       for(auto v:relatedEdge)
       {
           v->UpdatePositions();
       }
    }
    if(m_gm_south_anchor!=nullptr){
        std::vector<StockEdgeInterface*> relatedEdge = m_gm_south_anchor->GetAllRelatedEdge();
        for(auto v:relatedEdge)
        {
            v->UpdatePositions();
        }
    }
}

QPointF GMNode::GetStockNodePosition()
{
    return m_gmqt_graphics_node->pos();
}

std::pair<double, double> GMNode::GetNorthAnchor()
{
    double pos_x = m_gmqt_graphics_node->GetNodeStartX() + m_gmqt_graphics_node->GetNodeEndX();
    double pos_y = m_gmqt_graphics_node->GetNodeStartY();
    return std::make_pair(pos_x/2,pos_y);
}

std::pair<double, double> GMNode::GetSouthAnchor()
{
    double pos_x = m_gmqt_graphics_node->GetNodeStartX() + m_gmqt_graphics_node->GetNodeEndX();
    double pos_y = m_gmqt_graphics_node->GetNodeEndY();
    return std::make_pair(pos_x/2,pos_y);
}

std::pair<double, double> GMNode::GetWestAnchor()
{
    double pos_x = m_gmqt_graphics_node->GetNodeStartX();
    double pos_y = m_gmqt_graphics_node->GetNodeEndY()+ m_gmqt_graphics_node->GetNodeStartY();
    return std::make_pair(pos_x,pos_y/2);
}

std::pair<double, double> GMNode::GetEastAnchor()
{
    double pos_x = m_gmqt_graphics_node->GetNodeEndX();
    double pos_y = m_gmqt_graphics_node->GetNodeEndY()+ m_gmqt_graphics_node->GetNodeStartY();
    return std::make_pair(pos_x,pos_y/2);
}

std::pair<double, double> GMNode::GetAnchor(int pos)
{
    if(pos == POSITION::NORTH_ANCHOR){
        return GetNorthAnchor();
    }
    if(pos == POSITION::SOUTH_ANCHOR){
        return GetSouthAnchor();
    }
    if(pos == POSITION::WEST_ANCHOR){
        return GetWestAnchor();
    }
    if(pos == POSITION::EAST_ANCHOR){
        return GetEastAnchor();
    }
    return GetEastAnchor();
}

const int &GMNode::GetGMID() const
{
    return m_id;
}

const std::vector<int> &GMNode::GetRelatedSocketId() const
{
    return m_related_socket_ids;
}

void GMNode::SetAnchor(GMSocketInterface *anchor)
{
    GMSocket* gm_socket = static_cast<GMSocket*>(anchor);
    int pos = gm_socket->GetPosition();
    if(pos == POSITION::NORTH_ANCHOR){
        m_gm_north_anchor = anchor;
        gm_socket->SetPosition(GetAnchor(POSITION::NORTH_ANCHOR));
        gm_socket->SetParentItem(m_gmqt_graphics_node);
    }
    if(pos == POSITION::SOUTH_ANCHOR){
        m_gm_south_anchor = anchor;
        gm_socket->SetPosition(GetAnchor(POSITION::SOUTH_ANCHOR));
        gm_socket->SetParentItem(m_gmqt_graphics_node);
    }
}

std::string GMNode::serialize()
{

    nlohmann::json js =
    {
        {"id", m_id},
        {"scene",m_gm_scene->GetGMID()},
        {"pos_x",m_gmqt_graphics_node->pos().rx()},
        {"pos_y",m_gmqt_graphics_node->pos().ry()}
    };
    GMSocket* gm_socket1 = (GMSocket*)m_gm_north_anchor;
    GMSocket* gm_socket2 = (GMSocket*)m_gm_south_anchor;
    nlohmann::json js_socket;
    nlohmann::json js_temp1; js_temp1["id"] = gm_socket1->GetGMID(); js_socket.push_back(js_temp1);
    nlohmann::json js_temp2; js_temp2["id"] = gm_socket2->GetGMID(); js_socket.push_back(js_temp2);
    js["socket"] = js_socket;
    return js.dump();
}

GMObject* GMNode::deserialize(std::string data)
{
    std::stringstream ss; ss<<data;
    nlohmann::json js;    ss>>js;
    m_id = js["id"];
    // socket deserialize
    /*GMSocket* north;
    GMSocket* south;
    for(int i = 0; i<js["socket"].size(); i++){
        GMSocket* gm_socket = new GMSocket();
        gm_socket->deserialize(data);
        if(gm_socket->GetPosition() == POSITION::NORTH_ANCHOR){
            north = gm_socket;
            north->SetParentItem(m_gmqt_graphics_node);
            std::pair<double, double> pos = GetAnchor(north->GetPosition());
            north->SetPosition(pos);

        }
        if(gm_socket->GetPosition() == POSITION::SOUTH_ANCHOR){
            south = gm_socket;
            south->SetParentItem(m_gmqt_graphics_node);
            south->SetPosition(GetAnchor(south->GetPosition()));
        }
    }*/

    this->SetStockNodePosition(QPointF(js["pos_x"],js["pos_y"]));
    for(int i=0; i<js["socket"].size(); i++){
        std::cout<<js.dump(4)<<std::endl;
        int id = js["socket"][i]["id"];
        m_related_socket_ids.push_back(js["socket"][i]["id"]);
    }
    m_gm_scene->AddNode(this);
    return nullptr;
}

std::ostream& operator<<(std::ostream& out, const GMNode& obj)
{
    std::cout<<&obj<<std::endl;

    return out;
}
