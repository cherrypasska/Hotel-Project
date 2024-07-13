#include "human.h"
#include "ui_human.h"
#include "widget.h"

human::human(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::human),
    table(new hash_table()),
    tree(new Tree()),
    list(new linked_list())
{
    ui->setupUi(this);
    QList<QPushButton*> pushButtonList = {ui->pushButton_2, ui->pushButton_4, ui->pushButton_5, ui->pushButton_7, ui->pushButton_8, ui->pushButton_9};
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Номер паспорта" << "ФИО" << "Год рождения" << "Адрес" << "Цель прибытия" << "Номер");
    ui->lineEdit->setMaxLength(10);
    ui->lineEdit_3->setMaxLength(4);
    ui->lineEdit_6->setMaxLength(4);
    QDate minDate(2024, 5, 29);
    ui->dateEdit->setMinimumDate(minDate);
    ui->dateEdit_2->setMinimumDate(minDate);
    for (QPushButton* pushButton : pushButtonList){
        pushButton->setEnabled(false);
    }
    if (!table->is_empty()){
        table->print_hash(ui->tableWidget, list);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Номер паспорта" << "ФИО" << "Год рождения" << "Адрес" << "Цель прибытия" << "Номер");
    }
}

human::~human()
{
    delete ui;
    delete table;
}

void human::check_but(){ //откл кнопок
    bool l_1 = !ui->lineEdit->text().isEmpty();
    bool l_2 = !ui->lineEdit_2->text().isEmpty();
    bool l_3 = !ui->lineEdit_3->text().isEmpty();
    bool l_4 = !ui->lineEdit_4->text().isEmpty();
    bool l_5 = !ui->lineEdit_5->text().isEmpty();
    bool l_6 = !ui->lineEdit_6->text().isEmpty();
    ui->pushButton_4->setEnabled(l_1 && l_2 && l_3 && l_4 && l_5);
    if (l_1 && ui->lineEdit->text().length() == 10){
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
    }
    else{
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
    }
    ui->pushButton_7->setEnabled(l_2);
    ui->pushButton_8->setEnabled(l_1 && l_6);
    ui->pushButton_9->setEnabled(l_1 && l_6);
}

void human::clean_table(){ //очистка таблицы
    int row = 0, col = 0;
    while (row < ui->tableWidget->rowCount() && col < ui->tableWidget->columnCount()) {
        if (ui->tableWidget->item(row, col) != nullptr && !ui->tableWidget->item(row, col)->text().isEmpty()) {
            ui->tableWidget->removeRow(row);
        }
        else {
            row++;
            col++;
        }
    }
}

void human::on_pushButton_clicked()
{
    this->close();
    Widget* w = new Widget;
    w->setWindowTitle("Регистрация постояльцев в номерах");
    w->show();
}


void human::on_pushButton_2_clicked()
{
    if (!table->is_empty()){
        if (list->find_passport(ui->lineEdit->text()) == "не проживает"){
            int index = table->hash_func(ui->lineEdit->text());
            table->del_el(&table->h_table[index],ui->lineEdit->text(), list);
            QString str = ui->lineEdit_6->text();
            str = str.replace("L","4");
            str = str.replace("P","3");
            str = str.replace("O","2");
            str = str.replace("M","1");
        }
    }
    else{
        qDebug() << "table is empty";
    }
    check_but();

}


void human::on_pushButton_3_clicked()
{
    clean_table();
    if (!table->is_empty()){
        table->print_hash(ui->tableWidget, list);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Номер паспорта" << "ФИО" << "Год рождения" << "Адрес" << "Цель прибытия" << "Номер");
    }
    else{
        qDebug() << "table is empty";
    }
    check_but();

}


void human::on_pushButton_4_clicked()
{
    if (table->h_table[table->hash_func(ui->lineEdit->text())] != NULL && table->h_table[table->hash_func(ui->lineEdit->text())]->passport == ui->lineEdit->text()){
        qDebug() << "the guest has already been registered";
    }
    else{
        int index = table->hash_func(ui->lineEdit->text());
        table->add_el(&table->h_table[index], ui->lineEdit->text(), ui->lineEdit_2->text().replace(" ","_"), ui->lineEdit_3->text().toInt(), ui->lineEdit_4->text().replace(" ","_"), ui->lineEdit_5->text());
        table->write_to_file(table->h_table[index]);
        qDebug() << "the guest has been successfully registered";
    }
    check_but();

}


