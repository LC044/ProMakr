#include "OneMarkdown.h"
#include "./ui_OneMarkdown.h"
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include "maddy/parser.h"
#include <QDebug>
#include<QtWebEngine/QtWebEngine>
std::string html_end = "</div></body></html>";

// config is optional
// std::shared_ptr<maddy::ParserConfig> config = std::make_shared<maddy::ParserConfig>();
// config->isEmphasizedParserEnabled = false; // default true - this flag is deprecated
// config->isHTMLWrappedInParagraph = false; // default true - this flag is deprecated
// config->enabledParsers &= ~maddy::types::EMPHASIZED_PARSER; // equivalent to !isEmphasizedParserEnabled
// config->enabledParsers |= maddy::types::HTML_PARSER; // equivalent to !isHTMLWrappedInParagraph

// std::shared_ptr<maddy::Parser> parser = std::make_shared<maddy::Parser>(config);
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
std::string html_head = readFileIntoString("index.html");
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
//    QString html = ui->textEdit->toHtml();
    std::string str = text.toStdString();
     std::stringstream markdownInput(str);
    // std::shared_ptr<maddy::Parser> parser = std::make_shared<maddy::Parser>();

     std::string htmlOutput = parser->Parse(markdownInput);
     QString html = QString::fromStdString(htmlOutput);
//    ui->textBrowser->setHtml(html);
    // ui->webEngineView->load(QUrl("https://baidu.com/"));
    // ui->webEngineView->setHtml(html);
    // qDebug() << "OneMarkdown::on_textEdit_" <<text<<endl;
    // qDebug() << "OneMarkdown::on_textEdit_" <<QString::fromStdString(htmlOutput)<<endl;
        // m_view->page()->runJavaScript(QString("showPie(%1)").arg(sHtml));
    ui->webEngineView->page()->runJavaScript(QString("add(%1)").arg(text));
}

