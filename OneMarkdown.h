#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class OneMarkdown; }
QT_END_NAMESPACE

class OneMarkdown : public QMainWindow
{
    Q_OBJECT

public:
    OneMarkdown(QWidget *parent = nullptr);
    ~OneMarkdown();

private:
    Ui::OneMarkdown *ui;
};
#endif // MAINWINDOW_H
