#pragma once

#include <WinApiHelper.h>

class PipeStream : public WinApiHelper
{
    private:
         int type = 0;
    public:
        PipeStream();
        PipeStream(QString filename, uint32_t flags);
        bool open(QString filename, uint32_t flags);
        bool waitingClient();
        void close();
};
