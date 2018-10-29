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

    void setChangeLense(bool changeLenseclass){
         changeLens = changeLenseclass;
    }
    bool getChangeLense(){
        //qDebug() << "Смена линзы: " << changeLens;
        return changeLens;
    }
    //QString size;
    void setSize(QString sizeclass){
          size = sizeclass;
    }
    QString getSize(){
        //qDebug() << "Размер: " << size;
        return size;
    }
    //  int weight;
    void setWeight(int weightclass){
          weight = weightclass;
    }
    int getWeight(){

        //qDebug() << "Вес: " << weight;
        return weight;
    }
    //int cost;
    void setCost(int costclass){
          cost = costclass;
    }
    int getCost(){
        //qDebug() << "Цена: " << cost;
        return cost;
    }
    //QDate date;
    void setmyDate(QDate dateclass){
          date = dateclass;
    }
    QDate getmyDate(){
        qDebug() << "Дата: " << date;
        return  date;
    }
};


#endif // FOTOBASE_H
