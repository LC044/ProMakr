#ifndef TABLE_H
#define TABLE_H

#include <QWidget>

namespace Ui {
class table;
}

class table : public QWidget
{
    Q_OBJECT

public:
    explicit table(QWidget *parent = nullptr);
    ~table();

signals:
  void textEntered(const QString& text1, const QString& text2);

private slots:
    void on_certify_Button_clicked();

private:
    Ui::table *ui;
};

#endif // TABLE_H
