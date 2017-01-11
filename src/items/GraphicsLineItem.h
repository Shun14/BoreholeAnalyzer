#pragma once

#include <QGraphicsLineItem>
#include <QPainter>
#include <QDebug>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QtMath>

#include "GraphicsScene.h"
#include "GraphicsSettings.h"

#include "type.h"

class GraphicsLineItem : public QGraphicsLineItem
{
public:
    GraphicsLineItem(const QLineF & line, QGraphicsItem *parent = Q_NULLPTR);
    ~GraphicsLineItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    QPainterPath shape() const;
    static QPainterPath shapeFromPath(const QPainterPath&,const QPen&);


    int type() const
    {
        return Ruler;
    }

    QString getDataString();
    static GraphicsLineItem *loadFromString(QString data);

    void setFinished() {hasDrawed = true;}


    QString getRemark() {return remarkContent;}
    void setRemark(QString remark) {remarkContent = remark;}


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverLeaveEvent( QGraphicsSceneHoverEvent * event );
    bool sceneEvent(QEvent *event);

private:
    bool hasDrawed;
    QString remarkContent;
};
