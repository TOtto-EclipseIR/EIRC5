#pragma once
#include "eirExe.h"

#include <QList>
#include <QString>

#include "ArgumentType.h"
class EIREXE_EXPORT ArgumentItem
{
public:
    typedef QList<ArgumentItem> List;

public:
    ArgumentItem(const ArgumentType &argType,
                 const QString &string);
    QString toString() const;
    QString operator ()() const;

private:
    const ArgumentType cmType;
    const QString cmString;
};

