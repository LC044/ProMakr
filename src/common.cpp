#include "common.h"
std::string QtoString(QString str)
{
    return str.toStdString();
}
QString toQString(std::string str)
{
    return QString::fromStdString(str);
}

std::string int2str(int num)
{
    return std::to_string(num);
}