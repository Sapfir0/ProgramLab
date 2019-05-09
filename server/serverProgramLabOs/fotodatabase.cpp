#include "fotodatabase.h"
#include <QFile>
#include "filestream.h"

fotoDatabase::fotoDatabase()
{
    id =0;
    moding = false;
    load("./database.db");

}

fotoDatabase::~fotoDatabase() {
    save(filename); //тут косяк
}

int fotoDatabase::compareRecordsByID(uint first, uint second) {
    return fotobase::compare(this->record(first),this->record(second));

}

unsigned int fotoDatabase::append(fotobase writing) {
    moding = true;
	unsigned int tem = get_uniqueId();
	writing.id = tem;
	database.append(writing);

    //save(filename); //тут косяк
	return tem;

}

//сохранить данные в заданный файл, возвращает false, если сохранить данные не удалось;
bool fotoDatabase::save(QString filename) {

    FileStream stream;
    if (stream.open(filename, FileStream::out | FileStream::trunc)) {
        qDebug() << "file saved";
    } else {
        qDebug() << "file save error";
        qDebug() << "file:" << filename << "not created";
        return false;
    }
      stream << database.size();

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


    moding=false;
    return true;
}


//загрузить данные из заданного файла; при этом предыдущие данные уничтожаются, возвращает false, если сохранить данные не удалось;
bool fotoDatabase::load(QString filename) {
    FileStream stream;
    if(!stream.open(filename, FileStream::in)) {
        qDebug() << "file:" << filename << " not opened";
        return false; // если файл не открылся
    }

    int size;
    stream >> size;
        for (int i = 0; i < size; i++) {

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
	save(filename);
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

    save(filename);

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








