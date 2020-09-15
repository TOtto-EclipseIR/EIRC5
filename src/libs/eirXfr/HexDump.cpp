// file: {EIRC2 repo}./src/libs/eirXfr/HexDump.h
#include "HexDump.h"

#include <QByteArray>
#include <QImage>

#include <eirXfr/Debug.h>

HexDump::HexDump()
{
    TRACEFN
}

HexDump::HexDump(void *data, const int bytes,
                 const QString &name)
    : mpData((unsigned *)(data))
    , cmBytes(bytes)
    , cmName(name)
{
    TRACEQFI << name;
    NEEDDO(IT)
}

HexDump::HexDump(const QByteArray &ba, const QString &name)
    : mpData((unsigned *)(ba.data()))
    , cmBytes(ba.size())
    , cmName(name)
{
    TRACEQFI << name;
    NEEDDO(IT   )
}

HexDump::HexDump(const QImage &img, const int bytes)
    : mpData((unsigned *)(img.bits()))
    , cmBytes((bytes < 0) ? img.sizeInBytes() : bytes)
{
    TRACEQFI << img << bytes;
    NEEDDO(it)
}

QStringList HexDump::strings()
{
    TRACEFN
    if (mStrings.isEmpty()) format();
    return mStrings;
}

QString HexDump::string(const QChar &joinChar)
{
    TRACEFN
    return mStrings.join(joinChar);
}

void HexDump::format()
{
    TRACEFN
    QStringList qsl;

    qsl << QString("@0x%2 L%3 0x%4 %1").arg(cmName)
           .arg((ptrdiff_t)(mpData),
                2 * sizeof(unsigned), 16, QChar('0'))
           .arg(cmBytes).arg(cmBytes, 0, 16, QChar('0'));

    unsigned * pData = mpData;
    int offset = 0;
    while (cmBytes > offset)
    {
        unsigned u0 = *pData++;
        unsigned u1 = *pData++;
        QString s0 = printable(u0);
        QString s1 = printable(u1);

        QString twoUnsigned = QString("+%1 0x%2 %3 %4 %5")
                .arg(offset, 8, 10, QChar('0'))
                .arg(u0, 2 * sizeof(unsigned), 16, QChar('0'))
                .arg(u1, 2 * sizeof(unsigned), 16, QChar('0'));
        offset += 4 * sizeof (unsigned);
        qsl << twoUnsigned;
    }

    mStrings = qsl;
}

QString HexDump::printable(unsigned u)
{
    QString r;
    int k = sizeof(unsigned);
    while (k--)
    {
        quint8 byte = u & 0xFF;
        u >>= 1;
        QChar c(byte);
        r += c.isPrint() ? c : '~';
    }
    return r;
}
