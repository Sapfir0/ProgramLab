#include "transmitter.h"
#include <windows.h>
#include  <winbase.h>
#include <QString>

transmitter::transmitter()
{

}

bool startServerPipe() {
HANDLE CreateNamedPipe("./config.txt", PIPE_ACCESS_DUPLEX,
                       PIPE_NOWAIT,
                       254, 1024, 1024, 5000, nullptr);
}
