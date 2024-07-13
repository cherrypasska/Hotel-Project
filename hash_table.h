#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <QString>
#include <QTableWidget>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <cstdio>
#include "linked_list.h"

class hash_table {
private:
    struct key {
        QString passport;
        QString fio;
        int year;
        QString address;
        QString purpose;
        bool in;
        key* next;
        key(QString pa, QString f, int y, QString a, QString pu){
            passport = pa;
            fio = f;
            year = y;
            address = a;
            purpose = pu;
            in = false;
        }
    };
public:
    key* h_table[1500] = { nullptr };
    hash_table();
    int hash_func(const QString&);
    void count_kol(key**, int*);
    QString key_gen();
    void add_el(key**, QString, QString, int, QString, QString);
    bool is_empty();
    void del_file(QString, linked_list*);
    void del_el(key**, QString, linked_list*);
    void del_hash_table(linked_list*);
    void print_hash(QTableWidget*, linked_list*);
    void find_passport(QString, QTableWidget*, bool&);
    void find_fio(QString, QTableWidget*);
    void write_to_file(key*);
    void print();
};
#endif // HASH_TABLE_H
