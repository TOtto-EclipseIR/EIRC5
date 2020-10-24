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
    bool isNull() const             { return XfrLevel::level("NoLevel") == mLevel.level();}
    bool notNull() const            { return ! isNull(); }
    bool isError() const            { return XfrLevel::isError(mLevel.name()); }
    void clear();
    QUuid uid() const               { return mUid; }
    XfrLevel level() const          { return mLevel; }
    QString what() const            { return mWhat; }
    QString why() const             { return mWhy; }
    QString where() const           { return mWhere; }
    QString how() const             { return mHow; }
    QString funcInfo() const        { return mFuncInfo.getPrettyFunction(); }
    QString toString() const;

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
    static int errorCount();

    static XerEntry from(const char *qFuncInfo, const char *levelName,
                         const QString &what, const QString &why=QString(),
                         const QString &where=QString(), const QString &how=QString());
};

#define XRTNERROR(level, what, why, where, how) \

