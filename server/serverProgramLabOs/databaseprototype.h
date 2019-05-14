#ifndef DATABASEPROTOTYPE_H
#define DATABASEPROTOTYPE_H

#include <fotobase.h>

#include <QVector>

class DataBasePrototype
{
    public:
        virtual int count() const = 0;
        virtual uint append(fotobase record) = 0;
        virtual void remove(uint id) = 0;
        virtual void update(uint record_id, fotobase record) = 0;
        virtual int compareRecordsByID(uint, uint) = 0;
        virtual fotobase record(uint id) const = 0;
        virtual QVector<fotobase> records() = 0;
        virtual bool save(QString filename) = 0;
        virtual bool load(QString filename) = 0;
        virtual void clear() = 0;
        virtual bool isModidfied() const = 0;
        virtual ~DataBasePrototype(){}
};

#endif // DATABASEPROTOTYPE_H
