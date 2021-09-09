#include "gmscene.h"
#include "gmqtgraphicsscene.h"
#include "gmedge.h"
#include "gmsocket.h"
#include "json/json.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>


int GMScene::id = 0;
GMScene::GMScene()
{
    m_gm_id = GMScene::GenerateIDforGMObject();
    m_stock_graphics_scene = new GMQtGraphicScene(this);
}

int GMScene::GenerateIDforGMObject()
{
    return id++;
}

void GMScene::AddNode(StockNodeInterface *stock_node_interface)
{
   GMNode* stock_node = (GMNode*)stock_node_interface;
   m_stock_graphics_scene->addItem( stock_node->GetStockGraphicsNode() );
   m_stock_node_container.push_back( stock_node );
   m_id_qmobject_map.insert( std::make_pair(stock_node->GetGMID(),stock_node) );

}

void GMScene::AddEdge(StockEdgeInterface *gm_edge1)
{
    GMEdge* gm_edge = static_cast<GMEdge*>(gm_edge1);
    m_stock_edge_container.push_back(gm_edge);
    m_id_qmobject_map.insert(std::make_pair(gm_edge->GetGMID(),gm_edge));
}

void GMScene::RemoveNode(StockNodeInterface *gm_node)
{
    //remove edge
    GMNode* gm_node_imp = static_cast<GMNode*>(gm_node);
    m_stock_graphics_scene->removeItem(gm_node_imp->GetStockGraphicsNode());
    m_stock_node_container.erase(std::remove
             (m_stock_node_container.begin(),
              m_stock_node_container.end(),
              gm_node),
             m_stock_node_container.end());
}

void GMScene::RemoveEdge(StockEdgeInterface *stock_edge)
{
    //remove edge
    GMEdge* stock_edge_imp = static_cast<GMEdge*>(stock_edge);
    stock_edge_imp->RemoveEdge();
    m_stock_edge_container.erase(
         std::remove( m_stock_edge_container.begin(),
                      m_stock_edge_container.end(),
                      stock_edge),
                     m_stock_edge_container.end());

}

void GMScene::AddSocket(GMSocketInterface *gm_socket1)
{
    GMSocket* gm_socket = static_cast<GMSocket*>(gm_socket1);
    m_stock_graphics_scene->addItem(gm_socket->GetStockGraphicsSocket());
    m_gm_socket_container.push_back(gm_socket1);
    m_id_qmobject_map.insert(std::make_pair(gm_socket->GetGMID(),gm_socket));
}

void GMScene::RemoveAllEdges()
{
    for(auto i:m_stock_edge_container){
        GMEdge* stock_edge_imp = static_cast<GMEdge*>(i);
        stock_edge_imp->RemoveEdge();
    }
    m_stock_edge_container.clear();
}

void GMScene::RemoveAllNodes()
{
    for(auto i:m_stock_node_container){
        GMNode* gm_node_imp = static_cast<GMNode*>(i);
        m_stock_graphics_scene->removeItem(gm_node_imp->GetStockGraphicsNode());
    }
    m_stock_node_container.clear();
}

void GMScene::RemoveAllSockets()
{
    for(auto i:m_gm_socket_container){
        GMSocket* gm_socket_imp = static_cast<GMSocket*>(i);
        //m_stock_graphics_scene->removeItem(gm_socket_imp->GetStockGraphicsSocket());
    }
    m_gm_socket_container.clear();
}

void GMScene::ClearScene()
{

    //first remove edge
    RemoveAllEdges();
    //then remove node
    RemoveAllNodes();
    // remove all sockets
    RemoveAllSockets();
    m_id_qmobject_map.clear();
}

void GMScene::DisplayMap()
{
    std::stringstream ss;
    ss<<this;
    std::string address;
    ss>>address;
    std::cout<<"display id"<<std::endl;
    std::cout<<address;
}

std::vector<StockNodeInterface *> GMScene::GetStockNodesVector()
{
    return m_stock_node_container;
}

std::vector<StockEdgeInterface *> GMScene::GetStockEdgesVector()
{
    return m_stock_edge_container;
}

QGraphicsScene* GMScene::GetGraphicsScenePtr()
{
    return m_stock_graphics_scene;
}

std::string GMScene::serialize()
{

    nlohmann::json js;

    // save the scene
    js["scene_id"] = m_gm_id;
    js["scene_width"] = m_stock_graphics_scene->width();
    js["scene_height"] = m_stock_graphics_scene->height();
    //save node
    nlohmann::json js_node;
    for(auto i:m_stock_node_container){
        GMNode* stock_node = (GMNode*)i;
        js_node.push_back({js_node.parse(stock_node->serialize())});
    }
    js["node"] = js_node;
    // edge
    nlohmann::json js_edge;
    for(auto i:m_stock_edge_container){
        GMEdge* stock_edge = (GMEdge*)i;
        js_edge.push_back({js_node.parse(stock_edge->serialize())});
    }
    js["edge"] = js_edge;
    //socket
    nlohmann::json js_socket;
    for(auto i:m_gm_socket_container){
        GMSocket* gm_socket = (GMSocket*)i;
        js_socket.push_back( {js_socket.parse(gm_socket->serialize())} );
    }
    js["socket"] = js_socket;
    return js.dump();
}

GMObject* GMScene::deserialize(std::string data)
{
    std::stringstream ss; ss<<data;
    nlohmann::json js;    ss>>js;
    //deserialize node
    for(int i=0; i < js["node"].size(); i++)
    {
        GMNode* gm_node = new GMNode(this,1);
        gm_node->deserialize(js["node"][i].dump());
    }

    for(int i=0; i < js["socket"].size(); i++)
    {
        for(auto i:m_id_qmobject_map){
            std::cout<<i.first<<"    "<<i.second<<std::endl;
        }
        GMSocket* gm_socket = new GMSocket(this);
        gm_socket->deserialize(js["socket"][i].dump());
    }

    // relate socket to nodes;

    for(auto i:m_stock_node_container){
        std::cout<<"this is node"<<std::endl;
        GMNode* gm_node = static_cast<GMNode*>(i);
        std::vector<int> related_socket_id = gm_node->GetRelatedSocketId();
        for(auto i:related_socket_id){
            GMObject* gm_object = m_id_qmobject_map.at(i);
            gm_node->SetAnchor(static_cast<GMSocket*>(gm_object));
        }

    }

    //deserialize edge

    for(int i=0; i < js["edge"].size(); i++)
    {

        GMEdge* gm_edge = new GMEdge(this);
        gm_edge->deserialize(js["edge"][i].dump());
        GMObject* gm_start = m_id_qmobject_map.at(gm_edge->GetStartSocketId());
        GMObject* gm_end = m_id_qmobject_map.at(gm_edge->GetEndSocketId());
        gm_edge->SetStartAndEndSocket(static_cast<GMSocket*>(gm_start),
                                      static_cast<GMSocket*>(gm_end));
    }
    return nullptr;
}

const int &GMScene::GetGMID() const
{
    return m_gm_id;
}






