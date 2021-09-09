#include "gmedge.h"
#include "json/json.hpp"
#include <sstream>
#include <iostream>
#include "gmsocket.h"

GMEdge::GMEdge(GMScene *scene, GMSocketInterface *start_socket, GMSocketInterface *end_socket)
{
    m_id = GMScene::GenerateIDforGMObject();
    m_gm_scene = scene;
    m_start_socket = start_socket;
    m_end_socket = end_socket;
    m_gmqt_edge = new GMQtGraphicsEdge();
    m_gmqt_edge->SetSource(m_start_socket->GetSocketPosition()+QPointF(10,10));
    m_gmqt_edge->SetTarget(m_end_socket->GetSocketPosition()+QPointF(10,10));
    // Add Related Edge to socket
    m_start_socket->AddRelatedEdge(this);
    m_end_socket->AddRelatedEdge(this);
    scene->GetGraphicsScenePtr()->addItem(m_gmqt_edge);
    scene->AddEdge(this);
}


GMEdge::GMEdge(GMScene *scene, QPointF start, QPointF end)
{   m_gm_scene = scene;
    m_gmqt_edge = new GMQtGraphicsEdge();
    scene->GetGraphicsScenePtr()->addItem(m_gmqt_edge);
    m_gmqt_edge->SetSource(start);
    m_gmqt_edge->SetTarget(end);
}

GMEdge::GMEdge(GMScene *scene, GMNode *node1, int pos1, GMNode *node2, int pos2)
{
    m_gm_scene = scene;
    m_id = GMScene::GenerateIDforGMObject();
    m_start_socket = node1->GetGMSocket(pos1);
    m_end_socket = node2->GetGMSocket(pos2);
    m_gmqt_edge = new GMQtGraphicsEdge();
    m_gmqt_edge->SetSource(m_start_socket->GetSocketPosition()+QPointF(10,10));
    m_gmqt_edge->SetTarget(m_end_socket->GetSocketPosition()+QPointF(10,10));
    // Add Related Edge to socket
    m_start_socket->AddRelatedEdge(this);
    m_end_socket->AddRelatedEdge(this);
    m_gm_scene->GetGraphicsScenePtr()->addItem(m_gmqt_edge);
    m_gm_scene->AddEdge(this);
}

GMEdge::GMEdge(GMScene *scene)
{
    m_gm_scene = scene;
    m_gmqt_edge = new GMQtGraphicsEdge();
    m_gm_scene->GetGraphicsScenePtr()->addItem(m_gmqt_edge);

}

void GMEdge::SetTarget(QPointF des)
{
    if(m_gmqt_edge!=nullptr){
        m_gmqt_edge->SetTarget(des+QPointF(10,10));
        m_gmqt_edge->update();
    }
}

std::pair<double, double> GMEdge::GetSource()
{
    return std::make_pair(m_gmqt_edge->GetSource().rx(),m_gmqt_edge->GetSource().ry());
}

std::pair<double, double> GMEdge::GetTarget()
{
    return std::make_pair(m_gmqt_edge->GetTarget().rx(),m_gmqt_edge->GetTarget().ry());
}

void GMEdge::UpdatePositions()
{
    QPointF start = m_start_socket->GetSocketPosition();
    QPointF end=m_end_socket->GetSocketPosition();
    if(m_gmqt_edge!=nullptr){
        m_gmqt_edge->SetSource(start+QPointF(10,10));
        m_gmqt_edge->SetTarget(end+QPointF(10,10));
        m_gmqt_edge->update();
    }
}

void GMEdge::RemoveEdge()
{
    //Find Stock Socket Related to this edge, and remove reference to this edge
    if(m_start_socket!=nullptr)
    {
        std::vector<StockEdgeInterface*> related_edges = m_start_socket->GetAllRelatedEdge();
        related_edges.erase(std::remove(related_edges.begin(),related_edges.end(),this),related_edges.end());
    }
    if(m_end_socket!=nullptr)
    {
        std::vector<StockEdgeInterface*> related_edges = m_end_socket->GetAllRelatedEdge();
        related_edges.erase(std::remove(related_edges.begin(),related_edges.end(),this),related_edges.end());
    }
    //Remove edges from the scene
    m_gm_scene->GetGraphicsScenePtr()->removeItem(m_gmqt_edge);
}

void GMEdge::ConnectGMNodes(GMScene* scene, GMNode *node1, int pos1, GMNode *node2, int pos2)
{

    m_gm_scene = scene;
    m_start_socket = node1->GetGMSocket(POSITION::SOUTH_ANCHOR);
    m_end_socket = node2->GetGMSocket(POSITION::NORTH_ANCHOR);
    m_gmqt_edge = new GMQtGraphicsEdge();
    m_gmqt_edge->SetSource(m_start_socket->GetSocketPosition()+QPointF(10,10));
    m_gmqt_edge->SetTarget(m_end_socket->GetSocketPosition()+QPointF(10,10));
    // Add Related Edge to socket
    m_start_socket->AddRelatedEdge(this);
    m_end_socket->AddRelatedEdge(this);
    m_gm_scene->GetGraphicsScenePtr()->addItem(m_gmqt_edge);
    m_gm_scene->AddEdge(this);
}

const int &GMEdge::GetStartSocketId() const
{
    return m_start_socket_id;
}

const int &GMEdge::GetEndSocketId() const
{
    return m_end_stock_id;
}

void GMEdge::SetStartAndEndSocket(GMSocketInterface *start, GMSocketInterface *end)
{
    m_start_socket = start;
    m_end_socket = end;
    m_gmqt_edge->SetSource(m_start_socket->GetSocketPosition()+QPointF(10,10));
    m_gmqt_edge->SetTarget(m_end_socket->GetSocketPosition()+QPointF(10,10));
    // Add Related Edge to socket
    m_start_socket->AddRelatedEdge(this);
    m_end_socket->AddRelatedEdge(this);
}

std::string GMEdge::serialize()
{
    GMSocket* gm_socket1 = (GMSocket*)m_start_socket;
    GMSocket* gm_socket2 = (GMSocket*)m_end_socket;
    nlohmann::json js_socket;
    nlohmann::json js_temp1; js_temp1["id"] = gm_socket1->GetGMID(); js_socket.push_back(js_temp1);
    nlohmann::json js_temp2; js_temp2["id"] = gm_socket2->GetGMID(); js_socket.push_back(js_temp2);

    nlohmann::json js =
    {
        {"id", m_id},
        {"scene",m_gm_scene->GetGMID()},
        {"socket", js_socket}
    };
    return js.dump();
}

GMObject* GMEdge::deserialize(std::string data)
{
    std::stringstream ss; ss<<data;
    nlohmann::json js;    ss>>js;
    m_id = js["id"];
    m_start_socket_id = js["socket"][0]["id"];
    m_end_stock_id = js["socket"][1]["id"];
    m_gm_scene->AddEdge(this);
    return nullptr;
}

const int &GMEdge::GetGMID() const
{
    return m_id;
}
