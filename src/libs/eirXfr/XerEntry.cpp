#include "XerEntry.h"

#include <QtDebug>

#include "Debug.h"


XerEntry::XerEntry() : mUid(QUuid::createUuid()) {;}
XerEntry::~XerEntry() {;}

void XerEntry::clear()
{
    TRACEFN;
    mUid = QUuid();
    mLevel.clear();
    mFuncInfo.clear();
    mWhat.clear();
    mWhy.clear();
    mWhere.clear();
    mHow.clear();

}

QString XerEntry::toString() const
{
    return QString("%1: %2 %3 %4 %5 @%6")
            .arg(level().name())
            .arg(what())
            .arg(why())
            .arg(where())
            .arg(how())
            .arg(funcInfo());
}

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
