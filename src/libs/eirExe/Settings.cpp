#include "Settings.h"

#include <QTemporaryDir>
#include <QTemporaryFile>

#include <APP>
#include <eirXfr/Debug.h>

#include "ApplicationHelper.h"

Settings::Settings(QObject *parent)
    : QSettings((new QTemporaryFile(qApp->applicationName()+"XXXXXX.ini"))->fileName(),  QSettings::IniFormat, parent)
{
    TRACEQFI << QOBJNAME(parent);
//    mpTempIniFile = new QTemporaryFile(qApp->applicationName()+"XXXXXX.ini", this);
  //  TSTALLOC(mpTempIniFile);
    //mpTempIniFile->setObjectName("SettingsFile:TempIniFile");
    //EXPECT(mpTempIniFile->open());
    //this = new QSettings(mpTempIniFile->fileName(), QSettings::IniFormat, this);
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

void Settings::insert(const Settings::Key &key, const Settings::Value &valu)
{
    TRACEQFI << key() << valu;
    EMIT(importing(key, valu));
    set(key, valu);
}

bool Settings::contains(const Settings::Key &key) const
{
    return QSettings::contains(key);
}

void Settings::set(const Key &key, const Value &valu)
{
    TRACEQFI << key() << valu;
    if (this->contains(key))
    {
        EMIT(changing(key, valu, get(key)));
    }
    else
    {
        EMIT(creating(key, valu));
    }  // TODO see [#11] comment re {EMIT}s
    QSettings::setValue(key, valu);
}

void Settings::set(const Settings::Key &key, const QVariant &vari)
{
    MUSTDO(it);
    MUSTUSE(key);
    MUSTUSE(vari);
}

void Settings::setValue(const QString &key, const QVariant &vari)
{
    TRACEQFI << key << vari;
    if (this->contains(key))
    {
        EMIT(changing(key, vari.toString(), get(key)));
    }
    else
    {
        EMIT(creating(key, vari.toString()));
    }  // TODO see [#11] comment re {EMIT}s
    QSettings::setValue(key, vari);
}

void Settings::remove(const QString &key)
{
    TRACEQFI << key << QSettings::contains(key);
    if ( ! QSettings::contains(key))    return;     /* /========\ */
    EMIT(removing(key, get(key)));
    QSettings::remove(key);
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
    QSettings::beginGroup(key());
    EMIT(groupChanging(QSettings::group()));
}

void Settings::endGroup()
{
    TRACEFN;
    QSettings::endGroup();
    EMIT(groupChanging(QSettings::group()));
}

Settings::Value Settings::get(const Key &key, const Value &defaultValu) const
{
    TRACEQFI << key() << defaultValu;
    EMIT(getting(key, QSettings::value(key, defaultValu).toString())) ;
    return QSettings::value(key, defaultValu).toString();
}

QVariant Settings::value(const Settings::Key &key, const QVariant &defaultVari) const
{
    TRACEQFI << key() << defaultVari;
    EMIT(getting(key, QSettings::value(key(), defaultVari).toString()));
    return QSettings::value(key(), defaultVari);
}

MultiName::List Settings::keys() const
{
    MultiName::List mnl;
    foreach (QString key, QSettings::allKeys())
        mnl << MultiName(key);
    return mnl;
}

Settings::Map Settings::extract(const Key groupKey, const bool keepKey) const
{
    Settings::Map extractedMap;
    int nGroupSegments = groupKey.segmentCount();
    foreach (Key key, keys())
        if (key.startsWith(groupKey))
        {
            Value extractValue = get(key);
            Key extractKey = keepKey ? key : key.firstSegmentsRemoved(nGroupSegments);
            extractedMap.insert(extractKey, extractValue);
        }
    return extractedMap;
}

QStringList Settings::toStringList(const Key &groupKey)
{
    QStringList qsl;
    if ( ! groupKey.isEmpty()) beginGroup(groupKey);
    foreach (Key key, keys())
        qsl << QString("%1={%2}").arg(key).arg(get(key));
    if ( ! groupKey.isEmpty()) endGroup();
    return qsl;
}

QStringList Settings::toStringList(const QSettings::SettingsMap &map)
{
    QStringList qsl;
    foreach (QString key, map.keys())
        qsl << QString("%1={%2}").arg(key).arg(map.value(key).toString());
    return qsl;
}

void Settings::dump(const Key &groupKey)
{
    foreach (QString s, toStringList(groupKey)) DUMP << s;
}

void Settings::dump(const QSettings::SettingsMap &map)
{
    foreach (QString s, toStringList(map)) DUMP << s;
}

bool Settings::boolean(const Settings::Key &key, const bool &defaultValue) const
{
    bool ok = contains(key);
    bool result = value(key).toBool();
    return ok ? result : defaultValue;
}

int Settings::signedInt(const Key &key, const signed &defaultValue) const
{
    bool ok = contains(key);
    signed result = get(key).toInt(&ok);
    return ok ? result : defaultValue;
}

unsigned Settings::unsignedInt(const Key &key, const unsigned &defaultValue) const
{
    bool ok = contains(key);
    unsigned result = get(key).toUInt(&ok);
    return ok ? result : defaultValue;
}

qreal Settings::real(const Key &key, const qreal &defaultValue) const
{
    bool ok = contains(key);
    qreal result = get(key).toDouble(&ok);
    return ok ? result : defaultValue;
}

qreal Settings::realPerMille(const Key &key, const unsigned &defaultValue) const
{
    bool ok = contains(key);
    qreal result = get(key).toUInt(&ok);
    return perMille(ok ? result : defaultValue);
}

QQSize Settings::size(const Settings::Key &key, const QQSize &defaultValu) const
{
    QQSize resultSize = defaultValu;
    if (contains(key))
    {
        QQString sizeString = get(key);
        resultSize.set(sizeString);
    }
    return resultSize;
}

qreal Settings::perMille(const unsigned uValue)
{
    return qBound(0.001, qreal(uValue) / 1000.0, 0.999);
}

QString Settings::string(const Key &key, const Value &defaultValue) const
{
    TRACEQFI << key() << defaultValue << get(key, defaultValue);
    return get(key, defaultValue);
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
