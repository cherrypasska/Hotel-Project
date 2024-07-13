#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <qDebug>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>

class linked_list {
private:
    struct node {
        QString passport;
        QString h_room;
        QString check_in_date;
        QString eviction_date;
        node* next;
        node* prev;
        node(QString pas, QString h_r, QString c_date, QString e_date) {
            passport = pas;
            h_room = h_r;
            check_in_date = c_date;
            eviction_date = e_date;
        }
    };
    int size;
    node* head, *tail;

public:

    linked_list();
    void push_front(QString, QString, QString, QString);
    void push_back(QString, QString, QString, QString);
    void pop_front();
    void pop_back();
    void pop_el(QString);
    void swap(node*, node*);
    void counting_sort();
    void clear();
    void del_file(QString);
    bool is_empty();
    QString find_passport(QString);
    QString find_room(QString);
    void write_to_file(QString, QString, QString, QString);
    void print();
    ~linked_list();

};

#endif // LINKED_LIST_H
