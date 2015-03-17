#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //showMaximized();
}

void MainWindow::createArea()
{
    int w = 300*2;
    int h = 200*2;
    QRectF rect = geometry();
    resize(w,h);
    area = new Area(w-8,h-22);
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCentralWidget(area);

    //setFixedSize(rect.x(),rect.y());
    QAction *handle = new QAction("С помощью клавиш без повторения",this);
    QAction *rep = new QAction("С помощью клавиш с повторением",this);
    QAction *sin = new QAction("По синусоиде",this);
    QMenu *moveMenu = menuBar()->addMenu(tr("Способ движения"));
    moveMenu->addAction(handle);
    moveMenu->addAction(rep);
    moveMenu->addAction(sin);

    QAction *speedUp = new QAction("Больше",this);
    QAction *speedDown = new QAction("Меньше", this);
    QMenu *speedMenu = menuBar()->addMenu(tr("Скорость"));
    speedMenu->addAction(speedUp);
    speedMenu->addAction(speedDown);
    QAction *scopeUp = new QAction("Больше",this);
    QAction *scopeDown = new QAction("Меньше", this);
    QMenu *scopeMenu = menuBar()->addMenu(tr("Масштаб"));
    scopeMenu->addAction(scopeUp);
    scopeMenu->addAction(scopeDown);

    connect(sin,SIGNAL(triggered()),this,SLOT(getParam()));
    connect(&pd,SIGNAL(accepted()),this,SLOT(dialogDone()));
    connect(scopeUp,SIGNAL(triggered()),area,SLOT(zoomUp()));
    connect(scopeDown,SIGNAL(triggered()),area,SLOT(zoomDown()));
    connect(speedUp,SIGNAL(triggered()),area,SLOT(stepUp()));
    connect(speedDown,SIGNAL(triggered()),area,SLOT(stepDown()));
    connect(handle,SIGNAL(triggered()),area,SLOT(modeNone()));
    connect(rep,SIGNAL(triggered()),area,SLOT(modeReapeted()));

}

void MainWindow::getParam()
{
    pd.show();
}

void MainWindow::dialogDone()
{
    res r = pd.getData();
    area->setParams(r.a,r.l);
    emit area->modeSin();
}

MainWindow::~MainWindow()
{
    delete ui;
}
