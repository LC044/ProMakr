#include "OneMarkdown.h"
#include "./ui_OneMarkdown.h"
#include "global.h"
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include "maddy/parser.h"
#include <QDebug>
#include<QtWebEngine/QtWebEngine>
#include <QLabel>
#include <QTimer>
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
    ui->webEngineView->load(QUrl("file:///data/html/index.html"));

    const int tabStop = TAB_WIDTH;  // 4 characters
    QFontMetrics metrics(ui->textEdit->font());
    ui->textEdit->setTabStopWidth(tabStop * metrics.width(' '));
    connect(ui->textEdit,&QTextEdit::textChanged,this,&OneMarkdown::textEdit_textChanged);
    statusLabel = new QLabel("我是状态栏", this);
    ui->statusBar->addPermanentWidget(statusLabel);//添加右侧标签(永久性)
    QTimer *timer = new QTimer(this);
    timer->start(1000); //每隔1000ms发送timeout的信号
    connect(timer, SIGNAL(timeout()),this,SLOT(time_update()));
    ui->textEdit->setFont(QFont("宋体",12));//设置字体和字体大小
    // ui->textEdit->setTextColor(Qt::red);//设置字体颜色

}

OneMarkdown::~OneMarkdown()
{
    delete ui;
}


void OneMarkdown::on_textEdit_textChanged()
{
    
}

void OneMarkdown::on_textEdit_textEdited()
{

}
void OneMarkdown::on_textEdit_selectionChanged()
{

}


void OneMarkdown::textEdit_textChanged()
{
    // disconnect 可以使得编辑textedit内容的时候不陷入死循环
    disconnect(ui->textEdit,&QTextEdit::textChanged,this,&OneMarkdown::textEdit_textChanged);
    QString text = ui->textEdit->toPlainText();
    std::string str = text.toStdString();
    std::stringstream markdownInput(str);
    std::string htmlOutput = parser->Parse(markdownInput);
    QString html = QString::fromStdString(htmlOutput);
    ui->webEngineView->page()->runJavaScript(QString("add('%1')").arg(html));
    connect(ui->textEdit,&QTextEdit::textChanged,this,&OneMarkdown::textEdit_textChanged);
    qDebug()<<"HTML output"<<html<<endl;
    qDebug()<<"text output"<<text<<endl;
    qDebug()<<"text output"<<text.replace('\t', "    ")<<endl;
    // ui->statusBar.
}

void OneMarkdown::time_update()
{
    //[1] 获取时间
    QDateTime current_time = QDateTime::currentDateTime();
    QString timestr = current_time.toString( "hh:mm:ss"); //设置显示的格式
    statusLabel->setText(timestr); //设置label的文本内容为时间
}
