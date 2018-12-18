#include "fotodatabase.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QFileDialog>

fotoDatabase::fotoDatabase()
{

}

void fotoDatabase::createDatabase() {

    QFile database("db.txt");
    if (database.isOpen()) {

    }
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

void fotoDatabase::saveDatabaseUs() {

}


bool fotoDatabase::save(QString filename) const {
    QFile database(filename);
    if ( database.isOpen()) {

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
