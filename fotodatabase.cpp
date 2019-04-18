#include "fotodatabase.h"
#include <QFile>
#include <windows.h>

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

	save(filename);
	return tem;

}


//сохранить данные в заданный файл, возвращает false, если сохранить данные не удалось;
bool fotoDatabase::save(QString filename) {

    HANDLE hFile = CreateFile(TEXT("C://OS//os.txt"), GENERIC_WRITE, 0, NULL,
    OPEN_EXISTING|CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

    if (INVALID_HANDLE_VALUE == hFile) {
        return false;
    }

    moding = false;


    //LPCVOID lpbuff;
    DWORD temp2;
    DWORD data; //сюда записать данные из ui


    //WriteFile(hFile, &data, sizeof (data), &temp2, NULL );

        for (QList<fotobase>::const_iterator it = database.begin(); it < database.end(); it++ )  {
            fotobase temp = *it;
            WriteFile(hFile, &data, sizeof (temp.getNameOfModel()), &temp.getNameOfModel(), NULL );
            WriteFile(hFile, &data, sizeof (data), &temp.getGategory(), NULL );
            WriteFile(hFile, &data, sizeof (data), &temp.getAnalogOrNot(), NULL );
            WriteFile(hFile, &data, sizeof (data), &temp.getProducer(), NULL );
            WriteFile(hFile, &data, sizeof (data), &temp.getMatrRes(), NULL );
            WriteFile(hFile, &data, sizeof (data), &temp.getChangeLense()), NULL );
            WriteFile(hFile, &data, sizeof (data), &temp.getSize(), NULL );
            WriteFile(hFile, &data, sizeof (data), &temp.getWeight(), NULL );
            WriteFile(hFile, &data, sizeof (data), &temp.getCost(), NULL );
            WriteFile(hFile, &data, sizeof (data), &getmyDate().toString(), NULL );
        }
        CloseHandle(hFile);

        if (database.empty())
            qDebug() << "я не записал ничего";
        else
            qDebug() << "запись прошла успешно";

    return true;
}


//загрузить данные из заданного файла; при этом предыдущие данные уничтожаются, возвращает false, если сохранить данные не удалось;
bool fotoDatabase::load(QString filename) {

    qDebug() << "Я хочу высососать данные";

    HANDLE hFile = CreateFile(TEXT("C://OS//os.txt"), GENERIC_READ, 0, NULL,
    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (INVALID_HANDLE_VALUE == hFile) {
        return false;
    }

    moding = false;


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

        CloseHandle(hFile);
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








