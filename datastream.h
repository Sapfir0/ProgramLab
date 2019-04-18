#pragma once

#include <QString>

#include <windef.h>

using Size_t = unsigned long;

class DataStream
{
    private:
        HANDLE file;
        bool endFile;
    public:

        DataStream();
        ~DataStream();
        bool open();
        bool is_open();
        void close();
        bool eof();
        bool write(void* begin, Size_t size);
        bool read(void* begin, Size_t size);

};

DataStream& operator << (DataStream&, QChar);
DataStream& operator << (DataStream&, QString);
DataStream& operator >> (DataStream&, QChar&);
DataStream& operator >> (DataStream&, QString&);

template <typename num_t>
DataStream& operator << (DataStream& stream, num_t value) {
    stream.write(&value, sizeof(value));
    return stream;
}

template <typename num_t>
DataStream& operator >> (DataStream& stream, num_t& value) {
    stream.read(&value, sizeof(value));
    return stream;
}

//#endif // WINDATASTREAM_H
