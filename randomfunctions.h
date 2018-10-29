#ifndef RANDOMFUNCTIONS_H
#define RANDOMFUNCTIONS_H

#include <QString>

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
double rand(double b, double e)
{
   return b + (rand() % static_cast<unsigned int>((e - b) * 1000)) / 1000.;
}

#endif // RANDOMFUNCTIONS_H
