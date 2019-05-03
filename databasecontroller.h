#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <databaseprototype.h>
#include <pipestream.h>

class DataBaseController : public DataBasePrototype
{
    private:
        mutable PipeStream commandOutputStream, dataInputStream, dataOutputStream;
    public:
        DataBaseController();
        ~DataBaseController();
        int count() const;
        uint append(fotobase record);
        void remove(uint id);
        void update(uint record_id, fotobase record);
        int compareRecordsByID(uint, uint);
        fotobase record(uint id) const;
        QVector<fotobase> records();
        bool save(QString filename);
        bool load(QString filename);
        void clear();
        bool isModidfied() const;
};

#endif // DATABASECONTROLLER_H
