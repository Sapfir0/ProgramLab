#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

//#include <databaseprototype.h>
#include "fotobase.h"
#include <server_command.h>

#include <pipestream.h>
#include <thread.h>
#include <QObject>

class DataBaseController : public QObject
{
    Q_OBJECT
    private:
        class ServerSignalChecker;
        mutable PipeStream commandOutputStream, dataInputStream, dataOutputStream,  signalInputStream;
        Thread chekingSignal;
        QThread* checkerThread;
        ServerSignalChecker* checker;
    public:
        DataBaseController();
        ~DataBaseController();
        int count() const;
        void append(fotobase record);
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
           void remove_signal(uint);
           void clear_signal();
           void server_stop_signal();
           // этот сигнал требуется для чекера чтобы мы могли требовать считывать тогда когда как бы этого захотим
            void checking_next_signal();
        private slots:
            void serverSignaled(ClientCommand);


};

class DataBaseController::ServerSignalChecker : public QObject
{
        Q_OBJECT
    private:
        PipeStream& signalInputStream;
    public:
        explicit ServerSignalChecker(PipeStream& input);
    public slots:
        void start();
    signals:
        void check_command(ClientCommand);
};


#endif // DATABASECONTROLLER_H
