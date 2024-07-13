#ifndef WIDGET_H
#define WIDGET_H

#include <ui_widget.h>>
#include "human.h"
#include "room.h"
#include "hash_table.h"
#include "tree.h"
#include "linked_list.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
};

#endif // Widget_H
