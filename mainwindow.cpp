#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db;
    db=db.addDatabase("QSQLITE");
    db.setDatabaseName("itemPrice.db");
    db.open();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_Load_clicked()
{
    QSqlQuery q;
    q.exec("SELECT * FROM items");

    QSqlQueryModel *m = new QSqlQueryModel;
    m->setQuery(std::move(q));  // or m->setQuery(q);

    ui->tableView->setModel(m);
}

void MainWindow::on_pb_Read_clicked()
{
    QSqlQuery q;
    QString a;

    a= ui->lineName1->text();
    q.exec("SELECT numbers,price FROM items WHERE name = '"+a+"'");

    if (q.first()) {
        ui->label_number->setText(q.value(0).toString());
        ui->label_price->setText(q.value(1).toString());
        ui->label_total->setText(QString::number(q.value(0).toInt()* q.value(1).toInt()));
    }else {
        ui->label_number->setText("Error !!!");
        ui->label_price->setText("Error !!!");
        ui->label_total->setText("Error !!!");
    }
}


void MainWindow::on_pb_Delete_clicked()
{
    QSqlQuery q;
    QString a;
    a= ui->lineName2->text();
    q.exec("DELETE FROM items WHERE name= '"+a+"' ");
}


void MainWindow::on_pb_Replace_clicked()
{
    QSqlQuery q;
    QString a,b;

    a=ui->lineName3->text();
    b=ui->lineprice->text();

    q.exec("UPDATE items SET price= '"+b+"' WHERE name= '"+a+"' ");

    on_pb_Load_clicked();   // for reload
}

