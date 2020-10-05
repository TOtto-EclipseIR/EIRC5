#include "Console.h"

#include <QFile>

#include <eirXfr/Debug.h>

Console::Console(const ApplicationHelper::Flags flags)
    : ApplicationHelper(flags)
    , mpIn(new QFile(this))
    , mpOut(new QFile(this))
    , mpErr(new QFile(this))
{
    TRACEFN
    TSTALLOC(mpIn);
    TSTALLOC(mpOut);
    TSTALLOC(mpErr);
    setObjectName("Console");
    mpIn->setObjectName("Console:stdin");
    mpOut->setObjectName("Console:stdout");
    mpErr->setObjectName("Console:stderr");
    EXPECT(mpIn->open(stdin, QIODevice::ReadOnly));
    EXPECT(mpOut->open(stdout, QIODevice::WriteOnly));
    EXPECT(mpErr->open(stderr, QIODevice::WriteOnly));
}

bool Console::isForkQtDebug() const
{
    return m_ForkQtDebug;
}

void Console::putChar(const char c)
{
    if (mpIn->putChar(c))
        emit(charPut(c));
    else
        emit(charNotPut(c));
}

void Console::getChar()
{
    char buf[2];
    if (mpIn->getChar(buf))
        emit charGot(buf[0]);
    else
        emit charNotGot();
}

void Console::readLine()
{
    MUSTDO(it);

}

void Console::write(const QString &qs, const bool andFlush)
{
    mpOut->write(qs.toLocal8Bit());
    if (andFlush) mpOut->flush();
}

void Console::writeLine(const QString &qs,
                        const bool andFlush)
{
    write(qs.toLocal8Bit(), false);
    mpOut->write("\n");
    if (andFlush) mpOut->flush();
    if (m_ForkQtDebug) qInfo() << qs;
}

void Console::writeLines(const QStringList &qsl,
                         const bool andFlush,
                         const QString prefix)
{
    foreach (QString qs, qsl) writeLine(prefix + qs, false);
    if (andFlush) mpOut->flush();
}

void Console::writeErr(const QString &qs, const bool andFlush)
{
    mpErr->write(qs.toLocal8Bit());
    mpErr->write("\n");
    if (andFlush) mpErr->flush();
    if (m_ForkQtDebug) qCritical() << qs;
}

void Console::writeErrs(const QStringList &qsl)
{
    foreach (QString qs, qsl) writeErr(qs, false);
    mpErr->flush();
}

void Console::setForkQtDebug(bool mForkQtDebug)
{
    m_ForkQtDebug = mForkQtDebug;
}

void Console::resetForkQtDebug()
{
    m_ForkQtDebug = true;
}
