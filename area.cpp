#include "area.h"
#include <QGraphicsItem>
#include <QEvent>
#include <QKeyEvent>
#include <QtMath>

Area::Area(int w, int h, QWidget *parent) : QGraphicsView(parent), itemStep(2), timer(0), amplitude(0), length(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, w, h);
    setScene(scene);


    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);

    int l = 1;
    QPainterPath *topLeft = new QPainterPath();
    topLeft->addRect(-w-l,-h-l,w,h);

    QPainterPath *top = new QPainterPath();
    top->addRect(0-l,-h-l,w,h);

    QPainterPath *middleRight = new QPainterPath();
    middleRight->addRect(w+l,0+l,w,h);

    QPainterPath *middleLeft = new QPainterPath();
    middleLeft->addRect(-w-l,0-l,w,h);

    QPainterPath *down = new QPainterPath();
    down->addRect(0+l,h+l,w,h);
    QPainterPath *downRight = new QPainterPath();
    downRight->addRect(w+l,h+l,w,h);
    QPainterPath *downLeft = new QPainterPath();
    downLeft->addRect(-w-l,h+l,w,h);

    QPainterPath *topRight = new QPainterPath();
    topRight->addRect(w+l,-h-l,w,h);

    QMap<QString,QPainterPath*> m;

    m["topLeft"] = topLeft;
    m["top"] = top;
    m["middleRight"] = middleRight;
    m["middleLeft"] = middleLeft;
    m["down"] = down;
    m["downRight"] = downRight;
    m["downLeft"] = downLeft;
    m["topRight"] = topRight;
    centerItem = new SunItem(m);
    centerItem->setFlag(QGraphicsItem::ItemIsMovable);
    centerItem->setPos(100,100);

    scene->addItem(centerItem);

}

Area::~Area()
{

}

void Area::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    QRectF sceneRect = this->sceneRect();
    QPen pen;
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawRect(sceneRect);
}

void Area::keyPressEvent(QKeyEvent *event)
{
    point p1 = handleKey(event->key());
    if(keyPressed.size())
    {
        point p2 = handleKey(keyPressed.last());
        p1.x += p2.x;
        p1.y += p2.y;
    }
    if(p1.x!=0||p1.y!=0)
    {
        if(mode==NONE)
        {
            centerItem->moveBy(p1.x,p1.y);
        }else{
            direction = p1;
        }
    }

    centerItem->calculate();
    if(!keyPressed.contains(event->key()))
    {
        keyPressed.push_back(event->key());
    }
}


point Area::handleKey(int i)
{
    point p;
    int step = itemStep;
    switch (i) {
    case Qt::Key_Up:
        p.y=-step;
        break;
    case Qt::Key_Down:
        p.y=step;
        break;
    case Qt::Key_Left:
        p.x=-step;
        break;
    case Qt::Key_Right:
        p.x=step;
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    {
        qDebug() << width() << height();
        scale(width()/500.0,height()/500.0);
        break;
    }
    case Qt::Key_Enter:
        break;
    }
    return p;
}

void Area::keyReleaseEvent(QKeyEvent *event)
{
    keyPressed.removeAll(event->key());
}

void Area::zoomIn()
{
    centerItem->setScale(centerItem->scale()*1.05);
}

void Area::zoomOut()
{
        centerItem->setScale(centerItem->scale()/1.05);
}

void Area::zoomUp()
{
    zoomIn();
}

void Area::zoomDown()
{
    zoomOut();
}

void Area::stepUp()
{
    direction.x*=2;
    direction.y*=2;
    itemStep*=2;
}

void Area::stepDown()
{
    direction.x/=2;
    direction.y/=2;
    itemStep/=2;
}

void Area::modeNone()
{
    if(timer)
    {
        killTimer(timer);
        timer = 0;
    }
    mode = NONE;
}

void Area::modeSin()
{
    QPointF  p = centerItem->scenePos();
    startX = p.x();
    startY = p.y();
    if(!timer)
    {
        timer = startTimer(1000/33);
    }
    mode = SIN;
}

void Area::modeReapeted()
{
    if(!timer)
    {
        timer = startTimer(1000/33);
    }
    mode = REAPETED;
}

void Area::timerEvent(QTimerEvent *)
{
    switch(mode)
    {
    case REAPETED:
    {
        centerItem->moveBy(direction.x,direction.y);
        break;
    }
    case SIN:
    {
       QPointF  p = centerItem->pos();
              startX+=1;
              qDebug() << qSin(startX/length);
              centerItem->moveBy(1, amplitude*qSin(startX/length));
              break;
    }
    }
    centerItem->calculate();
}

void Area::setParams(int a, int l)
{
        amplitude = a;
        length = l;
}
