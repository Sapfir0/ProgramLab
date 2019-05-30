#include "WinApiHelper.h"

#include <windows.h>
#include <QDebug>

WinApiHelper::WinApiHelper() : file(NULL)
{

}

WinApiHelper::~WinApiHelper() {
    close();
}

bool WinApiHelper::is_open() {
    return file != INVALID_HANDLE_VALUE && file != NULL;
}

void WinApiHelper::close() {
    CloseHandle(file);
    file = NULL;
}

bool WinApiHelper::eof() {
    bool rd;
    rd = true;
    return !rd;
}

bool WinApiHelper::read(void* begin, Size_t size) {
    Size_t readByte = size;
    auto bRes = ReadFile(file, begin, size, &readByte, NULL);
    if (!bRes && readByte != size) {
        qDebug() << "fail read";
    }
    return bRes;
}

bool WinApiHelper::write(void* begin, Size_t size) {
    Size_t readByte = size;
    auto bRes = WriteFile(file, begin, size, &readByte, NULL);
    if (!bRes && readByte != size) {
        qDebug() << "fail write";
    }
    return bRes;
}

HANDLE WinApiHelper::getHandle() const {
    return this->file;
}
void WinApiHelper::setHandle(HANDLE newHandle) {
    this->file = newHandle;
}

WinApiHelper& operator << (WinApiHelper& stream, QString value) {
    stream << value.size();
    for (auto item : value) {
        stream << item;
    }
    return stream;
}

WinApiHelper& operator << (WinApiHelper& stream, QChar value) {
    stream.write(&value.unicode(), sizeof(value));
    return stream;
}

WinApiHelper& operator >> (WinApiHelper& stream, QString &value) {
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

WinApiHelper& operator >> (WinApiHelper& stream, QChar &value) {
    uint16_t chr;
    stream.read(&chr, sizeof(chr));
    value = chr;
    return stream;
}
