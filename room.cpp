#include "room.h"
#include "ui_room.h"

room::room(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::room),
    tree(new Tree()),
    list(new linked_list())
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Номер" << "Количество мест" << "Количество комнат" << "Санузел" << "Оборудование" << "Паспорт");
    ui->tableWidget->setColumnWidth(0, 60);
    ui->tableWidget->setColumnWidth(1, 140);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 70);
    ui->tableWidget->setColumnWidth(4, 300);
    ui->tableWidget->setColumnWidth(5, 90);
    ui->lineEdit->setMaxLength(4);
    ui->lineEdit_2->setMaxLength(1);
    ui->lineEdit_3->setMaxLength(1);
    ui->radioButton_2->click();
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    on_pushButton_4_clicked();
}

room::~room()
{
    delete tree;
    delete ui;
}

void room::check_but(){
    bool l_1 = !ui->lineEdit->text().isEmpty();
    bool l_2 = !ui->lineEdit_2->text().isEmpty();
    bool l_3 = !ui->lineEdit_3->text().isEmpty();
    ui->pushButton_2->setEnabled(l_1 && l_2 && l_3);
    ui->pushButton_3->setEnabled(l_1);
    ui->pushButton_6->setEnabled(l_1);
}

void room::clean_table(){
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

void room::check_eq(QString &s){
    QString str = "";
    if (ui->checkBox->isChecked()){
        str += "телевизор,";
    }
    if (ui->checkBox_2->isChecked()){
        str += "холодильник,";
    }
    if (ui->checkBox_3->isChecked()){
        str += "кондиционер,";
    }
    if (ui->checkBox_4->isChecked()){
        str += "сейф,";
    }
    if (!ui->checkBox->isChecked() && !ui->checkBox_2->isChecked() && !ui->checkBox_3->isChecked() && !ui->checkBox_4->isChecked()) {
        str = "отсутствует";
    }
    if (str[str.size() - 1] == ','){
        str = str.left(str.size() - 1);
    }
    s = str;
}

void room::new_string(QString& s){
    s = s.replace("L","4");
    s = s.replace("P","3");
    s = s.replace("O","2");
    s = s.replace("M","1");
}

void room::on_pushButton_clicked()
{
    Widget* w = new Widget;
    w->setWindowTitle("Регистрация постояльцев в номерах");
    w->show();
    this->close();
}

void room::on_pushButton_2_clicked() //создать номер
{
    QString str = ui->lineEdit->text();
    new_string(str);
    QString str1;
    check_eq(str1);
    tree->add_el(tree->root,str, ui->lineEdit_2->text().toInt(), ui->lineEdit_3->text().toInt(), flag, str1);
    tree->free_beds[str.toInt()] = ui->lineEdit_2->text().toInt();
    tree->write_to_file(tree->root);
    qDebug() << "the room has been successfully registered";
}

void room::on_pushButton_3_clicked() //удалить номер
{
    if (tree->root != NULL){
        QString str = ui->lineEdit->text();
        new_string(str);
        if (list->find_room(str) == "не проживает"){
            tree->del_el(tree->root, str);
            tree->del_file(ui->lineEdit->text());
        }
        else{
            qDebug() << "The room cannot be deleted";
        }
    }
    else{
        qDebug() << "There are no registered numbers";
    }
}

void room::on_pushButton_4_clicked()//показать все
{
    clean_table();
    if (tree->root != NULL){
        tree->print(tree->root,0);
        tree->show_tree(tree->root, list, ui->tableWidget);
    }
    else{
        qDebug() << "There are no registered numbers";
    }
}

void room::on_pushButton_5_clicked() //удалить все
{
    clean_table();
    if (tree->root != NULL){
        if (list->is_empty()){
            tree->del_tree(tree->root);
        }
        else{
            qDebug() << "The rooms cannot be deleted";
        }
    }
    else{
        qDebug() << "There are no registered numbers";
    }
}

void room::on_pushButton_6_clicked() //поиск по номеру комнаты
{
    if (tree->root != NULL){
        QString str = ui->lineEdit->text();
        new_string(str);
        clean_table();
        bool flag = false;
        ui->tableWidget->setRowCount(1);
        tree->find_room(tree->root, str, ui->tableWidget, flag);
        if (flag){
            ui->tableWidget->setItem(0, 5, new QTableWidgetItem(list->find_room(str)));
        }
        else{
            qDebug() << "the room was not found";
        }
    }
    else{
        qDebug() << "There are no registered numbers";
    }
}

void room::on_pushButton_7_clicked() //поиск по фрагменту оборудования
{
    clean_table();
    if (tree->root != NULL){
        QString s;
        check_eq(s);
        tree->find_eq(tree->root, s, ui->tableWidget, list);

    }
    else{
        qDebug() << "There are no registered numbers";
    }
}

void room::on_radioButton_clicked(bool checked)
{
    if (checked){
        flag = true;
    }
}

void room::on_radioButton_2_clicked(bool checked)
{
    if (checked){
        flag = false;
    }
}

void room::on_lineEdit_textChanged(const QString &arg1)
{
    if ((!arg1.isEmpty() && arg1[0] != 'L' && arg1[0] != 'P' && arg1[0] != 'O' && arg1[0] != 'M') || (arg1.size() > 1 && !arg1.mid(1).toInt() && arg1.mid(1) != "0" && arg1.mid(1) != "00")){
        ui->lineEdit->clear();
    }
    check_but();
}

void room::on_lineEdit_2_textChanged(const QString &arg1)
{
    if (!arg1.toInt()){
        ui->lineEdit_2->clear();
    }
    check_but();
}

void room::on_lineEdit_3_textChanged(const QString &arg1)
{
    if (!arg1.toInt()){
        ui->lineEdit_3->clear();
    }
    check_but();
}
