#pragma once
#include "eirXfr.h"

#include <QSharedDataPointer>

#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QHash>
#include <QUuid>
#include <QVariant>
#include <QVariantList>

#include <eirType/DProperty.h>

#include "XfrLevel.h"

typedef XfrLevel::Level XfrLevelLevel;

#define XFRENTRY_DATAPROPS(TND) \
    TND(qint64, TimeStampUtc, 0) \
    TND(XfrLevelLevel, Level, 0) \
    TND(QString, QFuncInfo, QString()) \
    TND(QString, ClassName, QString()) \
    TND(QString, FunctionName, QString()) \
    TND(QStringList, ArgumentNames, QStringList()) \
    TND(QString, Message, QString()) \
    TND(QString, Format, QString()) \
    TND(QStringList, VarNames, QStringList()) \
    TND(QVariantList, VarList, QVariantList()) \

class XfrEntryData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(XFRENTRY_DATAPROPS)
public:
    XfrEntryData(void)
    {
        DEFINE_DATAPROPS_CTORS(XFRENTRY_DATAPROPS)
    }
};

class EIRXFR_EXPORT XfrEntry
{
    DECLARE_PARENT_DATAPROPS(XFRENTRY_DATAPROPS)
    DECLARE_DATAPROPS(XfrEntry, XfrEntryData)
public:
    QUuid uid() const { return mUid; }
    bool isNull() const;

private:
    QUuid mUid;

//  ---------------- static ----------------

public:
    static XfrEntry at(const QUuid &uid);
    static XfrEntry from(const char *qFuncInfo, const char *levelName,
                              const QStringList names, const QVariantList &vars);
    static XfrEntry from(const char *qFuncInfo, const char *levelName,
                              const QString name1=QString(), const QVariant &var1=QVariant(),
                              const QString name2=QString(), const QVariant &var2=QVariant(),
                              const QString name3=QString(), const QVariant &var3=QVariant(),
                              const QString name4=QString(), const QVariant &var4=QVariant());

private:
    static QHash<QUuid, XfrEntry> smUidEntryHash;
};
