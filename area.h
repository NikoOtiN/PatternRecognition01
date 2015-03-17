#ifndef AREA_H
#define AREA_H
#include <QGraphicsView>
#include <QDebug>
#include <sunitem.h>
struct point {
    point()
    {
        x=0;
        y=0;
    }

    int x;
    int y;
};

class Area : public QGraphicsView
{
    Q_OBJECT

    enum MoveMode { NONE, REAPETED, SIN };

public:
    Area(int w = 500, int h = 500, QWidget *parent = 0);
    ~Area();
    void zoomIn();
    void zoomOut();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void setParams(int a, int l);
private:
    point handleKey(int i);

    SunItem *centerItem;
    QMap<QString,QPainterPath*> m;
    QVector<int> keyPressed;
    int itemStep;
    point direction;
    int timer;
    int startX;
    int startY;
    MoveMode mode;
    int amplitude;
    qreal length;
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void timerEvent(QTimerEvent *);
public slots:
    void zoomUp();
    void zoomDown();
    void stepUp();
    void stepDown();
    void modeReapeted();
    void modeNone();
    void modeSin();
};

#endif // AREA_H
