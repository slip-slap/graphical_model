#include "stockscene.h"
#include "stockgraphicsscene.h"
#include "stockedge.h"
#include <algorithm>

StockScene::StockScene()
{
    m_stock_graphics_scene = new StockGraphicsScene(this);
}

void StockScene::AddNode(StockNodeInterface *stock_node_interface)
{
   StockNode* stock_node = (StockNode*)stock_node_interface;
   m_stock_graphics_scene->addItem(stock_node->GetStockGraphicsNode());
   m_stock_node_interface_vec.push_back(stock_node);
}

void StockScene::AddEdge(StockEdgeInterface *stock_edge)
{
    m_stock_edge_interface_vec.push_back(stock_edge);
}

void StockScene::RemoveNode(StockNodeInterface *stock_node)
{
    m_stock_node_interface_vec.erase(std::remove
                                          (
                                            m_stock_node_interface_vec.begin(),
                                            m_stock_node_interface_vec.end(),
                                            stock_node),
                                      m_stock_node_interface_vec.end()
                                     );
}

void StockScene::RemoveEdge(StockEdgeInterface *stock_edge)
{
    //remove edge
    StockEdge* stock_edge_imp = static_cast<StockEdge*>(stock_edge);
    stock_edge_imp->RemoveEdge();
    m_stock_edge_interface_vec.erase(std::remove
                                          (
                                            m_stock_edge_interface_vec.begin(),
                                            m_stock_edge_interface_vec.end(),
                                            stock_edge),
                                      m_stock_edge_interface_vec.end()
                                     );

}

std::vector<StockNodeInterface *> StockScene::GetStockNodesVector()
{
    return m_stock_node_interface_vec;
}

std::vector<StockEdgeInterface *> StockScene::GetStockEdgesVector()
{
    return m_stock_edge_interface_vec;
}

QGraphicsScene* StockScene::GetGraphicsScenePtr()
{
    return m_stock_graphics_scene;
}