void human::on_pushButton_5_clicked()
{
    clean_table();
    if (!table->is_empty()){
        ui->tableWidget->setRowCount(1);
        bool flag;
        table->find_passport(ui->lineEdit->text(), ui->tableWidget,flag);
        QString str = list->find_passport(ui->lineEdit->text());
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
        ui->tableWidget->setItem(0, 5, new QTableWidgetItem(str));
        //list->print();
    }
    else{
        qDebug() << "table is empty";
    }
    check_but();
}


void human::on_pushButton_6_clicked()
{
    if (!table->is_empty() && list->is_empty()){
        table->del_hash_table(list);
        clean_table();
    }
    else{
        qDebug() << "table is empty or are the guests settled";
    }
    check_but();
}


void human::on_pushButton_7_clicked()
{
    clean_table();
    if (!table->is_empty()){
        ui->tableWidget->setRowCount(1);
        table->find_fio(ui->lineEdit_2->text().replace(" ","_"), ui->tableWidget);
    }
    else{
        qDebug() << "table is empty";
    }
    check_but();

}


void human::on_pushButton_8_clicked()
{
    QString str = ui->lineEdit_6->text();
    str = str.replace("L","4");
    str = str.replace("P","3");
    str = str.replace("O","2");
    str = str.replace("M","1");
    if (tree->free_beds[str.toInt()] != 0){
        bool flag = false;
        bool flag_1 = false;
        table->find_passport(ui->lineEdit->text(),NULL,flag_1);
        tree->find_room(tree->root,str,NULL,flag);
        if (flag && flag_1 && list->find_passport(ui->lineEdit->text()) == "не проживает"){
            list->push_back(ui->lineEdit->text(), str, c_date, e_date);
            tree->free_beds[str.toInt()] -= 1;
            tree->write_to_file(tree->root);
            qDebug() << "the guest has been successfully settled";
        }
        else{
            qDebug() << "the room or guest was not found";
        }
    }
    else{
        qDebug() << "all the seats in the room are occupied";
    }
    check_but();

}


void human::on_pushButton_9_clicked()
{
    QString str = ui->lineEdit_6->text();
    str = str.replace("L","4");
    str = str.replace("P","3");
    str = str.replace("O","2");
    str = str.replace("M","1");
    if (list->find_passport(ui->lineEdit->text()) != "не проживает"){
        tree->free_beds[str.toInt()] += 1;
        tree->write_to_file(tree->root);
        list->pop_el(ui->lineEdit->text());
        qDebug() << "The guest has been evicted";
    }
    else{
        qDebug() << "such a guest does not live";
    }

}

void human::on_lineEdit_textChanged(const QString &arg1) //проверка корректности паспорта
{
    if (!arg1.toLongLong()){
        ui->lineEdit->clear();
    }
    check_but();
}

void human::on_lineEdit_2_textChanged(const QString &arg1)
{
    if (arg1.toInt()){
        ui->lineEdit_2->clear();
    }
    check_but();
}

void human::on_lineEdit_3_textChanged(const QString &arg1) //проверка корректности даты рождения
{
    if (!arg1.toInt() || arg1.toInt() > 2024){
        ui->lineEdit_3->clear();
    }
    check_but();
}

void human::on_lineEdit_4_textChanged(const QString &arg1)
{
    if (arg1.toInt()){
        ui->lineEdit_4->clear();
    }
    check_but();
}

void human::on_lineEdit_5_textChanged(const QString &arg1)
{
    if (arg1.toInt()){
        ui->lineEdit_5->clear();
    }
    check_but();
}

void human::on_lineEdit_6_textChanged(const QString &arg1)
{
    if ((!arg1.isEmpty() && arg1[0] != 'L' && arg1[0] != 'P' && arg1[0] != 'O' && arg1[0] != 'M') || (arg1.size() > 1 && !arg1.mid(1).toInt() && arg1.mid(1) != "0" && arg1.mid(1) != "00")){
        ui->lineEdit_6->clear();
    }
    check_but();
}

void human::on_dateEdit_userDateChanged(const QDate &date)
{
    c_date = date.toString("dd.MM.yyyy");
    if (ui->dateEdit->date() > ui->dateEdit_2->date()){
        ui->dateEdit_2->setDate(ui->dateEdit->date().addDays(1));
    }
    check_but();
}

void human::on_dateEdit_2_userDateChanged(const QDate &date)
{
    if (!(ui->dateEdit->date() > ui->dateEdit_2->date())){
        e_date = date.toString("dd.MM.yyyy");
    }
    else{
        ui->dateEdit_2->setDate(ui->dateEdit->date().addDays(1));
    }
    check_but();
}
