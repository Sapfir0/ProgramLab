#include "WinApiHelper.h"

#include <windows.h>
#include <QDebug>
#include <windef.h>

WinApiHelper::WinApiHelper() {
    file = NULL;
}

WinApiHelper::~WinApiHelper() {
    close();
}

bool WinApiHelper::open() {
    if (file != NULL) close();
    file = CreateFileA("./os.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    bool fileOpen = file != INVALID_HANDLE_VALUE;
    return fileOpen;
}


void WinApiHelper::close() {
    CloseHandle(file);
    file = NULL;
}


bool WinApiHelper::read(void* begin, Size_t size) {
    return  ReadFile(file, begin, size, &size, NULL);
}

bool WinApiHelper::write(void* begin, Size_t size) {
    return WriteFile(file, begin, size, &size, NULL);
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


