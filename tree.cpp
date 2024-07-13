#include "tree.h"
#include "linked_list.h"
Tree::Tree(){
    root = NULL;
    QString folderPath = "C:\\hot\\hotel\\rooms";
    QDir directory(folderPath);
    if (!directory.exists()) {
        qDebug() << "unable to access the database";
    }
    QStringList files = directory.entryList(QStringList() << "*.txt", QDir::Files);
    foreach (QString filename, files) {
        QString filePath = folderPath + QDir::separator() + filename;
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "can't open the file" << filename;
            continue;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList data = line.split(" ");
            int a = (data[3] == "1");
            add_el(root,data[0],data[1].toInt(),data[2].toInt(),a,data[4]);
            if (data.size() == 6){
                free_beds[data[0].toInt()] = data[5].toInt();
            }
        }
        file.close();
    }

}

int Tree::get_height(tree* p) {
    return p != nullptr ? p->height : 0;
}

void Tree::update_hight(tree* p) {
    p->height = std::max(get_height(p->left), get_height(p->right)) + 1;
}

Tree::tree* Tree::left_rotate(tree* p) {
    tree* q = p->right;
    p->right = q->left;
    q->left = p;
    update_hight(p);
    update_hight(q);
    return q;
}

Tree::tree* Tree::right_rotate(tree* p) {
    tree* q = p->left;
    p->left = q->right;
    q->right = p;
    update_hight(p);
    update_hight(q);
    return q;
}

void Tree::big_left_rotate(tree* &p) {
    p->right = right_rotate(p->right);
    p = left_rotate(p);
}

void Tree::big_right_rotate(tree* &p) {
    p->left = left_rotate(p->left);
    p = right_rotate(p);
}

Tree::tree* Tree::get_max(tree* p) {
    if (p == nullptr) {
        return nullptr;
    }
    if (p->right == nullptr) {
        return p;
    }
    return get_max(p->right);
}

void Tree::balance(tree* &p) {
    while (true) {
        if (get_height(p->right) - get_height(p->left) == 2) {
            if (get_height(p->right->right) - get_height(p->right->left) == 0) {
                p = left_rotate(p);
            }
            else if (get_height(p->right->right) - get_height(p->right->left) == 1) {
                p = left_rotate(p);
            }
            else {
                big_left_rotate(p);
            }
        }
        else if (get_height(p->right) - get_height(p->left) == -2) {
            if (get_height(p->left->right) - get_height(p->left->left) == 0) {
                p = right_rotate(p);
            }
            else if (get_height(p->left->right) - get_height(p->left->left) == -1) {
                p = right_rotate(p);
            }
            else {
                big_right_rotate(p);
            }
        }
        else {
            break;
        }
    }

}

void Tree::add_el(tree* &p, QString h_r, int n_b, int n_r, bool t, QString e) {
    if (p == nullptr) {
        p = new tree(h_r, n_b, n_r, t, e);
    }
    else if (h_r == p->h_room) {
        qDebug() << "the number has already been registered";
        return;
    }
    else if (p->h_room < h_r) {
        add_el(p->right, h_r, n_b, n_r, t, e);
    }
    else {
        add_el(p->left, h_r, n_b, n_r, t, e);
    }
    update_hight(p);
    balance(p);
}

void Tree::del_el(tree* &p, QString h_r) {
    if (p == nullptr) {
        return;
    }
    else if (h_r < p->h_room) {
        del_el(p->left, h_r);
    }
    else if (h_r > p->h_room) {
        del_el(p->right, h_r);
    }
    else {
        if (p->right == nullptr || p->left == nullptr) {
            tree* temp = p;
            p = p->right == nullptr ? p->left : p->right;
            delete temp;
        }
        else {
            tree* maxLeft = get_max(p->left);
            p->h_room = maxLeft->h_room;
            del_el(p->left, maxLeft->h_room);
        }
    }
    if (p != nullptr) {
        update_hight(p);
        balance(p);
    }
}

void Tree::new_string(QString& str){
    switch(str.toInt() / 1000){
    case 4:
        str.replace(0, 1, "L");
        break;
    case 3:
        str.replace(0, 1, "P");
        break;
    case 2:
        str.replace(0, 1, "O");
        break;
    case 1:
        str.replace(0, 1, "M");
        break;
    }
}

