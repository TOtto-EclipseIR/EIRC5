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


void Settings::insert(const Map &keyVariantMap)
{
    MUSTDO(it);
    MUSTUSE(keyVariantMap);

}

void Settings::insert(const Settings::Key &key, const Settings::Valu &valu)
{
    TRACEQFI << key() << valu;
    EMIT(importing(key, valu));
    set(key, valu);
}

bool Settings::contains(const Settings::Key &key) const
{
    return QSettings::contains(key);
}

void Settings::set(const Key &key, const Valu &vlu)
{
    TRACEQFI << key() << vlu;
    if (this->contains(key))
    {
        EMIT(changing(key, vlu, valu(key)));
    }
    else
    {
        EMIT(creating(key, vlu));
    }  // TODO see [#11] comment re {EMIT}s
    QSettings::setValue(key, vlu);
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
        EMIT(changing(key, vari.toString(), valu(key)));
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
    EMIT(removing(key, valu(key)));
    QSettings::remove(key);
}

void Settings::setDefault(const Key &key, const Valu &valu)
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

Settings::Valu Settings::valu(const Key &key, const Valu &defaultValu) const
{
    Settings::Valu valu = QSettings::value(key, defaultValu).toString();
    EMIT(getting(key, valu));
    TRACEQFI << key() << valu << defaultValu;
    return valu;
}

QVariant Settings::vari(const Settings::Key &key, const QVariant &defaultVari) const
{
    QVariant vari = QSettings::value(key(), defaultVari);
    EMIT(getting(key, vari.toString()));
    TRACEQFI << key() << vari << defaultVari;
    return vari;
}

Settings::Map Settings::extract(const Key groupKey, const bool keepKey) const
{
    Settings::Map extractedMap;
    foreach (Key key, keys())
        if (key.startsWith(groupKey))
        {
            Valu extractValue = valu(key);
            Key extractKey = keepKey ? key : key.mid(groupKey.size());
            extractedMap[extractKey] = extractValue;
        }
    return extractedMap;
}

QStringList Settings::toDebugStringList(const Key &groupKey)
{
    QStringList qsl;
    if ( ! groupKey.isEmpty()) beginGroup(groupKey);
    foreach (Key key, keys())
        qsl << QString("%1={%2}").arg(key).arg(valu(key));
    if ( ! groupKey.isEmpty()) endGroup();
    return qsl;
}

QStringList Settings::toDebugStringList(const Map &map)
{
    QStringList qsl;
    foreach (QString key, map.keys())
        qsl << QString("%1={%2}").arg(key).arg(map.get(key).value().toString());
    return qsl;
}

void Settings::dump(const Key &groupKey)
{
    foreach (QString s, toDebugStringList(groupKey)) DUMP << s;
}

// static
void Settings::dump(const QSettings::SettingsMap &map)
{
    foreach (QString key, map.keys())
        DUMP << QString("%1={%2}").arg(key).arg(map.value(key).toString());
}

bool Settings::boolean(const Settings::Key &key, const bool &defaultValue) const
{
    bool ok = contains(key);
    bool result = vari(key).toBool();
    return ok ? result : defaultValue;
}

signed Settings::signedInt(const Key &key, const signed &defaultValue) const
{
    signed rtn = vari(key, defaultValue).value<signed>();
    TRACEQFI << key() << rtn << defaultValue;
    return rtn;
}

unsigned Settings::unsignedInt(const Key &key, const unsigned &defaultValue) const
{
    bool ok;
    unsigned result = valu(key).toUInt(&ok);
    ok &= contains(key);
    return ok ? result : defaultValue;
}

qreal Settings::real(const Key &key, const qreal &defaultValue) const
{
    bool ok = contains(key);
    qreal result = valu(key).toDouble(&ok);
    return ok ? result : defaultValue;
}

qreal Settings::realPerMille(const Key &key, const unsigned &defaultValue) const
{
    bool ok = contains(key);
    qreal result = valu(key).toUInt(&ok);
    return perMille(ok ? result : defaultValue);
}

QString Settings::string(const Settings::Key &key, const QString &defaultValu) const
{
    return valu(key, defaultValu);
}

QQSize Settings::size(const Settings::Key &key, const QQSize &defaultValu) const
{
    QQSize resultSize = defaultValu;
    if (contains(key))
    {
        QQString sizeString = valu(key);
        resultSize.set(sizeString);
    }
    return resultSize;
}

// static
qreal Settings::perMille(const unsigned uValue, bool unitBound)
{
    qreal fValue = qreal(uValue);
    return unitBound ? fValue : qBound(0.001, qreal(uValue) / 1000.0, 0.999);
}

#if 0
QString Settings::string(const Key &key, const Valu &defaultValue) const
{
    TRACEQFI << key() << defaultValue << get(key, defaultValue);
    return get(key, defaultValue);
}

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
