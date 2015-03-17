#include "paramdialog.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
paramDialog::paramDialog(QWidget *parent) : QDialog(parent)
{
    QGridLayout *grid = new QGridLayout();
    amplitude = new QLabel("Амплитуда");
    length = new QLabel("Длина полного колебания");
    grid->addWidget(amplitude,0,0);
    grid->addWidget(length,1,0);
    ok = new QPushButton("Ok");
    cancel = new QPushButton("Cancel");
    connect(ok,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));

    amp = new QSpinBox();

    len = new QSpinBox();

    grid->addWidget(amp,0,2);
    grid->addWidget(len,1,2);
    grid->addWidget(ok,3,1);
    grid->addWidget(cancel,3,2);
    setLayout(grid);
}

res paramDialog::getData()
{
    res result;
    result.a = amp->value();
    result.l = len->value();
    return result;
}

paramDialog::~paramDialog()
{

}

