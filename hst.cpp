#include "hst.h"
#include "ui_hst.h"
#include "QDebug"
#include "widget.h"
hst::hst(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::hst)
{
    ui->setupUi(this);
    QString folderPath = "C:\\hot\\hotel\\history";
    QDir directory(folderPath);
    if (!directory.exists()) {
        qDebug() << "unable to access the database";
    }
    QStringList files = directory.entryList(QStringList() << "*.txt", QDir::Files);
    int i = 0;
    foreach (QString filename, files) {
        i++;
    }
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Номер паспорта" << "Номер комнаты" << "Дата заселения" << "Дата выселения");
    ui->tableWidget->setRowCount(i);
    int j = 0;
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
            QString h = data[0];
            ui->tableWidget->setItem(j, 0, new QTableWidgetItem(h));
            ui->tableWidget->setItem(j, 1, new QTableWidgetItem(data[1]));
            ui->tableWidget->setItem(j, 2, new QTableWidgetItem(data[2]));
            ui->tableWidget->setItem(j, 3, new QTableWidgetItem(data[3]));
            qDebug() << "i am" << h << data[1] << data[2] << data[3];
            j+=1;
        }
        file.close();
    }
}

hst::~hst()
{
    delete ui;
}

void hst::on_pushButton_clicked()
{
    this->close();
    Widget* w = new Widget;
    w->setWindowTitle("Регистрация постояльцев в номерах");
    w->show();
}


