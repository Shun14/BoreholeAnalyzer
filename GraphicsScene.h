#pragma once

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>

#include <QGraphicsSceneMouseEvent>
#include "GraphicsTextItem.h"


class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene(QObject *parent = Q_NULLPTR);
    ~GraphicsScene();

    enum Mode {Normal, MoveItem, InsertSlitWidth, InsertRectangle, InsertAnyShape, InsertOccurance, InsertTextBox, InsertCross};

    void initItem();
    void setCurMode(Mode mode);
    Mode getCurMode() {return curMode;}

public slots:
    void updatePixmap(QPixmap pixmap);
    void clearPixmap();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    Mode curMode;

    QGraphicsPixmapItem *pixmapItem;
    QGraphicsItem *item;
    QGraphicsItem *createNewItem(QGraphicsSceneMouseEvent *mouseEvent);

signals:
    void modeChanged(GraphicsScene::Mode lastMode, GraphicsScene::Mode curMode);
    void itemInserted(QGraphicsItem* const &insertedItem);
    void itemDeleted(QGraphicsItem* const &deletedItem);

};
