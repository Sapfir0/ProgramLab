#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

//#include <databaseprototype.h>

#include <pipestream.h>
#include <thread.h>
#include <QObject>

class DataBaseController : public QObject, public DataBasePrototype
{
    Q_OBJECT
    private:
        mutable PipeStream commandOutputStream, dataInputStream, dataOutputStream,  signalInputStream;
        Thread chekingSignal;
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

    signals:
           void update_signal(uint);
           void append_signal(uint);


};

#endif // DATABASECONTROLLER_H
