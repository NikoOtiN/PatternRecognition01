#include "sunitem.h"
#include <QDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>

SunItem::SunItem(QMap<QString,QPainterPath*> m) : mirrors(m)
{
    w = 50;
    h = 50;
    QPainterPath sunPath;
    sunPath.addEllipse(-w/2,-h/2,w,h);
    sunPath.addRect(-w/2,-h/2,w,h);
    setPath(sunPath);

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setPos(50,50);

}

void SunItem::calculate()
{
    QMapIterator<QString, QPainterPath *> j(mirrors);
    QPolygonF polygon = scene()->sceneRect();
    QPainterPath iPath = mapToScene(path());
    QPainterPath sPath;
    sPath.addPolygon(polygon);
    if(sPath.contains(iPath)||sPath.intersects(iPath))
    {}else{
        while (j.hasNext()) {
                j.next();
                scene()->setSelectionArea(*j.value());
                QList<QGraphicsItem *> tmp = scene()->items(*j.value());
                if(!tmp.isEmpty())
                {
                    qDebug() << j.key();
                    QRectF intRect = j.value()->boundingRect();
                    qDebug() << intRect.x() << intRect.y();
                    setPos(scenePos().x()-intRect.x(),scenePos().y()-intRect.y());

                    for(int k = 0; k < childs.size(); k++)
                    {
                        if(childs.at(k)->data(1).toString()==j.key())
                        {
                            scene()->removeItem(childs.at(k));
                            childs.remove(k);
                        }
                    }
                }
        }
    }


    QMapIterator<QString, QPainterPath *> i(mirrors);
    while (i.hasNext()) {
            i.next();
            scene()->setSelectionArea(*i.value());
            QList<QGraphicsItem *> tmp = scene()->items(*i.value());
                if(!tmp.isEmpty())
                {
                    QRectF intRect = i.value()->boundingRect();
                    QPolygonF sceneRect = scene()->sceneRect();
                    QPointF p = scenePos();
                    QPainterPath sunPath = mapToScene(path());

                    QPainterPath sumPath, result, sc;
                    sc.addPolygon(sceneRect);
                    sumPath.addRect(intRect);
                    result = sumPath.subtracted(sc);

                    for(int j = 0; j < childs.size(); j++)
                    {
                        if(childs.at(j)->data(1).toString()==i.key())
                        {
                            scene()->removeItem(childs.at(j));
                            childs.remove(j);
                        }
                    }

                    QGraphicsPathItem *child = new PathItem(sumPath.intersected(sunPath), scale());
                    child->setData(1,QVariant(i.key()));
                    childs.push_front(child);
                    scene()->addItem(child);

                        child->setPos(-intRect.x(),-intRect.y());
                }else{
                    for(int j = 0; j < childs.size(); j++)
                    {
                        if(childs.at(j)->data(1).toString()==i.key())
                        {
                            scene()->removeItem(childs.at(j));
                            childs.remove(j);
                        }
                    }
                }
        }
}

SunItem::~SunItem()
{

}

