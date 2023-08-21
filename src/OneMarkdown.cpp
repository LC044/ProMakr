#include "OneMarkdown.h"
#include "./ui_OneMarkdown.h"

auto parser = std::make_shared<maddy::Parser>();

// std::string html_head = readFileIntoString("index.html");
OneMarkdown::OneMarkdown(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::OneMarkdown)
{

    ui->setupUi(this);
    initUi();
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
    // ui->textEdit->setTextColor(Qt::red);//设置字体颜色1
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

    if(IS_FILE_SAVED){
        IS_FILE_SAVED = false;
    }
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
    qDebug() << "splitter moved" << pos << index << endl;
    if (pos == 0 && index == 1)
    {
        on_btn_hide_show_sideBar_clicked();
        isSideClosed = true;
        // qDebug() << "splitter closed" << SideLastPos << pos << index << endl;
    }
    else
    {
        //  int w = ui->splitter->regValue("splitter_width").toInt(); //来自上次关闭时保留的值
        // ui->splitter->
        int w = ui->splitter->width();
        SidePos << pos * 100;
        qDebug() << "splitter closed" << ui->widget_side_bar->width() << pos << index << endl;
        // ui->line->setGeometry(QRect());
    }
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
    if (isShowSideBar)
    {
        ui->btn_hide_show_sideBar->setIcon(QIcon(":/icon/icon/btn_side_bar_show.png"));
        if (isSideClosed)
        {
            isSideClosed = false;
            ui->splitter->setSizes(SidePos);
        }
    }
    else
    {
        ui->btn_hide_show_sideBar->setIcon(QIcon(":/icon/icon/btn_side_bar_hide.png"));
    }
}

void OneMarkdown::InitTreeView()
{
    // 1，构造Model，这里示例具有3层关系的model构造过程
    QStandardItemModel *model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList() << "序号"
                                                   << "名称"); // 设置列头
    for (int i = 0; i < 5; i++)
    {
        // 一级节点，加入mModel
        QList<QStandardItem *> items1;
        QStandardItem *item1 = new QStandardItem(QString::number(i));
        QStandardItem *item2 = new QStandardItem("一级节点");
        items1.append(item1);
        items1.append(item2);
        model->appendRow(items1);

        for (int j = 0; j < 5; j++)
        {
            // 二级节点,加入第1个一级节点
            QList<QStandardItem *> items2;
            QStandardItem *item3 = new QStandardItem(QString::number(j));
            QStandardItem *item4 = new QStandardItem("二级节点");
            items2.append(item3);
            items2.append(item4);
            item1->appendRow(items2);

            for (int k = 0; k < 5; k++)
            {
                // 三级节点,加入第1个二级节点
                QList<QStandardItem *> items3;
                QStandardItem *item5 = new QStandardItem(QString::number(k));
                QStandardItem *item6 = new QStandardItem("三级节点");
                items3.append(item5);
                items3.append(item6);
                item3->appendRow(items3);
            }
        }
    }
    // 2，给QTreeView应用model
    ui->treeView->setModel(model);
}

void OneMarkdown::initUi()
{
    InitTreeView();
    // on_splitter_splitterMoved();
    ui->splitter->setCollapsible(1, false); // 设置右边显示窗口不可折叠
}

void OneMarkdown::on_btn_file_list_clicked()
{
}

void OneMarkdown::on_btn_outline_clicked()
{
}

void OneMarkdown::on_btn_outline_toggled(bool checked)
{
    if (!checked)
        return;
    qDebug() << "btn_outline_toggled" << endl;
}

void OneMarkdown::on_btn_file_list_toggled(bool checked)
{
    if (!checked)
        return;
    qDebug() << "btn_file_list_toggled" << endl;
}





