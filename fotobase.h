#ifndef FOTOBASE_H
#define FOTOBASE_H

#include <QString>
#include <QDate>
#include <QDebug>

class fotobase
{
private:
    QString nameOfModel;
    QString category;
    bool analogOrNot;
    QString producer;
    QString/*float*/ matrixRes;
    bool changeLens;
    QString size;
    int weight;
    int cost;
    QDate date;
public:
    fotobase();
    void ourBaseSetter(fotobase writing);
    void ourBaseGetter(fotobase writing);

    void setNameOfModel(QString nameofModelclass){
        nameOfModel = nameofModelclass;
    }
    QString getNameOfModel(){
        //qDebug() << "Имя модели: " << nameOfModel;
        return nameOfModel;
    }

    void setCategory(QString categoryclass){
        category = categoryclass;
    }
    QString getGategory(){
        //qDebug() << "Категория: " << category;
        return category;
    }

    void setAnalogOrNot(int analogOrNotclass){
        analogOrNot = analogOrNotclass;
    }
    bool getAnalogOrNot(){
        //qDebug() << "Цифровой?: " << analogOrNot;
        return analogOrNot;
    }

    void setProducer(QString producerclass){
        producer = producerclass;
    }
    QString getProducer(){
        //qDebug() << "Производитель: " <<  producer;
        return producer;
    }

    void setMatrRes(/*float*/QString matrixResolutionclass){
        matrixRes = matrixResolutionclass;
    }
    QString/*float*/ getMatrRes(){
        //qDebug() << "Разрешение матрицы: " <<  matrixRes;
        return matrixRes;
    }
    //        bool changeLens;
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
