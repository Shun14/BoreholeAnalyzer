#include "GraphicsAnyshape.h"

GraphicsAnyshape::GraphicsAnyshape(QPointF pos, QGraphicsItem *parent) :
    QGraphicsPolygonItem(parent),
    hasDrawed(false)
{
    addPoint(pos);
    setPen(QPen(GraphicsSettings::instance()->getPenColor(), GraphicsSettings::instance()->getPenWidth()));
}

GraphicsAnyshape::~GraphicsAnyshape()
{

}

void GraphicsAnyshape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = Q_NULLPTR;
    widget = Q_NULLPTR;
    painter->setRenderHint(QPainter::Antialiasing);

    QPen thisPen;
    thisPen.setColor(Qt::yellow);
    thisPen.setWidth(pen().width());
    thisPen.setStyle(Qt::SolidLine);
    painter->setPen(thisPen);

    painter->drawPolygon(this->polygon());

}



void GraphicsAnyshape::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (hasDrawed)
        return;

    if (event->buttons() & Qt::RightButton)
    {
        hasDrawed = true;
        GraphicsScene *scene = dynamic_cast<GraphicsScene *>(this->scene());
        scene->itemInserted();

        if (polygon().count() <= 2)
            return;

        QGraphicsSimpleTextItem *textItem = this->scene()->addSimpleText(QString::number(calcArea()/qPow(GraphicsScene::getRatio(), 2), 'f', 2).append("cm2"), QFont("Times", 40, QFont::Bold));
        textItem->setParentItem(this);


        textItem->setPos(polygon().last().x()+20, polygon().last().y()+20);

        return;
    }

    addPoint(event->scenePos());
}


void GraphicsAnyshape::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (hasDrawed)
        return;

    updatePoint(event->scenePos());
}


void GraphicsAnyshape::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (hasDrawed)
        return;
}



qreal GraphicsAnyshape::calcArea()
{
    qreal area = 0.0;
    qreal x1, y1, x2, y2;

    QPolygonF polygon = this->polygon();
    polygon.append(polygon.first());
    int count = polygon.count();

    qDebug() << count;
    for (int i = 0; i < count; i++)
        qDebug() << polygon.at(i);

    for (int i = 0; i < count - 1; i++)
    {
        x1 = polygon.at(i).x();
        y1 = polygon.at(i).y();
        x2 = polygon.at(i+1).x();
        y2 = polygon.at(i+1).y();
        area += qFabs(x1 * y2 - x2 * y1);
    }

    area /= 2;
    area *= 10000;

    return area;
}


void GraphicsAnyshape::addPoint(QPointF pos)
{
    QPolygonF polygon = this->polygon();
    polygon.append(pos);
    setPolygon(polygon);
}

void GraphicsAnyshape::updatePoint(QPointF pos)
{
    QPolygonF polygon = this->polygon();
    polygon.removeLast();
    polygon.append(pos);
    setPolygon(polygon);
}

void GraphicsAnyshape::clearPoints()
{
    QPolygonF polygon;
    polygon.clear();
    setPolygon(polygon);
}


GraphicsAnyshape::Data GraphicsAnyshape::getData()
{
    Data data = {this->polygon()};
    return data;
}
