#ifndef ROOM_H
#define ROOM_H

#include <QWidget>
#include "widget.h"
#include "tree.h"
#include "linked_list.h"
#include <QDebug>


namespace Ui {
class room;
}

class room : public QWidget
{
    Q_OBJECT

public:
    explicit room(QWidget *parent = 0);
    ~room();

private slots:

    void check_but();
    void clean_table();
    void check_eq(QString&);
    void new_string(QString&);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_radioButton_clicked(bool checked);
    void on_radioButton_2_clicked(bool checked);
    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_lineEdit_3_textChanged(const QString &arg1);
    void on_pushButton_7_clicked();

private:
    Ui::room *ui;
    Tree* tree;
    linked_list* list;
    bool flag;
};

#endif // ROOM_H
