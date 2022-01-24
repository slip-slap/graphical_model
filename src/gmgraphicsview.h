#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QEvent>
#include <QFocusEvent>
#include <QInputMethodEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include "gmqtgraphicsscene.h"
#include "gmqtgraphicscuttingline.h"
#include "gmsocketinterface.h"

class GMGraphicsView : public QGraphicsView
{

    Q_OBJECT

public:
    GMGraphicsView(QWidget *parent=nullptr);
    GMGraphicsView(QGraphicsScene* scene, QWidget* parent=nullptr);
    ~GMGraphicsView();

public:
    void SetStockGraphicScene(GMQtGraphicScene* stock_graphics_scene);
    void SetGMQtGraphicsCuttingLine(GMQtGraphicsCuttingLine* stock_graphics_cutting_line);

public slots:
    void RemoveSelectedItems();


private:
    QAction* m_remove_action;

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
   // void dragLeaveEvent(QDragLeaveEvent *event) override;
   // void dragMoveEvent(QDragMoveEvent *event) override;
private:
    int m_mode=1;
    GMQtGraphicScene* m_stock_graphics_scene;  
    GMQtGraphicsCuttingLine* m_stock_graphics_cutting_line;

    StockEdgeInterface* m_drag_stock_edge_interface;
    GMSocketInterface* m_drag_stock_edge_start;
    GMSocketInterface* m_drag_stock_edge_end;

};

#endif // GRAPHICSVIEW_H
