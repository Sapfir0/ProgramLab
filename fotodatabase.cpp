#include "fotodatabase.h"
#include <QFile>

fotoDatabase::fotoDatabase()
{
    id =0;
    moding = false;

}

unsigned int fotoDatabase::append(fotobase writing) {
    moding = true;
	unsigned int tem = get_uniqueId();
	writing.id = tem;
	database.append(writing);
	return tem;

}


//сохранить данные в заданный файл, возвращает false, если сохранить данные не удалось;
bool fotoDatabase::save(QString filename) {
    QFile record(filename);

        if ( !record.open(QIODevice::WriteOnly) ) {
            return false;
        }
        moding = false;

        QDataStream stream (&record);

        for (QList<fotobase>::const_iterator it = database.begin(); it < database.end(); it++ )
        {

            fotobase temp = *it;
            stream  << temp.getNameOfModel();
            stream  << temp.getGategory() ;
            stream  << temp.getAnalogOrNot();
            stream  << temp.getProducer() ;
            stream << temp.getMatrRes() ;
            stream << temp.getChangeLense() ;
            stream << temp.getSize() ;
            stream << temp.getWeight() ;
            stream << temp.getCost() ;
            stream  << temp.getmyDate().toString();

        }

        if (database.empty())
            qDebug() << "я не записал ничего";
        else
            qDebug() << "запись прошла успешно";

    return true;
}


//загрузить данные из заданного файла; при этом предыдущие данные уничтожаются, возвращает false, если сохранить данные не удалось;
bool fotoDatabase::load(QString filename) {
    QFile database(filename);
    moding = false;
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

            stream >> tempInt;
            temporaryClass.setCost(tempInt);

            stream >> tempString;
            temporaryClass.setmyDate( QDate::fromString(tempString) );

            this->append(temporaryClass);
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

void fotoDatabase::update(unsigned int id, fotobase record) {
    moding = true;

	for ( auto& it : database)
    {
		if (it.id == id) {
			uint tid = it.id;
			it = record;
			it.id = tid;
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
    //return QVector<fotobase> (database.begin(), database.end());//:(
}


int fotoDatabase::count() const {
    return database.size();
}


//удалить из базы данных запись c заданным идентификатором
void fotoDatabase::remove(unsigned int id) {
    moding = true;

	QList<fotobase>::iterator it;

    for (it = database.begin(); it != database.end() && it->id != id; ++it);//так и должно быть

	if (it != database.end())
		database.erase(it);

}


//уничтожает все данные
void fotoDatabase::clear() {
    moding=true;
    database.clear();
}


unsigned int fotoDatabase::get_uniqueId()  {
    qDebug() << id;
    return id++;
}


bool fotoDatabase::isUniqueId(unsigned int id) const { //не юзается, но мб

    if (id ==0)
        return false;

    for (auto it = database.begin(); it != database.end(); ++it) {
        if (it->id == id) return false;

	}

    return true;
}


bool fotoDatabase::isModified() const {
    return moding;
}








