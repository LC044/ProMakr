#include "OneMarkdown.h"
#include "./ui_OneMarkdown.h"

auto parser = std::make_shared<maddy::Parser>();

// std::string html_head = readFileIntoString("index.html");
OneMarkdown::OneMarkdown(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::OneMarkdown)
{

    ui->setupUi(this);
    QString text = "<h1> 一级标题 </h1>";
    ui->webEngineView->load(QUrl("file:///data/html/index.html"));

    const int tabStop = TAB_WIDTH; // 4 characters
    QFontMetrics metrics(ui->textEdit->font());
    ui->textEdit->setTabStopWidth(tabStop * metrics.width(' '));
    connect(ui->textEdit, &QTextEdit::textChanged, this, &OneMarkdown::textEdit_textChanged);
    statusLabel = new QLabel("我是状态栏", this);
    ui->statusBar->addPermanentWidget(statusLabel); // 添加右侧标签(永久性)
    QTimer *timer = new QTimer(this);
    timer->start(1000); // 每隔1000ms发送timeout的信号
    connect(timer, SIGNAL(timeout()), this, SLOT(time_update()));
    ui->textEdit->setFont(QFont("宋体", 12)); // 设置字体和字体大小
    // ui->textEdit->setTextColor(Qt::red);//设置字体颜色
    // 设置侧边栏初始比例 2:8
    ui->splitter->setStretchFactor(0, 2);
    ui->splitter->setStretchFactor(1, 8);
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
    disconnect(ui->textEdit, &QTextEdit::textChanged, this, &OneMarkdown::textEdit_textChanged);
    QString text = ui->textEdit->toPlainText();
    std::string str = text.toStdString();
    std::stringstream markdownInput(str);
    std::string htmlOutput = parser->Parse(markdownInput);
    QString html = QString::fromStdString(htmlOutput);
    ui->webEngineView->page()->runJavaScript(QString("add('%1')").arg(html));
    connect(ui->textEdit, &QTextEdit::textChanged, this, &OneMarkdown::textEdit_textChanged);
    countWords();
    qDebug() << "HTML output" << html << endl;
    qDebug() << "text output" << text << endl;
    qDebug() << "text output" << text.replace('\t', "    ") << endl;
    // ui->statusBar.
}

void OneMarkdown::time_update()
{
    //[1] 获取时间
    QDateTime current_time = QDateTime::currentDateTime();
    QString timestr = current_time.toString("hh:mm:ss"); // 设置显示的格式
    statusLabel->setText(timestr);                       // 设置label的文本内容为时间
}

void OneMarkdown::on_splitter_splitterMoved(int pos, int index)
{
}

int OneMarkdown::countWords()
{
    QString text = ui->textEdit->toPlainText();
    if (text.length() - size == 1)
    {
        if (text.length() == 1)
        {
            if (!text.at(0).isSpace())
            {
                counter++;
                ui->btn_word_count->setText(QString("%1 词").arg(QString::number(counter)));
            }
        }
        if (text.length() > 2)
        {
            start = text.length() - 1;
            end = text.length();
            if (text.at(start - 1).isSpace() && !text.at(end - 1).isSpace())
            {
                counter++;
                ui->btn_word_count->setText(QString("%1 词").arg(QString::number(counter)));
            }
        }
    }
    else if (text.length() - size > 1)
    {
        counter = 0;
        if (!text.at(0).isSpace())
            counter++;
        for (int i = 1; i < text.length(); i++)
        {
            if (!text.at(i).isSpace() && text.at(i - 1).isSpace())
                counter++;
        }
        ui->btn_word_count->setText(QString("%1 词").arg(QString::number(counter)));
    }
    size = text.length();
    return size;
    // int wordCount = ui->textEdit->toPlainText().split(QRegExp("(\\s|\\n|\\r)+")
    //             , QString::SkipEmptyParts).count();
    // return wordCount;
}
void OneMarkdown::on_btn_hide_show_sideBar_clicked()
{
    isShowSideBar = !isShowSideBar;
    ui->widget_side_bar->setVisible(isShowSideBar);
    if(isShowSideBar){
        ui->btn_hide_show_sideBar->setIcon(QIcon(":/icon/icon/btn_side_bar_show.png"));
    }
    else{
        // ui->splitter->setStretchFactor(0, 0);
        // ui->splitter->setStretchFactor(1, 10);
        ui->btn_hide_show_sideBar->setIcon(QIcon(":/icon/icon/btn_side_bar_hide.png"));
    }
}

