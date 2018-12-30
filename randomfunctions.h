#ifndef RANDOMFUNCTIONS_H
#define RANDOMFUNCTIONS_H

#include <QString>
#include <QDate>
#include <QDebug>
#include <QTime>

bool randomBool()  {
    return 0 + (rand() % (1 - 0 + 1)) == 1;
}

QString randSize() {
    int length = 6;
    QString str;
    str.resize(length);
    for (int s = 0; s < length ; ++s)
        str[s] = ('0' + (qrand() % ('9' - '0')));

    return str;
}

double my_randDouble(double MinValue, double MaxValue)
{//[a,b]
    return (MaxValue - MinValue)*static_cast<double>(qrand())/RAND_MAX + MinValue;
}
int my_rand(int MinValue, int MaxValue) {
    return (MaxValue - MinValue)*static_cast<int>(qrand())/RAND_MAX + MinValue;
}

//template <class T>
int workingRandom(int MinValue, int MaxValue) {
    return static_cast<int>((qrand()%RAND_MAX)%(int)(MaxValue - MinValue) + MinValue);
}


QDate randomDate(QDate data) {

    data.setDate(workingRandom(1755,2100),workingRandom(1,12),workingRandom(1,31));
    return data;
}


#endif // RANDOMFUNCTIONS_H
