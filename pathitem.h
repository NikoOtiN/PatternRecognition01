#ifndef PATHITEM_H
#define PATHITEM_H
#include <QGraphicsItem>

class PathItem : public QGraphicsPathItem
{
public:
    PathItem(QPainterPath p, qreal w);
    ~PathItem();
    qreal width;
    //QRectF boundingRect() const Q_DECL_OVERRIDE;
    //QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    //QRectF boundingRect() const Q_DECL_OVERRIDE;
private:
    //QPainterPath path;
};

#endif // PATHITEM_H
