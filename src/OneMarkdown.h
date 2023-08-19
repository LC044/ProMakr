#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// #include <QWeb
// #include <QWebChannel>
// #include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEngineView>
#include<QtWebEngine/QtWebEngine>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class OneMarkdown; }
QT_END_NAMESPACE
// QWebEngineView *webView = nullptr;
// QWebChannel *webChannel = nullptr;
class OneMarkdown : public QMainWindow
{
    Q_OBJECT

public:
    OneMarkdown(QWidget *parent = nullptr);
    ~OneMarkdown();

private slots:
    void on_textEdit_textChanged();

    void on_textEdit_selectionChanged();

    void on_textEdit_textEdited();

    void textEdit_textChanged();

    void time_update();
private:
    Ui::OneMarkdown *ui;
    QLabel *statusLabel;
};
#endif // MAINWINDOW_H
