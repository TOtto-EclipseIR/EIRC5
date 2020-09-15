#include "StdStreams.h"

#include <QTextStream>

StdStreams::StdStreams(QObject *parent)
    : QObject(parent)
    , mpStdin(new QTextStream(stdin, QIODevice::ReadOnly))
    , mpStdout(new QTextStream(stdout, QIODevice::WriteOnly))
    , mpStderr(new QTextStream(stderr, QIODevice::WriteOnly))
{
    setObjectName("StdStreams");
}

QTextStream *StdStreams::in()
{
    return mpStdin;
}

QTextStream *StdStreams::out()
{
    return mpStdout;
}

QTextStream *StdStreams::err()
{
    return mpStderr;
}
