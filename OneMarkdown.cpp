#include "OneMarkdown.h"
#include "./ui_OneMarkdown.h"
#include <memory>
#include <string>
#include "maddy/parser.h"
#include<QDebug>
std::stringstream markdownInput("# 一级标题");

// config is optional
// std::shared_ptr<maddy::ParserConfig> config = std::make_shared<maddy::ParserConfig>();

// config->isEmphasizedParserEnabled = false; // default true - this flag is deprecated
// config->isHTMLWrappedInParagraph = false; // default true - this flag is deprecated
// config->enabledParsers &= ~maddy::types::EMPHASIZED_PARSER; // equivalent to !isEmphasizedParserEnabled
// config->enabledParsers |= maddy::types::HTML_PARSER; // equivalent to !isHTMLWrappedInParagraph

// std::shared_ptr<maddy::Parser> parser = std::make_shared<maddy::Parser>(config);


OneMarkdown::OneMarkdown(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OneMarkdown)
{
    ui->setupUi(this);
    QString text = "<h1> 一级标题 </h1>";
    // ui->textEdit->setPlainText(text);//加载html用setHtml
    ui->textEdit->setHtml(text);
}

OneMarkdown::~OneMarkdown()
{
    delete ui;
}


void OneMarkdown::on_textEdit_textChanged()
{
    QString text = ui->textEdit->toPlainText();
    QString html = ui->textEdit->toHtml();
    // std::string htmlOutput = parser->Parse(markdownInput);
    // html = QString::fromStdString(htmlOutput); 
    ui->textBrowser->setHtml(html);
    qDebug() << "OneMarkdown::on_textEdit_" <<text<<endl;
}

