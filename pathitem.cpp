#include "pathitem.h"
#include <QPainter>
#include <QDebug>
PathItem::PathItem(QPainterPath p, qreal w) : QGraphicsPathItem(p)
{
    width = w;
}

PathItem::~PathItem()
{

}

void PathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QPen pen;
    pen.setWidthF(width);
    painter->setPen(pen);
    //path()
    painter->drawPath(path());
}
