#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H


#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>
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
#include <vector>
#include "gmsocketinterface.h"
#include "gmnode.h"
#include "gmscene.h"


class GMQtGraphicScene: public QGraphicsScene
{
public:
    GMQtGraphicScene(GMScene* gm_scene);

public:
    GMScene* GetGMScene();

protected:
    //void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    GMScene* m_gm_scene;
};

#endif // GRAPHICSSCENE_H
