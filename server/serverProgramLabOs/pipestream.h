#pragma once

#include <WinApiHelper.h>

class PipeStream : public WinApiHelper
{
    public:
        PipeStream();
        PipeStream(QString filename, uint32_t flags);
        bool open(QString filename, uint32_t flags);
        bool waitingClient();
};
