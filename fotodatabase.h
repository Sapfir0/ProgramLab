#ifndef FOTODATABASE_H
#define FOTODATABASE_H

#include <QList>
#include "fotobase.h"

class fotoDatabase
{
public:
    fotoDatabase();

    //4 lab

    QList<fotobase> record;

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
};

#endif // FOTODATABASE_H
