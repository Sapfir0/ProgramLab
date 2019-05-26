#include "server.h"

#include <QDebug>

#include <pipestream.h>
#include "config_pipe_naming.h"

PipeStream Server::signalOutputPipe(serverSignalsOutputPipeName, WinApiHelper::create | WinApiHelper::out);

Server::Server() : running(false)
{
    qDebug() << "Constructor";
}

int Server::exec() {
    qDebug() << "STARTING THE SERVER";

    PipeStream dataInputPipe, dataOutputPipe, commandInputPipe;

    if (!dataInputPipe.open(serverDataInputPipeName, WinApiHelper::create | WinApiHelper::in) ||
            !dataOutputPipe.open(serverDataOutputPipeName, WinApiHelper::create | WinApiHelper::out) ||
            !commandInputPipe.open(serverCommandInputPipeName, WinApiHelper::create | WinApiHelper::in) ||
            !signalOutputPipe.is_open())
    {
        qCritical() << "Couldn't create pipe";
        return -1;
    }

    qDebug() << "Input pipe has created." << endl << "Waiting for clients.." << endl;

    commandInputPipe.waitingClient();

    qDebug() << "Client has been connected." << endl << endl;


    do {
        ServerCommand c;
        // чтение из потока команд
        commandInputPipe >> c;
        running = this->doCommand(c, dataInputPipe, dataOutputPipe);
    } while (running);

    qDebug() << " FINISHING THE SERVER" << endl << endl;

    return 0;
}


bool Server::doCommand(ServerCommand command, PipeStream &input, PipeStream &output) {
    try {
        switch (command) {
            case ServerCommand::count: {
                qDebug() << "count";
                output << db.count();
                break;
            }
            case ServerCommand::append: {
                qDebug() << "append";
                fotobase value;
                input >> value;
                signalOutputPipe << ClientCommand::append << db.append(value);
                break;
            }
            case ServerCommand::remove: {
                qDebug() << "remove";
                uint id;
                input >> id;
                db.remove(id);
                signalOutputPipe << ClientCommand::remove << id;
                break;
            }
            case ServerCommand::update: {
                qDebug() << "update";
                uint id;
                fotobase value;
                input >> id >> value;
                db.update(id, value);
                signalOutputPipe << ClientCommand::update << id;
                break;
            }
            case ServerCommand::compare_two_records: { //для сортировки
                qDebug() << "compare two record";
                uint first, second;
                input >> first >> second;
                output << db.compareRecordsByID(first, second);
                break;
            }
            case ServerCommand::records: {
                qDebug() << "records";
                auto recs = db.records();
                qDebug() << "size" << recs.size() << "\nwith items";
                output << recs.size();
                for (fotobase item : recs) {
                    output << item;
                    qDebug() << "item: " << item.id;

                }
                break;
            }
            case ServerCommand::record: {
                //qDebug() << "record";
                uint id;
                input >> id;
                output << db.record(id);
                break;
            }
            case ServerCommand::save: {
                qDebug() << "save";
                QString filename;
                input >> filename;
                output << db.save(filename);
                break;
            }
            case ServerCommand::load: {
                qDebug() << "load";
                QString filename;
                input >> filename;
                output << db.load(filename);
                break;
            }
            case ServerCommand::clear: {
                qDebug() << "clear";
                signalOutputPipe << ClientCommand::clear;
                db.clear();
                break;
            }
            case ServerCommand::is_modified: {
                output << db.isModified();
                qDebug() << "if modifies";
                break;
            }
            case ServerCommand::end_connection: {
                qDebug() << "end_connect";
                output << db.isModified();
                return false;
            }
            default: {
                qDebug() << "dont have command: " << long(command);
            }
        }
    } catch (std::runtime_error error) {
        qCritical() << error.what();
        return false;
    }
    return true;
}
