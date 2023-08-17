#include "OneMarkdown.h"
#include "./ui_OneMarkdown.h"
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include "maddy/parser.h"
#include <QDebug>
#include<QtWebEngine/QtWebEngine>
auto parser = std::make_shared<maddy::Parser>();

std::string readFileIntoString(const std::string& path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}
// std::string html_head = readFileIntoString("index.html");
OneMarkdown::OneMarkdown(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OneMarkdown)
{
    ui->setupUi(this);
    QString text = "<h1> 一级标题 </h1>";
    // ui->textEdit->setPlainText(text);//加载html用setHtml
    // ui->textEdit->setHtml(text);
    ui->webEngineView->load(QUrl("file:///data/html/index.html"));
}

OneMarkdown::~OneMarkdown()
{
    delete ui;
}


void OneMarkdown::on_textEdit_textChanged()
{
    QString text = ui->textEdit->toPlainText();
    std::string str = text.toStdString();
    std::stringstream markdownInput(str);
    std::string htmlOutput = parser->Parse(markdownInput);
    QString html = QString::fromStdString(htmlOutput);
    ui->webEngineView->page()->runJavaScript(QString("add('%1')").arg(html));
    qDebug()<<"HTML output"<<html<<endl;
}

