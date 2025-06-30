#include "realmain.h"
#include "ui_sub1.h"

sub1::sub1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sub1)
{
    ui->setupUi(this);
}

sub1::~sub1()
{
    delete ui;
}
