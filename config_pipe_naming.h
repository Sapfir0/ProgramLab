#ifndef CONFIG_PIPE_NAMING_H
#define CONFIG_PIPE_NAMING_H

#include <QString>

const QString
serverDataInputPipeName = "\\\\.\\pipe\\dataInputPipe",
serverDataOutputPipeName = "\\\\.\\pipe\\dataOutputPipe",
serverCommandInputPipeName = "\\\\.\\pipe\\commandInputPipe",
serverSignalsOutputPipeName = "\\\\.\\pipe\\signalsOutputPipe"
;

const QString
clientDataInputPipeName = "\\\\.\\pipe\\dataOutputPipe",
clientDataOutputPipeName = "\\\\.\\pipe\\dataInputPipe",
clientCommandOutputPipeName = "\\\\.\\pipe\\commandInputPipe",
clientSignalsInputPipeName = "\\\\.\\pipe\\signalsOutputPipe"
;

#endif // CONFIG_PIPE_NAMING_H


