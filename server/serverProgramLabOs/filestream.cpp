#include "filestream.h"
#include <winbase.h>
#include <QDebug>


bool FileStream::open(QString filename, uint32_t flags) {
    if (file != NULL) close();
    file = CreateFileA("./os.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    bool fileOpen = file != INVALID_HANDLE_VALUE;
    return fileOpen;
}
