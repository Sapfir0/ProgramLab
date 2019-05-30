#pragma once

#include <fotodatabase.h>

#include <server_command.h>

#include <pipestream.h>

#include <map>
#include <memory>

class ServerWorker
{
    private:
        using pipes_t = std::map<clientID_t, std::shared_ptr<PipeStream>>;
        pipes_t* pipes;
        fotoDatabase* db;
        clientID_t clientid;
        bool running = false;
    public:
        ServerWorker();
        ServerWorker(pipes_t& signalPipe, fotoDatabase& database, clientID_t id);
        bool doCommand(ServerCommand command, PipeStream &,PipeStream &);
        int exec();
        void quit();
};
