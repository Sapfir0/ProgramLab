#ifndef FOTODATABASE_H
#define FOTODATABASE_H

#include <QList>
#include "fotobase.h"

class fotoDatabase
{
private:
   QList<fotobase> record;
   //unsigned int id;
   QString nameOfFile;

public:
    fotoDatabase();


    //4 lab


    void createDatabase();
    void loadDatabase();
    void saveInDatabase();
    void saveDatabaseUs();


    int count() const;
    int append(fotobase &record);
    void remove(unsigned int id);
    int update(unsigned int id, const QString &name, const QString &value);//вроде это
    //void record(uint id, fotobase &record) const;
    //const QVector<S> records() const;//пока хз как делать
    bool save(QString filename) const;
    bool load(QString filename);
    void clear();
    bool isModified() const;

    bool isUniqueId(unsigned int id) const;
    unsigned int get_uniqueId() const;
    unsigned int appender(const fotobase &writing);
};

#endif // FOTODATABASE_H
