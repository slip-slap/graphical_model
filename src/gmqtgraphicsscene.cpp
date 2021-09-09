#include "gmqtgraphicsscene.h"
#include "gmnode.h"
#include <iostream>
#include <QMenu>
#include <QPen>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsEllipseItem>
#include "gmqtgraphicssocket.h"



GMQtGraphicScene::GMQtGraphicScene(GMScene *gm_scene)
{
    m_gm_scene = gm_scene;
}

GMScene *GMQtGraphicScene::GetGMScene()
{
    return m_gm_scene;
}


void GMQtGraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent*event)
{
    QGraphicsScene::mouseMoveEvent(event);

}
