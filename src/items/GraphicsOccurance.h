#pragma once

#include <QGraphicsLineItem>

#include "GraphicsSettings.h"
#include "GraphicsScene.h"

class GraphicsOccurance : public QGraphicsLineItem
{
public:
    GraphicsOccurance(const QLineF &line, QGraphicsItem *parent = Q_NULLPTR);
    ~GraphicsOccurance();


    int type() const
    {
        return Occurance;
    }

    QString getDataString();
    static GraphicsOccurance *loadFromString(QString data);

    void setFinished() {hasDrawed = true;}

    QString getRemark() {return remarkContent;}
    void setRemark(QString remark) {remarkContent = remark;}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    bool hasDrawed;
    QString remarkContent;
};
