// file: {EIRC2 Repo}./src/libs/eirExe/FileName.h
#pragma once
#include "eirExe.h"

#include <QDateTime>
#include <QString>

class EIREXE_EXPORT FileName
{
public:
    FileName(const QString &qstr=QString());
    void set(const QString &qstr,
             const QDateTime &dateTime);
    void setBase(const QString &qstr);
    void setCurrent(const QString &qstr);
    QString toString(const QString &format=QString()) const;
    operator QString () const;
    QString operator ()() const;

private:
    QString mString;
    QDateTime mDateTime;
    static QDateTime smBaseDateTime;
};

