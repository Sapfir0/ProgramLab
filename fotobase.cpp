#include "fotobase.h"
#include  <QDate>
#include "randomfunctions.h"

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
    uint id;
}

fotobase::fotobase(const fotobase& f)
{
   //qDebug() << id;
    nameOfModel = f.nameOfModel;
    category = f.category;
    analogOrNot = f.analogOrNot;
    producer = f.producer;
    matrixRes = f.matrixRes;
    changeLens = f.changeLens;
    size = f.size;
    weight = f.weight;
    cost = f.cost;

    id = f.id;
}


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
QString fotobase::getNameOfModel() const{
    return nameOfModel;
}

void fotobase::setCategory(QString categoryclass){
    category = categoryclass;
}
QString fotobase::getGategory() const{
    return category;
}

void fotobase::setAnalogOrNot(int analogOrNotclass){
    analogOrNot = analogOrNotclass;
}
bool fotobase::getAnalogOrNot() const{
    return analogOrNot;
}

void fotobase::setProducer(QString producerclass){
    producer = producerclass;
}
QString fotobase::getProducer() const{
    return producer;
}

void fotobase::setMatrRes(double matrixResolutionclass){
    matrixRes = matrixResolutionclass;
}
double fotobase::getMatrRes() const{
    return matrixRes;
}

void fotobase::setChangeLense(bool changeLenseclass){
     changeLens = changeLenseclass;
}
bool fotobase::getChangeLense() const {
    return changeLens;
}

void fotobase::setSize(QString sizeclass){
      size = sizeclass;
}
QString fotobase::getSize() const{
    return size;
}

void fotobase::setWeight(int weightclass){
      weight = weightclass;
}
int fotobase::getWeight() const{
    return weight;
}

void fotobase::setCost(int costclass){
      cost = costclass;
}
int fotobase::getCost() const{
    return cost;
}

void fotobase::setmyDate(QDate dateclass){
      date = dateclass;
}
QDate fotobase::getmyDate() const{
    return  date;
}




fotobase fotobase::randomix( ) {

    fotobase write;
    QStringList categoryList = { "Профессиональный", "Любительский", "Полупрофессиональный"};
    QStringList producerList = { "Nikon", "Panasonic", "Sony", "Canon", "Olympus", "Зенит" }; //самодокуентирующийся код
    QStringList nameOfModelList = { "GH-4", "TY-3", "Cyber-shot DSC-RX100", "Revolution", "X-A5", "EOS 77D", "TG-5", "Pen E-PL9" };
    QVector<double> resolution = { 2.45, 5.67, 16,73, 12.6, 11.23, 32.12};
    QTime now = QTime::currentTime();
    qsrand( now.msec() ); //угадай что это такое

    QString strCategory = categoryList.at(rand()%categoryList.size());
    bool changeLens;

    if (strCategory == categoryList.at(2))
        changeLens = randomBool();
    else
        changeLens = false;

    double whatismatrres;
    bool analogOrNot = randomBool();
    if ( analogOrNot == true)
        whatismatrres = resolution.at(qrand()%resolution.size());
    else
        whatismatrres = 2.0;


    QDate mydata;
    mydata = randomDate(mydata);

    write.setNameOfModel( nameOfModelList.at( rand() % nameOfModelList.size()) );
    write.setCategory ( strCategory);
    write.setAnalogOrNot ( analogOrNot);
    write.setProducer ( producerList.at(rand() % producerList.size() ) );
    write.setMatrRes ( whatismatrres );
    write.setChangeLense ( changeLens );
    write.setSize ( randSize() );
    write.setWeight ( qrand() % 8000 + 100);
    write.setCost ( qrand() % 150000  + 1000  );
    write.setmyDate ( mydata);

    return write;
}
