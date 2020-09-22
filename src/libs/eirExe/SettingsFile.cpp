#include "SettingsFile.h"

#include <QSettings>
#include <QTemporaryDir>
#include <QTemporaryFile>

#include <eirXfr/Debug.h>

#include "ApplicationHelper.h"

SettingsFile::SettingsFile(ApplicationHelper *helper)
    : QObject(helper)
{
    TSTALLOC(helper);
    TRACEQFI << QOBJNAME(helper);
    mpTempIniFile = helper->tempDirFile("ini", this);
    TSTALLOC(mpTempIniFile);
    mpTempIniFile->setObjectName("SettingsFile:TempIniFile");
    EXPECT(mpTempIniFile->open(QIODevice::ReadWrite | QIODevice::Text));
    mpSettings = new QSettings(mpTempIniFile->fileName(), QSettings::IniFormat, this);

}

bool SettingsFile::isNull() const
{
    TRACEQFI << PTRSTRING(mpTempIniFile) << PTRSTRING(mpSettings) << (mpTempIniFile ? mpTempIniFile->exists() : false);
    return nullptr != mpTempIniFile && nullptr != mpSettings && mpTempIniFile->exists();
}

void SettingsFile::import(const QQFileInfo &iniFileInfo)
{
    TRACEQFI << iniFileInfo;
    QSettings * importSettings = new QSettings(iniFileInfo.absoluteFilePath(), QSettings::IniFormat, this);
    foreach (QString key, importSettings->allKeys())
        mpSettings->setValue(key, importSettings->value(key));
}

void SettingsFile::set(const QString &key, const QString &value) const
{
    TRACEQFI << key << value;
    mpSettings->setValue(key, value);
}

QString SettingsFile::value(const QString &key, const QString &defaultValue) const
{
    return mpSettings->value(key, defaultValue).toString();
}

QString SettingsFile::string(const QString &key, const QString &defaultValue) const
{
    return value(key, defaultValue);
}

SettingsFile::Map SettingsFile::map() const
{
    SettingsFile::Map extracted;
    foreach (QString key, mpSettings->allKeys())
        extracted.insert(key, mpSettings->value(key).toString());
    return extracted;
}

SettingsFile::Map SettingsFile::extract() const
{
    return map();
}

SettingsFile::Map SettingsFile::extract(const QString groupKey, const bool keepKey) const
{
    return map().extract(groupKey, keepKey);
}


SettingsFile::Map::Map() {;}

SettingsFile::Map SettingsFile::Map::extract(const QString groupKey, const bool keepKey) const
{
    SettingsFile::Map extracted;
    QString keyStart = groupKey.simplified().split("/", Qt::SkipEmptyParts).join("/");
    foreach (QString key, keys())
        if (key.startsWith(keyStart))
        {
            QString v = value(key);
            if ( ! keepKey)
                key = key.mid(keyStart.size());
            extracted.insert(key, v);
        }
    return extracted;
}

void SettingsFile::Map::import(const SettingsFile::Map &keyValueStringMap)
{
    foreach (QString key, keyValueStringMap.keys())
        insert(key, keyValueStringMap.value(key));
}

void SettingsFile::Map::operator +=(const SettingsFile::Map &keyValueStringMap)
{
    import(keyValueStringMap);
}

void SettingsFile::Map::setDefault(const QString key, const QVariant &variant)
{
    if ( ! contains(key)) insert(key, variant.toString());
}

QStringList SettingsFile::Map::toStringList() const
{
    QStringList qsl;
    foreach (QString key, keys())
        qsl << QString("%1={%2}").arg(key).arg(value(key));
    return qsl;
}

void SettingsFile::Map::dump() const
{
    foreach (QString d, toStringList()) DUMP << d;
}
