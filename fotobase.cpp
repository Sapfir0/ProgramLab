#include "fotobase.h"

fotobase::fotobase()
{

}

void fotobase::setNameOfModel(QString nameofModelclass){
    nameOfModel = nameofModelclass;
}
QString fotobase::getNameOfModel(){
    //qDebug() << "Имя модели: " << nameOfModel;
    return nameOfModel;
}

void fotobase::setCategory(QString categoryclass){
    category = categoryclass;
}
QString fotobase::getGategory(){
    //qDebug() << "Категория: " << category;
    return category;
}


void fotobase::setAnalogOrNot(int analogOrNotclass){
    analogOrNot = analogOrNotclass;
}
bool fotobase::getAnalogOrNot(){
    //qDebug() << "Цифровой?: " << analogOrNot;
    return analogOrNot;
}

void fotobase::setProducer(QString producerclass){
    producer = producerclass;
}
QString fotobase::getProducer(){
    //qDebug() << "Производитель: " <<  producer;
    return producer;
}

void fotobase::setMatrRes(double matrixResolutionclass){
    matrixRes = matrixResolutionclass;
}
double fotobase::getMatrRes(){
    //qDebug() << "Разрешение матрицы: " <<  matrixRes;
    return matrixRes;
}
