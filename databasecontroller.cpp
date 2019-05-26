#include "databasecontroller.h"

#include <server_command.h>

#include <exception>

#include <QDebug>

#include "config_pipe_naming.h"


DataBaseController::DataBaseController() {
    bool fullConnect = true, hasConnectedStream = false;
    int poputok = 0;
    bool commandOutConnected = false, dataInputConnected = false, dataOutputConnected = false,
            signalInputConnected = false;
    do {
        if (!commandOutConnected)
            commandOutConnected = commandOutputStream.open(clientCommandOutputPipeName, WinApiHelper::out);
        if (!dataInputConnected)
            dataInputConnected = dataInputStream.open(clientDataInputPipeName, WinApiHelper::in);
        if (!dataOutputConnected)
            dataOutputConnected = dataOutputStream.open(clientDataOutputPipeName, WinApiHelper::out);

        fullConnect = commandOutConnected && dataInputConnected && dataOutputConnected;
        if(!signalInputConnected) {
            signalInputConnected = signalInputStream.open(clientSignalsInputPipe)
        }
        hasConnectedStream = commandOutConnected || dataInputConnected || dataOutputConnected;
        poputok++;
    } while (!fullConnect && hasConnectedStream && poputok < 10);
    if (!fullConnect) {
        throw std::runtime_error("error connected to server");
    }
}

DataBaseController::~DataBaseController() {
    if (commandOutputStream.is_open()) {
        qDebug() << "end connection";
        commandOutputStream << ServerCommand::end_connection;
    }
}

int DataBaseController::count() const {
    int count;
    commandOutputStream << ServerCommand::count;
    dataInputStream >> count;
    return count;
}

uint DataBaseController::append(fotobase record) {
    commandOutputStream << ServerCommand::append;
    dataOutputStream << record;
    uint id;
    dataInputStream >> id;
    return id;
}

void DataBaseController::remove(uint id) {
    commandOutputStream << ServerCommand::remove;
    dataOutputStream << id;
}

void DataBaseController::update(uint record_id, fotobase record) {
    commandOutputStream << ServerCommand::update;
    dataOutputStream << record_id << record;
}

fotobase DataBaseController::record(uint id) const {
    fotobase tmp;

    commandOutputStream << ServerCommand::record;
    dataOutputStream << id;
    dataInputStream >> tmp;

    return tmp;
}

QVector<fotobase> DataBaseController::records() {
    QVector<fotobase> tmp;
    int vector_size = 0;
    commandOutputStream << ServerCommand::records;
    dataInputStream >> vector_size;
    tmp.reserve(vector_size);
    for (int i = 0; i < vector_size; i++) {
        fotobase tmp_record;
        dataInputStream >> tmp_record;
        tmp.push_back(tmp_record);
    }
    return tmp;
}

bool DataBaseController::save(QString filename) {
    bool bulk;

    commandOutputStream << ServerCommand::save;
    dataOutputStream << filename;
    dataInputStream >> bulk;

    return bulk;
}

bool DataBaseController::load(QString filename) {
    bool bulk;

    commandOutputStream << ServerCommand::load;
    dataOutputStream << filename;
    dataInputStream >> bulk;

    return bulk;
}

void DataBaseController::clear() {
    commandOutputStream << ServerCommand::clear;
}

bool DataBaseController::isModidfied() const {
    bool res;

    commandOutputStream << ServerCommand::is_modified;
    dataInputStream >> res;

    return res;
}

int DataBaseController::compareRecordsByID(uint first, uint second) {
    int res;

    commandOutputStream << ServerCommand::compare_two_records;
    dataOutputStream << first << second;
    dataInputStream >> res;

    return res;
}
