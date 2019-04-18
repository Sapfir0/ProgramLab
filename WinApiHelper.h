#pragma once

#include <QString>

#include <windef.h>

using Size_t = unsigned long;

class WinApiHelper
{
    private:
        HANDLE file;
        bool endFile;
    public:

        WinApiHelper();
        ~WinApiHelper();
        bool open();
        bool is_open();
        void close();
        bool eof();
        bool write(void* begin, Size_t size);
        bool read(void* begin, Size_t size);

};

WinApiHelper& operator << (WinApiHelper&, QChar);
WinApiHelper& operator << (WinApiHelper&, QString);
WinApiHelper& operator >> (WinApiHelper&, QChar&);
WinApiHelper& operator >> (WinApiHelper&, QString&);

template <typename num_t>
WinApiHelper& operator << (WinApiHelper& stream, num_t value) {
    stream.write(&value, sizeof(value));
    return stream;
}

template <typename num_t>
WinApiHelper& operator >> (WinApiHelper& stream, num_t& value) {
    stream.read(&value, sizeof(value));
    return stream;
}

//#endif // WINWinApiHelper_H
