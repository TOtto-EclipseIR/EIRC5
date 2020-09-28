#include "QtcvConsole.h"

#include <QDateTime>
#include <QString>
#include <QTimer>


#include <eirXfr/Debug.h>

QtcvConsole::QtcvConsole(const Flags flags)
    : Console(flags)
{
    TRACEQFI << QOBJNAME(Console::parent()) << flags;
    CONNECT(this, &QtcvConsole::initialized,
            this, &QtcvConsole::start);
    EMIT(ctord());
    QTimer::singleShot(500, this, &QtcvConsole::initialize);
}

void QtcvConsole::initialize()
{
    TRACEFN;
    EMIT(initialized());
}

void QtcvConsole::start()
{
    TRACEFN;
    writeLine(QString("Hello from %1 at %2").arg(qApp->arguments().first())
              .arg(QDateTime::currentDateTime().toString()));
    writeLine(QString("   Compiled %1 at %2").arg(__DATE__).arg(__TIME__));
}
