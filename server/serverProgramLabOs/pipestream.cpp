#include "pipestream.h"

#include <winbase.h>
#include <filestream.h>
#include <QDebug>

bool PipeStream::open(QString filename, uint32_t flags) {
    DWORD openMode = 0, pipeMode = 0;
    DWORD bufferSizeIn = 1024, bufferSizeOut = 1024, maxInstances = 254, timeOut = 5000;


    pipeMode = PIPE_TYPE_MESSAGE | PIPE_WAIT;
    pipeMode |= PIPE_READMODE_MESSAGE;
    if (flags & io::in) {
        openMode |= PIPE_ACCESS_INBOUND;
    }
    if (flags & io::out) {
        openMode |= PIPE_ACCESS_OUTBOUND;
    }


    if (flags & io::create) {
        file = CreateNamedPipeA(filename.toStdString().c_str(),
                         openMode,
                         pipeMode,
                         maxInstances,
                         bufferSizeIn,
                         bufferSizeOut,
                         timeOut,
                         nullptr);
    } else {
        FileStream game;
        game.open(filename, flags);
        file = game.getHandle();
        game.setHandle(NULL);
    }


    bool fileOpen = file != INVALID_HANDLE_VALUE;

    if (!fileOpen) {
        //qDebug() << "Pipe create error: " << filename;
    }

    return fileOpen;
}

bool PipeStream::waitingClient() {
    return ConnectNamedPipe(file, nullptr);
}
