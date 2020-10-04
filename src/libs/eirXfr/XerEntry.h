#pragma once
#include "eirXfr.h"

#include <QMap>
#include <QUuid>

#include "XfrEntry.h"
#include "XfrFunctionInfo.h"
#include "XfrLevel.h"

class EIRXFR_EXPORT XerEntry
{
public:
    typedef QMap<QUuid, XerEntry*> UidMap;

public:
    XerEntry();
    ~XerEntry();
    QUuid uid() const { return mUid; }
    XfrLevel level() const;
    QString what() const;
    QString why() const;
    QString where() const;
    QString how() const;

private:
    QUuid mUid;
    XfrLevel mLevel=XfrLevel::level("NoLevel");
    XfrFunctionInfo mFuncInfo;
    QString mWhat;
    QString mWhy;
    QString mWhere;
    QString mHow;

//  ---------------- static ----------------
public:
    static XerEntry at(const QUuid &uid);
    static bool isError();
    static int errorCount();



    static XerEntry from(const char *qFuncInfo, const char *levelName,
                         const QString &what, const QString &why,
                         const QString &where, const QString &how);
 /*
    static XerEntry from(const char *qFuncInfo, const char *levelName,
                              const QStringList names=QStringList(),
                         const QVariantList &vars=QVariantList());
    static XerEntry from(const char *qFuncInfo, const char *levelName,
                              const QString name1, const QVariant &var1,
                              const QString name2=QString(), const QVariant &var2=QVariant(),
                              const QString name3=QString(), const QVariant &var3=QVariant(),
                              const QString name4=QString(), const QVariant &var4=QVariant());
*/
private:
    static UidMap smMap;
};
