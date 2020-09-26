#include "Settings.h"

#include <QSettings>
#include <QTemporaryDir>
#include <QTemporaryFile>

#include <APP>
#include <eirXfr/Debug.h>

#include "ApplicationHelper.h"

Settings::Settings(QObject *parent)
    : QObject(parent)
{
    TRACEQFI << QOBJNAME(parent);
    mpTempIniFile = new QTemporaryFile(qApp->applicationName()+"XXXXXX.ini", this);
    TSTALLOC(mpTempIniFile);
    mpTempIniFile->setObjectName("SettingsFile:TempIniFile");
    EXPECT(mpTempIniFile->open());
    mpSettings = new QSettings(mpTempIniFile->fileName(), QSettings::IniFormat, this);
}

bool Settings::isNull() const
{
    TRACEQFI << PTRSTRING(mpTempIniFile) << PTRSTRING(mpSettings)
             << (mpTempIniFile ? mpTempIniFile->exists() : false)
             << mLiveMap.isEmpty();
    return nullptr != mpTempIniFile && nullptr != mpSettings
            && ! mpTempIniFile->exists() && mLiveMap.isEmpty();
}

void Settings::insert(const QQFileInfo &iniFileInfo)
{
    TRACEQFI << iniFileInfo;
    QSettings * importSettings = new QSettings(iniFileInfo.absoluteFilePath(),
                                               QSettings::IniFormat, this);
    foreach (Key key, importSettings->allKeys())
        insert(key, importSettings->value(key).toString());
}

void Settings::insert(const QStringList &keyValueStrings)
{
    MUSTDO(it);
    MUSTUSE(keyValueStrings);
}

void Settings::insert(const Settings::Map &keyValueStringMap)
{
    MUSTDO(it);
    MUSTUSE(keyValueStringMap);

}

void Settings::insert(const QSettings::SettingsMap &keyVariantMap)
{
    MUSTDO(it);
    MUSTUSE(keyVariantMap);

}

void Settings::insert(const Settings::Key &key, const Settings::Value &value)
{
    TRACEQFI << key() << value;
    EMIT(imported(key, value));
    set(key, value);
}

bool Settings::contains(const Settings::Key &key) const
{
    return mLiveMap.contains(key);
}

void Settings::set(const Key &key, const Value &valu)
{
    TRACEQFI << key() << valu;
    if (mpSettings->contains(key))
    {
        EMIT(changed(key, valu, value(key)));
    }
    else
    {
        EMIT(created(key, valu));
    }  // TODO see [#11] comment re {EMIT}s
    mpSettings->setValue(key, valu);
    mLiveMap.insert(key, valu);
}

void Settings::set(const QString &key, const QVariant &vari)
{
    MUSTDO(it);
    MUSTUSE(key);
    MUSTUSE(vari);
}

void Settings::setDefault(const Key &key, const Value &valu)
{
    MUSTDO(it);
    MUSTUSE(key);
    MUSTUSE(valu);

}

void Settings::setDefault(const Settings::Key& key, const QVariant &vari)
{
    MUSTDO(it);
    MUSTUSE(key);
    MUSTUSE(vari);

}

void Settings::beginGroup(const Settings::Key &key)
{
    TRACEQFI << key();
    mpSettings->beginGroup(key());
    EMIT(groupChanged(mpSettings->group()));
}

void Settings::endGroup()
{
    TRACEFN;
    mpSettings->endGroup();
    EMIT(groupChanged(mpSettings->group()));
}

Settings::Value Settings::value(const Key &key, const Value &defaultValue) const
{
    return mpSettings->value(key, defaultValue).toString();
}

Settings::Map Settings::extract(const Key groupKey, const bool keepKey) const
{
    Settings::Map extractedMap;
    int nGroupSegments = groupKey.segmentCount();
    foreach (Key key, mLiveMap.keys())
        if (key.startsWith(groupKey))
        {
            Value extractValue = value(key);
            Key extractKey = keepKey ? key : key.firstSegmentsRemoved(nGroupSegments);
            extractedMap.insert(extractKey, extractValue);
        }
    return extractedMap;
}

QStringList Settings::toStringList() const
{
    QStringList qsl;
    foreach (Key key, mLiveMap.keys())
        qsl << QString("%1={%2}").arg(key).arg(value(key));
    return qsl;
}

void Settings::dump() const
{
    dump(mLiveMap);
}

void Settings::dump(const Settings::Map map)
{
    foreach (Key key, map.keys())
        DUMP << key() << "=" << map.value(key);
}

int Settings::signedInt(const QString &key, const signed &defaultValue) const
{
    bool ok = contains(key);
    signed result = value(key).toInt(&ok);
    return ok ? result : defaultValue;
}

unsigned Settings::unsignedInt(const QString &key, const unsigned &defaultValue) const
{
    bool ok = contains(key);
    unsigned result = value(key).toUInt(&ok);
    return ok ? result : defaultValue;
}

qreal Settings::real(const QString &key, const qreal &defaultValue) const
{
    bool ok = contains(key);
    qreal result = value(key).toDouble(&ok);
    return ok ? result : defaultValue;
}

qreal Settings::realPerMille(const QString &key, const int &defaultValue) const
{
    bool ok = contains(key);
    qreal result = value(key).toInt(&ok);
    return qreal(ok ? result : defaultValue) / 1000.0;
}

QString Settings::string(const QString &key, const QString &defaultValue) const
{
    return value(key, defaultValue);
}


#if 0

void Settings::Map::import(const Settings::Map &keyValueStringMap)
{
    foreach (QString key, keyValueStringMap.keys())
        insert(key, keyValueStringMap.value(key));
}

void Settings::Map::operator +=(const Settings::Map &keyValueStringMap)
{
    import(keyValueStringMap);
}

void Settings::Map::setDefault(const QString key, const QVariant &variant)
{
    if ( ! contains(key)) insert(key, variant.toString());
}

QStringList Settings::Map::toStringList() const
{
    QStringList qsl;
    foreach (QString key, keys())
        qsl << QString("%1={%2}").arg(key).arg(value(key));
    return qsl;
}

void Settings::Map::dump() const
{
    foreach (QString d, toStringList()) DUMP << d;
}
#endif
