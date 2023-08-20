#include "common.h"
std::string QtoString(QString str)
{
    return str.toStdString();
}
QString toQString(std::string str)
{
    return QString::fromStdString(str);
}