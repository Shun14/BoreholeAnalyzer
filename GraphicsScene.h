#pragma once

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QVector>

#include "DbHandler.h"
#include "GraphicsSettings.h"
#include "GraphicsTextItem.h"
#include "GraphicsLineItem.h"
#include "GraphicsAngleItem.h"
#include "GraphicsRectItem.h"
#include "GraphicsAnyshape.h"
#include "GraphicsOccurance.h"


#define Border          100
#define Interval        10
#define Segment         25

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene(QObject *parent = Q_NULLPTR);
    ~GraphicsScene();

    enum Mode {MoveItem, InsertLine, InsertRuler, InsertShift, InsertRectangle, InsertAnyShape, InsertOccurance, InsertTextBox, InsertCross};

    void setCurMode(Mode mode);


    static Mode getCurMode() {return curMode;}
    static double getRatio() {return ratio;}

    void itemFinished(QString content);


public slots:
    void clearScene();
    void updatePixmap(QPixmap pixmap, qreal start, qreal end);

    void saveLastItem();
    void deleteLastItem();

    void getSavedItem(QVector<QGraphicsItem *>items);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void drawBackground(QPainter * painter, const QRectF & rect);

private:
    static Mode curMode;
    static qreal ratio;

    QRectF pixmapRect;
    qreal pixmap_start, pixmap_end;

    QGraphicsItem *item;

    bool hasSaved, showInfo;

signals:
    void modeChanged(GraphicsScene::Mode curMode); 
    void showStatus(QString message, int timeout);

    void showRealInfo(QString info);

    void itemSaved(QGraphicsItem *item);


};
