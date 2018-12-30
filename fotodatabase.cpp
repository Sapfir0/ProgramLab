#include "fotodatabase.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QFileDialog>
//#include "fotobase.h"

fotoDatabase::fotoDatabase()
{

}

void fotoDatabase::createDatabase() {

//    QFile database("db.txt");
//    if (database.isOpen()) {

//    }
}

unsigned int fotoDatabase::appender(const fotobase &writing) {
    //аргумент не возвращается
//    unsigned int tem = get_uniqueId();
//    record.insert(tem, writing);
//    record[tem].id = tem;
//    return tem;

}

void fotoDatabase::loadDatabase() {
    nameOfFile = QFileDialog::getOpenFileName(
                0, QString("Открыть базу данных"),
                QString(),QString("Текстовые файлы (*.txt,*.ini);;)"));

    qDebug() << nameOfFile;

}

void fotoDatabase::saveDatabaseUs() {
    QFileDialog::getSaveFileName(0, "Сохранить как",
                                 QString(), QString(".txt, .ini"));
}

void fotoDatabase::saveInDatabase() {
   // QFile db("db.txt");

   // if ( db.open(QIODevice::WriteOnly)) {
//        QDataStream zapis = record[indexOfRecord]; //текущую запушиим
//        db.write(zapis);
//        db.close(); //только теперь запишется

  //  }
}


bool fotoDatabase::save(QString filename) const {
    QFile database(filename);
    if ( !database.open(QIODevice::WriteOnly) ) {
        return false;
    }

    QDataStream strem(&database);
    QList<fotobase>::const_iterator it ; //const не лучше, но так робит

    for (it = record.begin(); it < record.end(); it++ )
    {
        fotobase temp; //тут вроде надо приравнять к значению данного итератора
        strem << temp.getNameOfModel() << "\n";
        strem << temp.getGategory() << "\n";
        strem << temp.getAnalogOrNot()<< "\n";
        strem << temp.getProducer() << "\n";
        strem << temp.getMatrRes() << "\n";
        strem << temp.getChangeLense() << "\n";
        strem << temp.getSize() << "\n";
        strem << temp.getWeight() << "\n";
        strem << temp.getCost() << "\n";
        strem << temp.getmyDate() << "\n" << "\n";
    }
    qDebug() << "я не записал ничего кек";
    return true;
}

bool fotoDatabase::load(QString filename) {
    QFile database(filename);
    if (!database.open(QIODevice::ReadOnly)) {
        return false;
    }
    QDataStream strem(&database);
    while (!strem.atEnd()) {
        fotobase temporaryClass;
        QString tempString;
        int tempInt;
        bool tempBool;
        double tempDouble;

        strem >> tempString;
        temporaryClass.setNameOfModel(tempString);

        strem >> tempString;
        temporaryClass.setCategory(tempString);

        strem >> tempBool;
        temporaryClass.setAnalogOrNot(tempBool);

        strem >> tempString;
        temporaryClass.setProducer(tempString);

        strem >> tempDouble;
        temporaryClass.setMatrRes(tempDouble);

        strem >> tempBool;
        temporaryClass.setChangeLense(tempBool);

        strem >> tempString;
        temporaryClass.setSize(tempString);

        strem >> tempInt;
        temporaryClass.setWeight(tempInt);

        strem >> tempString;
        temporaryClass.setCost(tempInt);

        //тут должна быть дата ыы
        /*
        strem << temp.getmyDate() << "\n" << "\n";*/

    }

}

int fotoDatabase::count() const {
    return record.size();
}

void fotoDatabase::remove(unsigned int id) {
    //удалить из базы данных запись c заданным идентификатором
    record.removeAt(id);
}

void fotoDatabase::clear() {
    record.clear();
}












