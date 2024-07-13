#include "widget.h"
#include "ui_widget.h"
#include "room.h"
#include "hst.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    human* h = new human();
    h->setWindowTitle("Регистрация постояльцев в номерах");
    h->show();
    this->close();
}

void Widget::on_pushButton_2_clicked()
{
    room* r = new room();
    r->setWindowTitle("Регистрация номеров");
    r->show();
    this->close();
}


void Widget::on_pushButton_3_clicked()
{
    hst* k = new hst();
    k->setWindowTitle("История");
    k->show();
    this->close();
}

