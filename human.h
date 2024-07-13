#ifndef HUMAN_H
#define HUMAN_H

#include "hash_table.h"
#include "linked_list.h"
#include "tree.h"
#include <QWidget>


namespace Ui {
class human;
}

class human : public QWidget
{
    Q_OBJECT

public:
    explicit human(QWidget *parent = nullptr);
    ~human();

private slots:
    void check_but();
    void clean_table();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_3_textChanged(const QString &arg1);
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_dateEdit_userDateChanged(const QDate &date);
    void on_dateEdit_2_userDateChanged(const QDate &date);
    void on_pushButton_9_clicked();
    void on_lineEdit_4_textChanged(const QString &arg1);
    void on_lineEdit_5_textChanged(const QString &arg1);
    void on_lineEdit_6_textChanged(const QString &arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);
private:
    Ui::human *ui;
    hash_table *table;
    Tree* tree;
    linked_list* list;
    QString c_date;
    QString e_date;

};

#endif // HUMAN_H
