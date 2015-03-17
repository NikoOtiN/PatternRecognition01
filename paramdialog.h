#ifndef PARAMDIALOG_H
#define PARAMDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QSpinBox>

struct res {
    int a;
    int l;
};

class paramDialog : public QDialog
{
    Q_OBJECT
private:
    QPushButton *ok, *cancel;
    QLabel *amplitude, *length;
    QSpinBox *amp, *len;
public:
    paramDialog(QWidget *parent = 0);
    res getData();
    ~paramDialog();
};

#endif // PARAMDIALOG_H
