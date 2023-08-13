#include "OneMarkdown.h"
#include "./ui_OneMarkdown.h"

OneMarkdown::OneMarkdown(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OneMarkdown)
{
    ui->setupUi(this);
}

OneMarkdown::~OneMarkdown()
{
    delete ui;
}

