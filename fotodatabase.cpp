#include "fotodatabase.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>

fotoDatabase::fotoDatabase()
{

}

unsigned int fotoDatabase::append(fotobase writing) {
    //аргумент не возвращается
	unsigned int tem = get_uniqueId();
	writing.id = tem;
	record.append(writing);
	return tem;

}

bool fotoDatabase::save(QString filename) const {
    QFile database(filename);

    if ( !database.open(QIODevice::WriteOnly) ) {
        return false;
    }

    QDataStream srem(&database);
    //QList<fotobase>::const_iterator it ; //const не лучше, но так робит

    for (auto it = record.begin(); it < record.end(); it++ )
    {
        if (it != record.begin()) srem << "\n";

		fotobase temp = *it; //тут вроде надо приравнять к значению данного итератора
        srem << temp.getNameOfModel() << "\n";
        srem << temp.getGategory() << "\n";
        srem << temp.getAnalogOrNot()<< "\n";
        srem << temp.getProducer() << "\n";
        srem << temp.getMatrRes() << "\n";
        srem << temp.getChangeLense() << "\n";
        srem << temp.getSize() << "\n";
        srem << temp.getWeight() << "\n";
        srem << temp.getCost() << "\n";
        srem << temp.getmyDate();

        qDebug() << temp.getNameOfModel();
    }

    if (record.empty()) qDebug() << "я не записал ничего кек";

    return true;
}

bool fotoDatabase::load(QString filename) {
    QFile database(filename);
    if (!database.open(QIODevice::ReadOnly)) {
        return false;
    }
    QDataStream srem(&database);

    while (!srem.atEnd()) {

        fotobase temporaryClass;
        QString tempString;
        int tempInt;
        bool tempBool;
        double tempDouble;
		QDate tempDate;


        srem >> tempString;
        temporaryClass.setNameOfModel(tempString);

        srem >> tempString;
        temporaryClass.setCategory(tempString);

        srem >> tempBool;
        temporaryClass.setAnalogOrNot(tempBool);

        srem >> tempString;
        temporaryClass.setProducer(tempString);

        srem >> tempDouble;
        temporaryClass.setMatrRes(tempDouble);

        srem >> tempBool;
        temporaryClass.setChangeLense(tempBool);

        srem >> tempString;
        temporaryClass.setSize(tempString);

        srem >> tempInt;
        temporaryClass.setWeight(tempInt);

        srem >> tempString;
        temporaryClass.setCost(tempInt);

        //тут должна быть дата ыы
        srem >> tempDate;
        temporaryClass.setmyDate( tempDate );

    }
    return true;
}

int fotoDatabase::count() const {
    return record.size();
}

void fotoDatabase::remove(unsigned int id) {
    //удалить из базы данных запись c заданным идентификатором
	for (auto it = record.end(); it-- != record.end() && it->id != id;)
    if (it != record.end()) record.erase(it);
}

void fotoDatabase::clear() {
    record.clear();
}

unsigned int fotoDatabase::get_uniqueId() const {
    unsigned int id = qrand();
    while (!isUniqueId(id)) {
        id = qrand();
    }
    qDebug() << "new id -" << id;
    return id;
}

bool fotoDatabase::isUniqueId(unsigned int id) const {
    if (id ==0)
        return false;

	for (auto it : record) {
		if (it.id == id) return false;
	}
    return true;
}









