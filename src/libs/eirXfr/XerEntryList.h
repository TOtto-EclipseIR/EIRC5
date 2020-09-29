#pragma once
#include "eirXfr.h"

#include "XerEntry.h"
#include "XfrFilter.h"

class XerEntryList
{
public:
    XerEntryList(const QString &name=QString());
    QUuid collect(const XerEntry &entry);
    XerEntry entry(const int index);
    QString name() const;

    bool isError() const;
    int errorCount() const;
    UidList filter(const XfrFilter &xf);
    void clear(const int index);
    void clear(const XfrFilter &xf);
    void clearAll();

private:
    const QString cmName;
    UidList mErrorUidList;
};

