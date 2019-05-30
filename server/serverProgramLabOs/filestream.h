#pragma once

#include <WinApiHelper.h>

class FileStream : public WinApiHelper
{
    private:
        //QString filename = "./os.txt";
    public:
        bool open(QString filename, uint32_t flags);
};



//#endif // WINDATASTREAM_H
