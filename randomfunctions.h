#ifndef RANDOMFUNCTIONS_H
#define RANDOMFUNCTIONS_H

#include <QString>
#include <QDate>
#include <QDebug>

bool randomBool()  {
    return 0 + (rand() % (1 - 0 + 1)) == 1;
}


void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

QString randString(int len)
{
    QString str;
    str.resize(len);
    for (int s = 0; s < len ; ++s)
        str[s] = QChar('A' + char(qrand() % ('Z' - 'A')));

    return str;
}
QString randSize() {
    int length = 6;
    QString str;
    str.resize(length);
    for (int s = 0; s < length ; ++s)
        str[s] = ('0' + (qrand() % ('9' - '0')));

    return str;
}

double my_rand(double MinValue, double MaxValue)
{//[a,b]
    return (MaxValue - MinValue)*static_cast<double>(qrand())/RAND_MAX + MinValue;
}
int my_rand(int MinValue, int MaxValue) {
    return (MaxValue - MinValue)*static_cast<int>(qrand())/RAND_MAX + MinValue;
}

QDate randomDate(QDate data) {
    data.setDate(my_rand(1755,2100),my_rand(1,12),my_rand(1,31));
    return data;
}


#endif // RANDOMFUNCTIONS_H
