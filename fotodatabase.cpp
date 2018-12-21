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

    QFile database("db.txt");
    if (database.isOpen()) {

    }
}

unsigned int fotoDatabase::appender(const fotobase &writing) {
    //аргумент не возвращается
    unsigned int tem = get_uniqueId();
    record.insert(tem, writing);
    record[tem].id = tem;
    return tem;

}

void fotoDatabase::loadDatabase() {
//    QString database = QFileDialog::getOpenFileName(
//                this, QString("Открыть базу данных"),
//                QString(),QString("Текстовые файлы (*.txt,*.bat);;)"));
}

void fotoDatabase::saveInDatabase() {
    QFile db("db.txt");

    if ( db.open(QIODevice::WriteOnly)) {
//        QDataStream zapis = record[indexOfRecord]; //текущую запушиим
//        db.write(zapis);
//        db.close(); //только теперь запишется

    }
}


bool fotoDatabase::isUniqueId(unsigned int id) const {
    if (id == 0)
        return false;
    return record.contains(id);
}

unsigned int fotoDatabase::getUniqueId() const {
    unsigned int id = qrand();
    while (record.contains(id)) {
        id = qrand();
    }
    return id;
}

void fotoDatabase::saveDatabaseUs() {

}


bool fotoDatabase::save(QString filename) const {
    QFile database(filename);
    if ( database.open(QIODevice::ReadOnly)) {
        QTextStream strem(file);
        qDebug() << database.flush();

        if ( database.flush() )
            return true;
    }
    return false;
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
