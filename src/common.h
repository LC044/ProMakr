#ifndef COMMON_H
#define COMMON_H
#include <string>
#include <QDebug>
std::string QtoString(QString str);
QString toQString(std::string str);
#endif // COMMON_H