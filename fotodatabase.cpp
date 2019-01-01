#include "fotodatabase.h"

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

    QDataStream stream(&database);

    for (QList<fotobase>::const_iterator it = record.begin(); it < record.end(); it++ )
    {
        fotobase temp = *it; //тут вроде надо приравнять к значению данного итератора

        stream << temp.getNameOfModel() << "\n";
        stream << temp.getGategory() << "\n";
        stream << temp.getAnalogOrNot()<< "\n";
        stream << temp.getProducer() << "\n";
        stream << temp.getMatrRes() << "\n";
        stream << temp.getChangeLense() << "\n";
        stream << temp.getSize() << "\n";
        stream << temp.getWeight() << "\n";
        stream << temp.getCost() << "\n";
        stream << temp.getmyDate() << "\n" << "\n";
        qDebug() << temp.getNameOfModel();
    }

    if (record.empty())
        qDebug() << "я не записал ничего кек";

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
//        stream >> tempString;
//        temporaryClass.setmyDate(QString::to(tempString) );

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









