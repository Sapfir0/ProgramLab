#include "pipestream.h"

#include <winbase.h>
#include <filestream.h>
#include <QDebug>


bool PipeStream::open(QString filename, uint32_t flags) {
    DWORD openMode = 0, pipeMode = 0;

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
                         254,
                         1024,
                         1024,
                         5000,
                         nullptr);
    } else {
        FileStream game;
        game.open(filename, flags);
        file = game.getHandle();
        game.setHandle(NULL);
    }

    bool fileOpen = file != INVALID_HANDLE_VALUE;

    if (!fileOpen) {
        qDebug() << "Pipe create error: " << filename;
    }

    return fileOpen;
}
