#include "OneMarkdown.h"
#include "./ui_OneMarkdown.h"
#include "global.h"
bool IS_FILE_SAVED = false;
QString  CURRENT_FILE="NULL"
void OneMarkdown::on_action_new_file_triggered()
{
}

void OneMarkdown::on_action_open_file_triggered()
{
    // 选择文件对话框/
    disconnect(ui->textEdit, &QTextEdit::textChanged, this, &OneMarkdown::textEdit_textChanged);
    QFileDialog *f = new QFileDialog(this);
    f->setWindowTitle("选择数据文件*.md");
    f->setNameFilter("*.md");
    f->setViewMode(QFileDialog::Detail);

    QString filePath;
    if (f->exec() == QDialog::Accepted)
        filePath = f->selectedFiles()[0];

    // ui->lineEdit->setText(filePath);
    // ui->textEdit->append("文件路径:"+filePath);
    // 文件信息//
    QFileInfo info(filePath);
    // ui->textEdit->append(QString("文件大小:%1 byte").arg(info.size()));
    // ui->textEdit->append(QString("文件名称:%1").arg(info.fileName()));
    // ui->textEdit->append(QString("创建时间:%1").arg(info.created().toString("yyyy-MM-dd hh:mm:ss")));
    // ui->textEdit->append(QString("修改时间:%1").arg(info.lastModified().toString("yyyy-MM-dd hh:mm:ss")));

    /// 文件内容//
    // 首先设置要使用的编码格式
    QTextCodec *qc = QTextCodec::codecForName("utf-8");
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->textEdit->append("文件打开失败");
        return;
    }
    ui->textEdit->clear();
    QTextStream readStream(&file);

    while (!readStream.atEnd())
    {
        ui->textEdit->append(readStream.readLine());
    }
    connect(ui->textEdit, &QTextEdit::textChanged, this, &OneMarkdown::textEdit_textChanged);
    textEdit_textChanged();
}
void OneMarkdown::on_action_save_file_triggered()
{
    if (!IS_FILE_SAVED) // r如果标记为1，证明有文件加载，不然没有不需要保存
    {
        QString filePath;                               // 存储保存路径
        filePath = QFileDialog::getSaveFileName(this, "保存");
        if (filePath.isEmpty())
        {
            QMessageBox::information(this, "信息", "保存失败");
        }
        else
        {
            // 内容保存到路径文件
            QFile file(filePath);

            // 以文本方式打开
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                // todo: 增量保存，优化保存性能
                QTextStream out(&file); // IO设备对象的地址对其进行初始化

                out << ui->textEdit->toPlainText() << endl; // 输出

                QMessageBox::information(this, "文件保存成功", QString("文件保存在%2").arg(filePath));

                file.close();
                IS_FILE_SAVED = true;
            }
            else
            {
                QMessageBox::warning(this, tr("Error"), tr("File to open file!"));
            }
            // QDir *temp = new QDir; // 声明文件对象
            // QMessageBox::information(this, "文件保存成功", QString("文件保存在%2").arg(filePath));
        }
    }
    else
    {
        QMessageBox::information(this, "错误", "保存失败");
    }
}

void OneMarkdown::on_action_new_window_triggered()
{
}

void OneMarkdown::on_action_open_recent_file_triggered()
{
}
