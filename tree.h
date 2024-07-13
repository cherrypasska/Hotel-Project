#ifndef TREE_H
#define TREE_H

#include "algorithm"
#include <QDebug>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <cstdio>
#include "linked_list.h"

class Tree {
private:
    struct tree {
        QString h_room;
        int num_beds;
        int num_rooms;
        bool toilet;
        QString equipment;
        int height;
        tree* left;
        tree* right;
        tree(QString h_r, int n_b, int n_r, bool t, QString e) {
            h_room = h_r;
            num_beds = n_b;
            num_rooms = n_r;
            toilet = t;
            equipment = e;
            height = 1;
            left = right = nullptr;
        }
    };
public:

    tree* root;
    int free_beds[5000];
    Tree();
    int get_height(tree*);
    void update_hight(tree*);
    tree* left_rotate(tree*);
    tree* right_rotate(tree*);
    void big_left_rotate(tree*&);
    void big_right_rotate(tree*&);
    tree* get_max(tree*);
    void balance(tree*&);
    void add_el(tree*&, QString, int, int, bool, QString);
    void del_el(tree*&, QString);
    void del_tree(tree*&);
    void show_tree(tree*, linked_list*, QTableWidget*);
    void print(tree*, int);
    void new_string(QString&);
    bool word_in_string(QString, QString);
    void find_room(tree*, QString, QTableWidget*, bool&);
    void find_eq(tree*, QString, QTableWidget*, linked_list*);
    //void preorder(tree*); //прямой обход дерева
    void write_to_file(tree*);
    void del_file(QString);
    ~Tree(){
        delete root;
    }

};

#endif // TREE_H
