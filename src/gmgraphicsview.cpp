#include <iostream>
#include <QMenu>
#include <QApplication>
#include "gmgraphicsview.h"
#include "gmsocket.h"
#include "gmedge.h"

int MODE_NO_OPERATION = 1;
int MODE_EDGE_DRAG = 2;
int MODE_CUTTING_LINE = 3;

GMGraphicsView::GMGraphicsView(QWidget *parent): QGraphicsView(parent){
    m_remove_action = new QAction("delete item",this);
    connect(m_remove_action, SIGNAL(triggered()),this, SLOT(RemoveSelectedItems()));
    m_mode = MODE_NO_OPERATION;

    // enable dropping
    this->setAcceptDrops(true);

}

GMGraphicsView::~GMGraphicsView(){}


void GMGraphicsView::SetStockGraphicScene(GMQtGraphicScene *stock_graphics_scene)
{
    m_stock_graphics_scene = stock_graphics_scene;
}

void GMGraphicsView::SetGMQtGraphicsCuttingLine(GMQtGraphicsCuttingLine *stock_graphics_cutting_line)
{
    this->m_stock_graphics_cutting_line = stock_graphics_cutting_line;
}

void GMGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsItem* item =this->itemAt(event->pos());

    if(event->button() == Qt::LeftButton && m_mode == MODE_NO_OPERATION)
    {
        if(GMQtGraphicSocket* v=dynamic_cast<GMQtGraphicSocket*>(item))
        {
               this->m_mode = MODE_EDGE_DRAG;
               std::cout<<"start dragging edge"<<std::endl;
               if(GMQtGraphicSocket* v=dynamic_cast<GMQtGraphicSocket*>(item))
               {
                   std::cout<<"assign start socket"<<std::endl;
                   GMScene* stock_scene = m_stock_graphics_scene->GetGMScene();
                   m_drag_stock_edge_start = v->GetStockSocketInterface();

                   QPointF start = m_drag_stock_edge_start->GetSocketPosition();
                   QPointF end = mapToScene(event->pos());
                   this->m_drag_stock_edge_interface = new GMEdge(stock_scene,start,end);
                   return;
               }
        }
    }

    if(event->button() == Qt::LeftButton && m_mode == MODE_NO_OPERATION)
    {
        if (item == nullptr && event->modifiers() & Qt::ShiftModifier)
        {
            this->m_mode = MODE_CUTTING_LINE;
            QMouseEvent* fake_event = new QMouseEvent(QEvent::MouseButtonRelease,event->localPos(),
                                                 event->screenPos(), Qt::LeftButton, Qt::NoButton,
                                                 event->modifiers());
            QGraphicsView::mouseReleaseEvent(fake_event);

            QApplication::setOverrideCursor(Qt::CrossCursor);
            return;
        }
    }


    QGraphicsView::mousePressEvent(event);
}


void GMGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
     if(this->m_mode == MODE_CUTTING_LINE)
     {
         QPointF pos = mapToScene(event->pos());
         m_stock_graphics_cutting_line->AppendQPoint(pos.toPoint());
         m_stock_graphics_cutting_line->update();
     }

     if(this->m_mode == MODE_EDGE_DRAG)
     {
         GMEdge* stock_edge = static_cast<GMEdge*>(this->m_drag_stock_edge_interface);
         if(stock_edge!=nullptr)
         {
             stock_edge->SetTarget(mapToScene(event->pos()));
         }
     }
     QGraphicsView::mouseMoveEvent(event);

}


void GMGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsItem* item =this->itemAt(event->pos());

    if(event->button() == Qt::LeftButton && this->m_mode == MODE_CUTTING_LINE && event->modifiers() & Qt::ShiftModifier)
    {
        m_mode = MODE_NO_OPERATION;
        // remove all the cutting line
        std::vector<StockEdgeInterface*> edge_container = this->m_stock_graphics_scene->GetGMScene()->GetStockEdgesVector();
        QVector<QPoint> point_container = m_stock_graphics_cutting_line->getQpoints();
        //for(QPoint* start = point_container.begin(); start!=point_container.end()-2;)
        //{
            QPoint p1 = point_container[1];
            QPoint p2 = *point_container.rbegin();
            for(auto i:edge_container)
            {
                GMEdge* stock_edge = static_cast<GMEdge*>(i);
                GMQtGraphicsEdge* gmqt_graphics_edge = stock_edge->GetGMQtGraphicsEdge();

                if(gmqt_graphics_edge->isIntersectsWith(p1, p2))
                {
                    stock_edge->RemoveEdge();
                }
            }
        //}

        m_stock_graphics_cutting_line->ClearPoint();
        m_stock_graphics_cutting_line->update();
        QApplication::setOverrideCursor(Qt::ArrowCursor);
    }

    if(event->button() == Qt::LeftButton && this->m_mode == MODE_EDGE_DRAG)
    { 
        this->m_mode = MODE_NO_OPERATION;
        std::cout<<"end dragging edge"<<std::endl;
        GMEdge* stock_edge = static_cast<GMEdge*>(this->m_drag_stock_edge_interface);
        stock_edge->RemoveEdge();
        if(GMQtGraphicSocket* v=dynamic_cast<GMQtGraphicSocket*>(item))
        {
             //StockEdge* stock_edge = static_cast<StockEdge*>(m_drag_stock_edge_interface);
             GMScene* stock_scene = m_stock_graphics_scene->GetGMScene();
             m_drag_stock_edge_end =  v->GetStockSocketInterface();
             new GMEdge(stock_scene, m_drag_stock_edge_start,m_drag_stock_edge_end);
             stock_scene->RemoveEdge(m_drag_stock_edge_interface);
             std::cout<<"assign end socket"<<std::endl;
         }
         return;
    }

    QGraphicsView::mouseReleaseEvent(event);
}


void GMGraphicsView::RemoveSelectedItems()
{
    QList<QGraphicsItem*> items_selected = m_stock_graphics_scene->selectedItems();
    QList<QGraphicsItem*> items = m_stock_graphics_scene->items();
    std::cout<<"items selected size: "<<items_selected.size()<<std::endl;
    std::cout<<"items size: "<<items.size()<<std::endl;
}

void GMGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(m_remove_action);
    menu.exec(event->globalPos());
}

void GMGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    std::cout<<"drag enter"<<std::endl;
    GMNode* gm_node = new GMNode(m_stock_graphics_scene->GetGMScene());
    gm_node->SetStockNodePosition(event->pos());
}
