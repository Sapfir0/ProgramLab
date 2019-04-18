#include "datastream.h"

#include <windows.h>
#include <QDebug>
#include <windef.h>

DataStream::DataStream() {
    file = NULL;
}

DataStream::~DataStream() {
    close();
}

bool DataStream::open() {
    if (file != NULL) close();
    file = CreateFileA("./os.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    bool fileOpen = file != INVALID_HANDLE_VALUE;
    return fileOpen;
}


void DataStream::close() {
    CloseHandle(file);
    file = NULL;
}


bool DataStream::read(void* begin, Size_t size) {
    return  ReadFile(file, begin, size, &size, NULL);
}

bool DataStream::write(void* begin, Size_t size) {
    return WriteFile(file, begin, size, &size, NULL);
}

DataStream& operator << (DataStream& stream, QString value) {
    stream << value.size();
    for (auto item : value) {
        stream << item;
    }
    return stream;
}

DataStream& operator << (DataStream& stream, QChar value) {
    stream.write(&value.unicode(), sizeof(value));
    return stream;
}

DataStream& operator >> (DataStream& stream, QString &value) {
    int size;
    stream >> size;
    value.clear();
    value.reserve(size);

    QChar item;
    for (int i = 0; i < size; i++) {
        stream >> item;
        value.push_back(item);
    }

    return stream;
}

DataStream& operator >> (DataStream& stream, QChar &value) {
    uint16_t chr;
    stream.read(&chr, sizeof(chr));
    value = chr;
    return stream;
}


