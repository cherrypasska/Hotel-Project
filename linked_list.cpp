#include "linked_list.h"

linked_list::linked_list() {
    size = 0;
    head = NULL;
    tail = NULL;
    QString folderPath = "C:\\hot\\hotel\\nowhistory";
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
            push_back(data[0], data[1], data[2], data[3]);
        }
        file.close();
    }
}

void linked_list::push_back(QString pas, QString h_r, QString c_date, QString e_date){
    size++;
    node* ptr = new node(pas, h_r, c_date, e_date);
    ptr->prev = tail;
    ptr->next = NULL;
    if (tail != NULL){
        tail->next = ptr;
    }
    if (head == NULL){
        head = ptr;
    }
    tail = ptr;
    //counting_sort();
    write_to_file(h_r,pas,c_date,e_date);
}

void linked_list::pop_front(){
    if (size != 0){
        size--;
        if (head == NULL){
            return;
        }
        node* ptr = head->next;
        if(ptr != NULL){
            ptr->prev = NULL;
        }
        else{
            tail = NULL;
        }
        delete head;
        head = ptr;
    }
    else{
        qDebug() << "list is empty";
    }
    //counting_sort();
}

void linked_list::pop_back(){
    if (size != 0){
        size--;
        if (tail == NULL){
            return;
        }
        node* ptr = tail->prev;
        if (ptr != NULL){
            ptr->next = NULL;
        }
        else{
            head = NULL;
        }
        delete tail;
        tail = ptr;
        if (tail != NULL) {
            tail->prev = ptr;
        }
    }
    else{
        qDebug() << "list is empty";
    }
    //counting_sort();
}

void linked_list::pop_el(QString pas){
    if (size != 0){
        size--;
        node* p = head;
        bool flag = false;
        while (p != NULL){
            if (p->passport == pas){
                del_file(pas);
                flag = true;
                break;
            }
            p = p->next;

        }
        if (!flag){
            qDebug() << "the guest was not found";
            return;
        }
        if (p == NULL){
            return;
        }
        if (p->prev == NULL){
            pop_front();
            return;
        }
        if (p->next == NULL){
            pop_back();
            return;
        }
        node* left = p->prev;
        node* right = p->next;
        left->next = right;
        right->prev = left;
        delete p;
    }
    else{
        qDebug() << "list is empty";
    }
    //counting_sort();
}

void linked_list::swap(node* a, node* b){
    QString temp_passport = a->passport;
    QString temp_h_room = a->h_room;
    QString temp_check_in_date = a->check_in_date;
    QString temp_eviction_date = a->eviction_date;

    a->passport = b->passport;
    a->h_room = b->h_room;
    a->check_in_date = b->check_in_date;
    a->eviction_date = b->eviction_date;

    b->passport = temp_passport;
    b->h_room = temp_h_room;
    b->check_in_date = temp_check_in_date;
    b->eviction_date = temp_eviction_date;
}

void linked_list::counting_sort() {
    if (size <= 1) {
        return;
    }
    QVector<node*> list1;
    node* ptr = head;
    int i = 0;
    while(ptr!=NULL){
        list1[i] = ptr;
    }
    QVector<node*> sorted;
    for(int j = 0; j < list1.size(); i++){
        int k = 0;
        for(int h = 0; h < list1.size(); i++){
            if((list1[h] < list1[j]) || ((list1[h] == list1[j]) && (h < j))) k++;
        }
        sorted[k] = list1[j];
    }
    head = sorted[0];
    head->prev = NULL;
    ptr = head;
    for (int i = 1; i < size; ++i) {
        ptr->next = sorted[i];
        sorted[i]->prev = ptr;
        ptr = ptr->next;
    }
    tail = ptr;
    tail->next = NULL;
}

QString linked_list::find_passport(QString pas){
    node* p = head;
    while (p != NULL){
        if (p->passport == pas){
            return p->h_room;
        }
        p = p->next;
    }
    return "не проживает";
}

QString linked_list::find_room(QString h_r){
    node* p = head;
    QString pas = "";
    while (p != NULL){
        if (p->h_room == h_r){
            pas += (p->passport + ", ");
        }
        p = p->next;
    }
    if (pas != "" && pas[pas.size() - 2] == ','){
        pas = pas.left(pas.size() - 2);
        return pas;
    }
    else if(pas != ""){
        return pas;
    }
    else{
        return "не проживает";
    }
}

bool linked_list::is_empty(){
    return head == NULL;
}

void linked_list::clear() {
    while (head) {
        node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

void linked_list::del_file(QString p){
    QString str = QStringLiteral("C:\\hot\\hotel\\nowhistory\\") + p + QStringLiteral(".txt");
    const char *  file = str.toLocal8Bit().constData();
    if (remove(file) != 0) {
        qDebug() << "the guest was not found!";
    } else {
        qDebug() << "the file was deleted successfully";
    }
}

void linked_list::write_to_file(QString h_r, QString pas, QString c_date, QString e_date){
    QFile file("C:\\hot\\hotel\\nowhistory\\" + pas + ".txt");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << pas << " " << h_r << " " << c_date << " " << e_date;
    file.close();
    QFile file1("C:\\hot\\hotel\\history\\" + pas + ".txt");
    file1.open(QIODevice::WriteOnly);
    QTextStream ou(&file1);
    ou << pas << " " << h_r << " " << c_date << " " << e_date;
    file1.close();
}

void linked_list::print(){
    node* ptr = head;
    while (ptr != NULL){
        qDebug() << ptr->h_room << " " << ptr->passport;
        ptr = ptr->next;
    }
}

linked_list::~linked_list(){
    clear();
}
