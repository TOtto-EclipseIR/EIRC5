#include "XfrEntry.h"
DEFINE_DATAPROPS(XfrEntry, XfrEntryData)

#include <QtDebug>

QHash<QUuid, XfrEntry*> XfrEntry::smUidEntryHash;

void XfrEntry::ctor(void)
{
    mUid = QUuid::createUuid();
    smUidEntryHash.insert(uid(), this);
}

void XfrEntry::dtor(void)
{
    smUidEntryHash.remove(uid());
}

bool XfrEntry::isNull() const
{
     return uid().isNull() || 0 == getTimeStampUtc()
             || XfrLevel::level("NoLevel") == getLevel() ;
}

bool XfrEntry::isValidLevel() const
{
    return toLevel().isValid();
}

bool XfrEntry::notValidLevel() const
{
    return ! isValidLevel();
}

XfrLevel::Level XfrEntry::getLevel() const
{
    return XfrLevel::Level(getLevelLevel());
}

void XfrEntry::setLevel(XfrLevel::Level lvl)
{
    setLevelLevel(XfrLevelLevel(lvl));
}

const XfrLevel XfrEntry::toLevel() const
{
    return XfrLevel(getLevel());
}

XfrEntry XfrEntry::at(const QUuid &uid)
{
    return *smUidEntryHash.value(uid);
}

XfrEntry XfrEntry::from(const char *qFuncInfo, const char *levelName,
                        const QStringList names, const QVariantList &vars)
{
    XfrEntry entry;
    QUuid uid = QUuid::createUuid();
    entry.setTimeStampUtc(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch());
    entry.setQFuncInfo(qFuncInfo);
    entry.setLevel(XfrLevel::level(levelName));
    entry.setVarNames(names);
    entry.setVarList(vars);
    smUidEntryHash.insert(uid, &entry);

    qDebug() << QDateTime::fromMSecsSinceEpoch(entry.getTimeStampUtc())
             << entry.getQFuncInfo() << entry.getLevel()
             << XfrLevel::name(entry.getLevel())
             << entry.getVarNames() << entry.getVarList();
                ;
    return entry;
}

XfrEntry XfrEntry::from(const char *qFuncInfo, const char *levelName,
                     const QString name1, const QVariant &var1,
                     const QString name2, const QVariant &var2,
                     const QString name3, const QVariant &var3,
                     const QString name4, const QVariant &var4)
{
    QStringList names;
    QVariantList vars;
    names << name1 << name2 << name3 << name4;
    vars << var1 << var2 << var3 << var4;
    return from(qFuncInfo, levelName, names, vars);
}

