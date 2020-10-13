#include "XerEntry.h"

#include <QtDebug>

#include "Debug.h"


XerEntry::XerEntry() : mUid(QUuid::createUuid()) {;}
XerEntry::~XerEntry() {;}

XerEntry XerEntry::from(const char *qFuncInfo, const char *levelName,
                        const QString &what, const QString &why,
                        const QString &where, const QString &how)
{
    TRACEQFI << qFuncInfo << levelName << what << why << where << how;
    XerEntry entry;
    entry.mFuncInfo = XfrFunctionInfo(qFuncInfo);
    entry.mLevel = XfrLevel::level(levelName);
    entry.mWhat = what;
    entry.mWhy = why;
    entry.mWhere = where;
    entry.mHow = how;
    return entry;
}
