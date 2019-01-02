#include "fotodatabase.h"

fotoDatabase::fotoDatabase()
{

}

unsigned int fotoDatabase::append(fotobase writing) {
    //аргумент не возвращается
	unsigned int tem = get_uniqueId();
	writing.id = tem;
	database.append(writing);
	return tem;

}

bool fotoDatabase::save(QString filename) const {
    QFile record(filename);

    if ( !record.open(QIODevice::WriteOnly) ) {
        return false;
    }

    QDataStream stream (&record);
  
    for (QList<fotobase>::const_iterator it = database.begin(); it < database.end(); it++ )
    {
        if (it != database.begin()) stream << "\n";

		    fotobase temp = *it; //тут вроде надо приравнять к значению данного итератора
        stream  << temp.getNameOfModel() << "\n";
        stream  << temp.getGategory() << "\n";
        stream  << temp.getAnalogOrNot()<< "\n";
        stream  << temp.getProducer() << "\n";
        stream << temp.getMatrRes() << "\n";
        stream << temp.getChangeLense() << "\n";
        stream << temp.getSize() << "\n";
        stream << temp.getWeight() << "\n";
        stream << temp.getCost() << "\n";
        stream  << temp.getmyDate();

    }

    if (database.empty()) qDebug() << "я не записал ничего кек";
	else qDebug() << "запись прошла успешно";
    return true;
}

bool fotoDatabase::load(QString filename) {
    QFile database(filename);
    if (!database.open(QIODevice::ReadOnly)) {
        return false;
    }
    QDataStream stream(&database);

    while (!stream.atEnd()) {

        fotobase temporaryClass;
        QString tempString;
        int tempInt;
        bool tempBool;
        double tempDouble;
		QDate tempDate;


        stream >> tempString;
        temporaryClass.setNameOfModel(tempString);

        stream >> tempString;
        temporaryClass.setCategory(tempString);

        stream >> tempBool;
        temporaryClass.setAnalogOrNot(tempBool);

        stream >> tempString;
        temporaryClass.setProducer(tempString);

        stream >> tempDouble;
        temporaryClass.setMatrRes(tempDouble);

        stream >> tempBool;
        temporaryClass.setChangeLense(tempBool);

        stream >> tempString;
        temporaryClass.setSize(tempString);

        stream >> tempInt;
        temporaryClass.setWeight(tempInt);

        stream >> tempString;
        temporaryClass.setCost(tempInt);

        //тут должна быть дата ыы
        srem >> tempDate;
        temporaryClass.setmyDate( tempDate );


    }
    return true;
}

fotobase& fotoDatabase::record(uint id) {
	for (auto& it : database) {
		if (it.id == id) return it;
	}
	throw 0;
}

QVector<fotobase> fotoDatabase::records() const {
	QVector<fotobase> t;
	std::for_each(database.begin(), database.end(), [&t](const fotobase& i){t.push_back(i);});
	return t;
}

int fotoDatabase::count() const {
    return database.size();
}

void fotoDatabase::remove(unsigned int id) {
    //удалить из базы данных запись c заданным идентификатором
	for (auto it = database.end(); it-- != database.end() && it->id != id;)
    if (it != database.end()) database.erase(it);
}

void fotoDatabase::clear() {
    database.clear();
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

	for (auto it : database) {
		if (it.id == id) return false;
	}
    return true;
}









