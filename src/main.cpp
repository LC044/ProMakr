#include "OneMarkdown.h"
#include <QTextCodec>
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    system("chcp 65001");
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 9));
    {
#if (QT_VERSION <= QT_VERSION_CHECK(5, 0, 0))
#if _MSC_VER
        QTextCodec *codec = QTextCodec::codecForName("GBK");
#else
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
#endif
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);
#else
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
#endif
    }
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "OneMarkdown_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }

    OneMarkdown w;
    w.show();
    return a.exec();
}
