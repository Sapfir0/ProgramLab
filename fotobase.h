#ifndef FOTOBASE_H
#define FOTOBASE_H

#include <QString>
#include <QDate>
#include <QDebug>

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
    static int compare(const fotobase&, const fotobase&);
    bool operator <(const fotobase);
    bool operator >(const fotobase);
    bool operator <=(const fotobase);
    bool operator >=(const fotobase);
    bool operator ==(const fotobase);
    bool operator !=(const fotobase);
   // void operator =(fotobase write);

    void setNameOfModel(QString nameofModelclass);
    QString getNameOfModel();

    void setCategory(QString categoryclass);
    QString getGategory();

    void setAnalogOrNot(int analogOrNotclass);
    bool getAnalogOrNot();

    void setProducer(QString producerclass);
    QString getProducer();

    void setMatrRes(double matrixResolutionclass);
    double getMatrRes();

    void setChangeLense(bool changeLenseclass);
    bool getChangeLense();

    void setSize(QString sizeclass);
    QString getSize();

    void setWeight(int weightclass);
    int getWeight();

    void setCost(int costclass);
    int getCost();

    void setmyDate(QDate dateclass);
    QDate getmyDate();
};


#endif // FOTOBASE_H
