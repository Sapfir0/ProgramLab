#ifndef FOTOBASE_H
#define FOTOBASE_H

#include <QDate>
#include <QDebug>
#include <datastream.h>


class fotobase
{
private:

    QString nameOfModel; //Название модели
    QString category; //Категория
    bool analogOrNot; //Цифровой
    QString producer; //Изготовитель
    double matrixRes; //Разрешение матрицы
    bool changeLens; //Сменная линза
    QString size; //Размер
    int weight; //Вес
    int cost; //Цена
    QDate date; //Дата


public:
    fotobase();
    fotobase(const fotobase& f);

    unsigned int id;

    static int compare(const fotobase&, const fotobase&);
    bool operator <(const fotobase&);
    bool operator >(const fotobase&);
    bool operator <=(const fotobase&);
    bool operator >=(const fotobase&);
    bool operator ==(const fotobase&);
    bool operator !=(const fotobase&);
   // void operator =(fotobase write);


    static fotobase randomix();

    void setNameOfModel(QString nameofModelclass);
    QString getNameOfModel() const;

    void setCategory(QString categoryclass);
    QString getGategory() const;

    void setAnalogOrNot(int analogOrNotclass);
    bool getAnalogOrNot() const;

    void setProducer(QString producerclass);
    QString getProducer() const;

    void setMatrRes(double matrixResolutionclass);
    double getMatrRes() const;

    void setChangeLense(bool changeLenseclass);
    bool getChangeLense() const;

    void setSize(QString sizeclass);
    QString getSize() const;

    void setWeight(int weightclass);
    int getWeight() const;

    void setCost(int costclass);
    int getCost() const;

    void setmyDate(QDate dateclass);
    QDate getmyDate()  const;
};


DataStream& operator << (DataStream&, fotobase);
DataStream& operator >> (DataStream&, fotobase&);

#endif // FOTOBASE_H
