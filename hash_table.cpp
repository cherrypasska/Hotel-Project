#include "hash_table.h"
#include "linked_list.h"


hash_table::hash_table(){
    QString folderPath = "C:\\hot\\hotel\\guests";
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
            int index = hash_func(data[0]);
            add_el(&h_table[index], data[0], data[1], data[2].toInt(), data[3], data[4]);
        }
        file.close();
    }
}

int hash_table::hash_func(const QString& key) {
    int h = 0;
    for (QChar c : key) {
        h += 2 * c.unicode() * c.unicode() * c.unicode();
    }
    return h % 1500;
}

void hash_table::add_el(key** head, QString pa, QString f, int y, QString a, QString pu) {
    key* cur = *head;
    key* p = new key(pa, f, y, a, pu);
    if (cur == NULL) {
        p->next = NULL;
        *head = p;
    }
    else {
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = p;
        p->next = NULL;
    }
}

void hash_table::del_file(QString k, linked_list* list){
    if(list->find_passport(k) != "не проживает"){
        QString str = QStringLiteral("C:\\hot\\hotel\\guests\\") + k + QStringLiteral(".txt");
        const char *  file = str.toLocal8Bit().constData();
        if (remove(file) != 0) {
            qDebug() << "the guest was not found";
        }
        else {
            qDebug() << "the file was deleted successfully";
        }
        QString str1 = QStringLiteral("C:\\hot\\hotel\\nowhistory\\") + k + QStringLiteral(".txt");
        const char *  file1 = str.toLocal8Bit().constData();
        if (remove(file) != 0) {
        }
        else {
        }
    }
}

void hash_table::del_el(key** head, QString k, linked_list* list) {
    bool flag = false;
    key* e = *head;
    key* prev = nullptr;
    while (e != nullptr) {
        if (e->passport == k) {
            flag = true;
            break;
        }
        prev = e;
        e = e->next;
    }
    if (flag) {
        if (e == *head) {
            *head = e->next;
        } else {
            prev->next = e->next;
        }
        delete e;
        del_file(k, list);
    } else {
        qDebug() << "The guest was not found";
    }
}

bool hash_table::is_empty(){
    for (int i = 0; i < 1500; i++){
        if (h_table[i] != NULL){
            return false;
        }
    }
    return true;
}

void hash_table::del_hash_table(linked_list* list){
    for (int i = 0; i < 1500; i++){
        if (h_table[i] != NULL){
            while (h_table[i] != NULL){
                key* temp = h_table[i];
                h_table[i] = h_table[i]->next;
                del_file(temp->passport, list);
                delete temp;
            }
        }
    }
}

void hash_table::find_passport(QString pas, QTableWidget* tableWidget, bool &flag){
    int index = hash_func(pas);
    if (h_table[index] != NULL){
        key* p = h_table[index];
        while (p != NULL){
            if (p->passport == pas){
                flag = true;
                if (tableWidget != NULL){
                    tableWidget->setItem(0, 0, new QTableWidgetItem(p->passport));
                    tableWidget->setItem(0, 1, new QTableWidgetItem(p->fio));
                    tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(p->year)));
                    tableWidget->setItem(0, 3, new QTableWidgetItem(p->address));
                    tableWidget->setItem(0, 4, new QTableWidgetItem(p->purpose));
                }
                return;
            }
            p = p->next;

        }
    }
    else{
        qDebug() << "The guest has not been found";
    }
}

void hash_table::find_fio(QString f, QTableWidget* tableWidget){
    int row = 0;
    bool flag = false;
    for (int i = 0; i < 1500; i++){
        if (h_table[i] != NULL){
            key* p = h_table[i];
            while (p != NULL){
                if (p->fio == f){
                    int index = hash_func(p->passport);
                    tableWidget->setItem(row, 0, new QTableWidgetItem(p->passport));
                    tableWidget->setItem(row, 1, new QTableWidgetItem(p->fio));
                    tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(h_table[index]->year)));
                    tableWidget->setItem(0, 3, new QTableWidgetItem(h_table[index]->address));
                    tableWidget->setItem(0, 4, new QTableWidgetItem(h_table[index]->purpose));
                    row++;
                    flag = true;
                }
                p = p->next;
            }
        }
    }
    if (flag == false){
        qDebug() << "The guest has not been found";
    }
}

void hash_table::print_hash(QTableWidget* tableWidget, linked_list* list) {
    for (int i = 0; i < 1500; ++i) {
        key* current = h_table[i];
        while (current != nullptr) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(current->passport));
            tableWidget->setItem(row, 1, new QTableWidgetItem(current->fio));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(current->year)));
            tableWidget->setItem(row, 3, new QTableWidgetItem(current->address));
            tableWidget->setItem(row, 4, new QTableWidgetItem(current->purpose));
            tableWidget->setItem(row, 5, new QTableWidgetItem(list->find_passport(current->passport)));
            current = current->next;
        }
    }
}

void hash_table::write_to_file(key* head) {
    key* p = head;
    while (p != NULL) {
        QFile file("C:\\hot\\hotel\\guests\\" + p->passport + ".txt");
            file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out << p->passport << " " << p->fio << " " << p->year << " " << p->address << " " << p->purpose;
        file.close();
        p = p->next;
    }
}

void hash_table::print(){
    for (int i = 0; i < 1500; i++){
        if (h_table[i] != NULL){
            key* p = h_table[i];
            while (p != NULL){
                qDebug() << p->passport;
                p = p->next;
            }
        }
    }
}
