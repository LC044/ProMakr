#include "table.h"
#include "ui_table.h"
#include "table.h"
/*#include <iostream>
using namespace std;*/
table::table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::table)
{
    ui->setupUi(this);
    connect(ui->cancel_Button,&QPushButton::clicked,this,&table::close);
//    connect(ui->certify_Button,&QPushButton::clicked,this,&table::on_certify_Button_clicked);
}

table::~table()
{
    delete ui;
}

void table::on_certify_Button_clicked()
{
    QString col_text = ui->column_lineEdit->text();
    QString row_text = ui->row_lineEdit->text();

    emit textEntered(col_text, row_text);
    close();
}

