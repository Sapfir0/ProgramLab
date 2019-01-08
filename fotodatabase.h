#ifndef FOTODATABASE_H
#define FOTODATABASE_H

#include <QList>
#include <QDebug>
#include "fotobase.h"

class fotoDatabase
{
	private:
		QList<fotobase> database;
	public:

		fotoDatabase();


		//4 lab
		void createDatabase();
		void loadDatabase();
		void saveInDatabase();
		void saveDatabaseUs();


		int count() const;
		unsigned int append(fotobase record);
		void remove(unsigned int id);
		void update(unsigned int id, fotobase record);//вроде это//не то
		fotobase& record(uint id);
		QVector<fotobase> records() const;
		bool save(QString filename) const;
		bool load(QString filename);
		void clear();
		bool isModified() const;

		bool isUniqueId(unsigned int id) const;
		unsigned int get_uniqueId() const;
};

#endif // FOTODATABASE_H