void Tree::write_to_file(tree* p){
    if (p->right != NULL){
        write_to_file(p->right);
    }
    QString str = p->h_room;
    new_string(str);
    QFile file("C:\\hot\\hotel\\rooms\\" + str + ".txt");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << p->h_room << " " << p->num_beds << " " << p->num_rooms << " " << p->toilet << " " << p->equipment << " " << free_beds[p->h_room.toInt()];
    file.close();
    if (p->left != NULL){
        write_to_file(p->left);
    }
}

void Tree::del_file(QString name){
    QString str = QStringLiteral("C:\\hot\\hotel\\rooms\\") + name + QStringLiteral(".txt");
    const char *  file = str.toLocal8Bit().constData();
    if (remove(file) != 0) {
        qDebug() << "the file could not be deleted";
    } else {
        qDebug() << "the file was deleted successfully";
    }
}

void Tree::find_room(tree* p, QString room, QTableWidget* tableWidget, bool &flag){
    if (p == NULL){
        return;
    }
    if (p->h_room == room){
        flag = true;
        if (tableWidget != NULL){
            QString f = (p->toilet == 1 ? "Есть" : "Нет");
            QString str = p->h_room;
            new_string(str);
            tableWidget->setItem(0, 0, new QTableWidgetItem(str));
            tableWidget->setItem(0, 1, new QTableWidgetItem(QString::number(p->num_beds)));
            tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(p->num_rooms)));
            tableWidget->setItem(0, 3, new QTableWidgetItem(f));
            tableWidget->setItem(0, 4, new QTableWidgetItem(p->equipment));
        }
        return;
    }
    if (room > p->h_room){
        find_room(p->right, room, tableWidget, flag);
    }
    else{
        find_room(p->left, room, tableWidget,flag);
    }
}

bool Tree::word_in_string(QString word, QString str){
    const int size = 1105;
    int array[size];
    int m = word.size();
    int n = str.size();
    for (int i = 0; i < size; ++i){
        array[i] = m;
    }
    for (int i = 0; i < m - 1; ++i){
        array[word[i].unicode()] = m - 1 - i;
    }
    int i = m - 1, j = m - 1;
    while (i < n){
        if(str[i] == word[j]){
            if(j == 0){
                return true;
            }
            --i;
            --j;
        }
        else{
            i += array[str[i].unicode()];
            j = m - 1;
        }
    }
    return false;
}

void Tree::find_eq(tree* p, QString e, QTableWidget* tableWidget, linked_list* list){
    if (p != NULL){
        QStringList l = e.split(",");
        bool flag = false;
        for (int i = 0; i < l.size(); i++){
            flag = word_in_string(l[i], p->equipment);
        }
        if (flag){
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            QString str = p->h_room;
            new_string(str);
            QString f = (p->toilet == 1 ? "Есть" : "Нет");
            tableWidget->setItem(row, 0, new QTableWidgetItem(str));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(p->num_beds)));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(p->num_rooms)));
            tableWidget->setItem(row, 3, new QTableWidgetItem(f));
            tableWidget->setItem(row, 4, new QTableWidgetItem(p->equipment));
            tableWidget->setItem(row, 5, new QTableWidgetItem(list->find_passport(p->h_room)));
        }
        find_eq(p->left, e, tableWidget, list);
        find_eq(p->right, e, tableWidget, list);
    }

}

void Tree::del_tree(tree*& p) {
    if (p == nullptr) {
        return;
    }
    del_tree(p->right);
    del_tree(p->left);
    QString str = p->h_room;
    new_string(str);
    del_file(str);
    qDebug() << str;
    delete p;
    p = NULL;
}

void Tree::show_tree(tree* p, linked_list* list, QTableWidget* tableWidget){
    if (p != NULL){
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        QString str = p->h_room;
        new_string(str);
        QString f = (p->toilet == 1 ? "Есть" : "Нет");
        tableWidget->setItem(row, 0, new QTableWidgetItem(str));
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(p->num_beds)));
        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(p->num_rooms)));
        tableWidget->setItem(row, 3, new QTableWidgetItem(f));
        tableWidget->setItem(row, 4, new QTableWidgetItem(p->equipment));
        str = p->h_room;
        tableWidget->setItem(row, 5, new QTableWidgetItem(list->find_room(str)));
        show_tree(p->left, list, tableWidget);
        show_tree(p->right, list, tableWidget);
    }
}

void Tree::print(tree* p, int h) {
    if (p != nullptr) {
        print(p->right, h + 4);
        qDebug().noquote().nospace() << QString("%1%2").arg("", h, QLatin1Char(' ')).arg(p->h_room);
        print(p->left, h + 4);
    }
}
