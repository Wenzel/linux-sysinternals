#ifndef CONVERT_H
#define CONVERT_H

#include <QString>

#define TOQSTRING(std_string) \
    QString::fromUtf8(std_string.data(), std_string.size())


#endif // CONVERT_H
