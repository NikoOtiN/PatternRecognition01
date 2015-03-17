#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "area.h"
#include "paramdialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void createArea();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    paramDialog pd;
    Area *area;
public slots:
    void getParam();
    void dialogDone();
};

#endif // MAINWINDOW_H
