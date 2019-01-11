#include "fotodatabase.h"
#include <QFile>

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


//сохранить данные в заданный файл, возвращает false, если сохранить данные не удалось;
bool fotoDatabase::save(QString filename) const {
    QFile record(filename);

    if ( !record.open(QIODevice::WriteOnly) ) {
        return false;
    }

    QTextStream stream (&record);

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
        stream  << temp.getmyDate().toString();
    }

    if (database.empty())
        qDebug() << "я не записал ничего кек";
    else
        qDebug() << "запись прошла успешно";

    return true;
}


//загрузить данные из заданного файла; при этом предыдущие данные уничтожаются, возвращает false, если сохранить данные не удалось;
bool fotoDatabase::load(QString filename) {

    QFile database(filename);
    if (!database.open(QIODevice::ReadOnly)) {
        return false;
    }
    QTextStream stream(&database);

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

        stream >> (int&)tempBool;
        temporaryClass.setAnalogOrNot(tempBool);

        stream >> tempString;
        temporaryClass.setProducer(tempString);

        stream >> tempDouble;
        temporaryClass.setMatrRes(tempDouble);

        stream >> (int&)tempBool;//без этого не робит хех
        temporaryClass.setChangeLense(tempBool);

        stream >> tempString;
        temporaryClass.setSize(tempString);

        stream >> tempInt;
        temporaryClass.setWeight(tempInt);

        stream >> tempString;
        temporaryClass.setCost(tempInt);

        //тут должна быть дата ыы
        stream >> tempString;
        temporaryClass.setmyDate( QDate::fromString(tempString) );


        append(temporaryClass);
    }
    return true;
}

fotobase& fotoDatabase::record(unsigned int id) {//идея в том что ссылку можно читать

    for ( auto& it : database)
    {
        if (it.id == id)
            return it;
    }

    throw 0;//мы кидаем исключение тк такого объекта у нас нет
}

/*заменить запись в базе данных;
возвращается новая позиция записи в соответствии с порядком сортировки:
*/
void fotoDatabase::update(unsigned int id, fotobase record) {

    for ( auto& it : database)
    {
		if (it.id == id) {
            uint newID = it.id;
			it = record;
            it.id = newID;
		}
	}
}


/*возвратить вектор записей, которые должны отображается в браузере,
где fotobase — структура, соответствующая строке браузера
(поля структуры совпадают с колонками барузера, также структура содержат идентификатор записи);*/
QVector<fotobase> fotoDatabase::records() const {
	QVector<fotobase> temp;

    for (auto& i : database) {
        temp.push_back(i);
    };

    return temp;
    //return QVector<fotobase> (database.begin(), database.end());//сосамба куте не могет в стл стайл
}


int fotoDatabase::count() const {
    return database.size();
}


//удалить из базы данных запись c заданным идентификатором
void fotoDatabase::remove(unsigned int id) {
	QList<fotobase>::iterator it;

    for (it = database.begin(); it != database.end() && it->id != id; ++it);//так и должно быть

	if (it != database.end())
		database.erase(it);

}


//уничтожает все данные
void fotoDatabase::clear() {
    database.clear();
}

/*
дает абсолютно уникальный айдишник итему в диапоазоне qrand*/
unsigned int fotoDatabase::get_uniqueId() const {

    unsigned int id = qrand();

    while (!isUniqueId(id)) {
        id = qrand();
    }
    qDebug() << "new id -" << id;
    return id;
}

/*проверяет уникальный ли айди хех*/
bool fotoDatabase::isUniqueId(unsigned int id) const {

    if (id ==0)
        return false;
//фор с диапазоном
    for (auto it : database) {
        if (it.id == id)
            return false;
    }

//    for (auto it = database.begin(); it != database.end(); ++it) {
//        if (it->id == id)
//            return false;
//	}



    return true;
}









