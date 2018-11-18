#include "fotobase.h"
#include  <QDate>

fotobase::fotobase()
{
    nameOfModel = "";
    category = "Профессиональный";
    analogOrNot = false;
    producer = "Nikon";
    matrixRes = 2.00;
    changeLens = false;
    size = "00-00-00";
    weight = 100;
    cost = 0;
    date.setDate(2000, 1,1);
}

//fotobase fotobase::operator <(fotobase record) {
//    record.category
//}
bool fotobase::operator >(const fotobase &record) {
    return compare(*this, record) > 0;
}
bool fotobase::operator >=(const fotobase &record) {
    return compare(*this, record) >= 0;
}
bool fotobase::operator <=(const fotobase &record) {
    return compare(*this, record) <= 0;
}
bool fotobase::operator <(const fotobase &record) {
    return compare(*this, record) < 0;
}
bool fotobase::operator ==(const fotobase &record) {
    return compare(*this, record) == 0;
}
bool fotobase::operator !=(const fotobase &record) {
    return compare(*this, record) != 0;
}




int fotobase::compare(const fotobase& firstI, const fotobase& secondI)  {
    //if (c1.category!=c2.category) return c1.category - c2.category;
    // Записи упорядочиваются по следующим полям: категория, разрешение матрицы, цена, производитель, модель
    if ( firstI.category != secondI.category )
    {
        if ( firstI.category < secondI.category)
            return  -1;
        else
            return  1;
    }

    if ( firstI.matrixRes != secondI.matrixRes )
    {
        if ( firstI.matrixRes < secondI.matrixRes)
            return  -1;
        else
            return  1;
    }

    if ( firstI.cost != secondI.cost )
    {
        if ( firstI.cost < secondI.cost )
            return  -1;
        else
            return  1;
    }

    if ( firstI.producer != secondI.producer )
    {
        if ( firstI.producer < secondI.producer )
            return  -1;
        else
            return  1;
    }

    if ( firstI.nameOfModel != secondI.nameOfModel )
    {
        if ( firstI.nameOfModel < secondI.nameOfModel )
            return  -1;
        else
            return  1;
    }

        return 0;
}

//void fotobase::lower(const fotobase& firstI, const fotobase& secondI) {
//    // Записи упорядочиваются по следующим полям: категория, разрешение матрицы, цена, производитель, модель

//}


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

void fotobase::setChangeLense(bool changeLenseclass){
     changeLens = changeLenseclass;
}
bool fotobase::getChangeLense(){
    //qDebug() << "Смена линзы: " << changeLens;
    return changeLens;
}

void fotobase::setSize(QString sizeclass){
      size = sizeclass;
}
QString fotobase::getSize(){
    //qDebug() << "Размер: " << size;
    return size;
}
//  int weight;
void fotobase::setWeight(int weightclass){
      weight = weightclass;
}
int fotobase::getWeight(){
    //qDebug() << "Вес: " << weight;
    return weight;
}

void fotobase::setCost(int costclass){
      cost = costclass;
}
int fotobase::getCost(){
    //qDebug() << "Цена: " << cost;
    return cost;
}

void fotobase::setmyDate(QDate dateclass){
      date = dateclass;
}
QDate fotobase::getmyDate(){
   // qDebug() << "Дата: " << date;
    return  date;
}
