#include "OneMarkdown.h"
#include "./ui_OneMarkdown.h"

void OneMarkdown::on_action_new_file_triggered()
{
    
}


void OneMarkdown::on_action_open_file_triggered()
{
    //选择文件对话框/
	disconnect(ui->textEdit,&QTextEdit::textChanged,this,&OneMarkdown::textEdit_textChanged);
    QFileDialog* f = new QFileDialog(this);
    f->setWindowTitle("选择数据文件*.md");
    f->setNameFilter("*.md");
    f->setViewMode(QFileDialog::Detail);

    QString filePath;
    if(f->exec() == QDialog::Accepted)
        filePath = f->selectedFiles()[0];

    // ui->lineEdit->setText(filePath);
    // ui->textEdit->append("文件路径:"+filePath);
    // 文件信息//
    QFileInfo info(filePath);
    // ui->textEdit->append(QString("文件大小:%1 byte").arg(info.size()));
    // ui->textEdit->append(QString("文件名称:%1").arg(info.fileName()));
    // ui->textEdit->append(QString("创建时间:%1").arg(info.created().toString("yyyy-MM-dd hh:mm:ss")));
    // ui->textEdit->append(QString("修改时间:%1").arg(info.lastModified().toString("yyyy-MM-dd hh:mm:ss")));

    ///文件内容//
    //首先设置要使用的编码格式
    QTextCodec * qc = QTextCodec::codecForName("utf-8");
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->textEdit->append("文件打开失败");
        return;
    }
    ui->textEdit->clear();
    QTextStream readStream(&file);

    while(!readStream.atEnd())
    {
        ui->textEdit->append(readStream.readLine());
    }
    connect(ui->textEdit,&QTextEdit::textChanged,this,&OneMarkdown::textEdit_textChanged);
    textEdit_textChanged();
}