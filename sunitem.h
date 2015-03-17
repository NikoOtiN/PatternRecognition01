#ifndef SUNITEM_H
#define SUNITEM_H

#include <QGraphicsPathItem>
#include <QGraphicsScene>
#include <QPainterPath>
#include <QPainter>
#include <QVector>
#include "pathitem.h"
class SunItem : public QGraphicsPathItem
{
public:
    enum MoveMode { Left, Right, Top, Bottom, Sin, Stop };
    SunItem(QMap<QString, QPainterPath *> m);

    void calculate();
    ~SunItem();
private:
    QMap<QString,QPainterPath*> mirrors;
    QVector<QGraphicsPathItem*> childs;
    int w;
    int h;

    //QPainterPath copyPath;
protected:
};

#endif // SUNITEM_H
