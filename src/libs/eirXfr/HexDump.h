// file: {EIRC2 repo}./src/libs/eirXfr/HexDump.h
#pragma once
#include "eirXfr.h"

#include <QByteArray>
#include <QStringList>
class QImage;

#include <eirType/MultiName.h>

class EIRXFR_EXPORT HexDump
{
public:

public:
    HexDump();
    HexDump(void * data, const int bytes,
            const QString &name=MultiName());
    HexDump(const QByteArray &ba,
            const QString &name=MultiName());
    HexDump(const QImage & img, const int bytes=-1);
    QStringList strings();
    QString string(const QChar &joinChar=QChar('\n'));


private:
    void format();
    QString printable(unsigned u);

private:
    unsigned * mpData=nullptr;
    const int cmBytes=0;
    const QString cmName;
    QStringList mStrings;
};

