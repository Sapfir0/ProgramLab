#include "fotobase.h"

fotobase::fotobase()
{

}
void fotobase::ourBaseSetter(fotobase writing) {
    qDebug() << "sstop it";
//    writing.getNameOfModel();
//    writing.getGategory();
//    writing.getAnalogOrNot();
//    writing.getProducer();
//    writing.getMatrRes();
//    writing.getChangeLense();
//    writing.getSize();
//    writing.getWeight();
//    writing.getCost();
//    writing.getmyDate();
}
void fotobase::ourBaseGetter(fotobase writing) {
    writing.getNameOfModel();
    writing.getGategory();
    writing.getAnalogOrNot();
    writing.getProducer();
    writing.getMatrRes();
    writing.getChangeLense();
    writing.getSize();
    writing.getWeight();
    writing.getCost();
    writing.getmyDate();
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

void fotobase::setMatrRes(/*float*/QString matrixResolutionclass){
    matrixRes = matrixResolutionclass;
}
QString/*float*/ fotobase::getMatrRes(){
    //qDebug() << "Разрешение матрицы: " <<  matrixRes;
    return matrixRes;
}
