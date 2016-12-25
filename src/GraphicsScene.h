#pragma once

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <QUuid>
#include <qmath.h>

#include "GraphicsSettings.h"


#include "GraphicsSettings.h"
#include "GraphicsTextItem.h"
#include "GraphicsLineItem.h"
#include "GraphicsAngleItem.h"
#include "GraphicsRectItem.h"
#include "GraphicsAnyshape.h"
#include "GraphicsOccurance.h"

#include "type.h"

#include <QMap>


#define Border          150
#define Interval        30
#define Segment         30

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene(QObject *parent = Q_NULLPTR);
    ~GraphicsScene();


    typedef struct
    {
        QUuid uuid;
        QGraphicsItem *item;
    }ItemData;

    typedef struct
    {
        QString type;
        QString isSaved;
        QString data;
    }TableData;


    enum Mode {MoveItem, InsertLine, InsertRuler, InsertShift, InsertRectangle, InsertAnyShape, InsertOccurance, InsertTextBox, InsertCross};

    void setCurMode(Mode mode);
    static Mode getCurMode();


    void itemFinished(QString content);

    QImage getSceneImage();
    QImage getSceneImageFor3D();

    static QImage getImageFromData(QPixmap pixmap, qreal start, qreal end, QMap<QString, QGraphicsItem *> items);


    QPointF scene2Real(QPointF scenePos);
    QPointF real2Scene(QPointF realPos);


    bool hasNewItem();
    QMap<QString, QGraphicsItem *> getNewItems();
    void saveNewItems();

public slots:
    void clearScene();
    void updateIndexData(QPixmap pixmap, qreal start, qreal end, QMap<QString, QGraphicsItem *> items);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void drawBackground(QPainter * painter, const QRectF & rect);

private:
    bool showInfo;
    qreal pixmap_start, pixmap_end;
    qreal pixmap_width, pixmap_height;

    QGraphicsItem *item;


    static Mode curMode;

    QString getShowString(QGraphicsItem *item);
    QString getAngleString(qreal angle);


    QMap<QString, QGraphicsItem *> newItems, savedItems;
    void addItemData(QUuid uuid, QGraphicsItem *item, bool saved = false);
    void deleteItemData(QUuid uuid);
    void clearItemData();

    void updateTable();

signals:
    void modeChanged(GraphicsScene::Mode curMode);
    void showStatus(QString message);
    void showRealInfo(QString info);

    void emitTableData(QVector<GraphicsScene::TableData> tableData);
};
