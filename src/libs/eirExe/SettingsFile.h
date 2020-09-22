// file: {repo: EIRC5}./src/libs/eirExe/QSettings.h
#pragma once
#include "eirExe.h"

#include <QObject>
#include <QMap>
#include <QString>
#include <QVariant>
class QSettings;
class QTemporaryDir;
class QTemporaryFile;

#include <eirType/QQFileInfo.h>
#include <eirType/Rational.h>

class ApplicationHelper;

class EIREXE_EXPORT SettingsFile : public QObject
{
    Q_OBJECT
public:
    class EIREXE_EXPORT Map : public QMap<QString, QString>
    {
    public:
        Map();
        Map extract(const QString groupKey, const bool keepKey=false) const;
        void import(const Map &keyValueStringMap);
        void operator += (const Map &keyValueStringMap);
        void setDefault(const QString key, const QVariant &variant);
        void setDefault(const QString key, const QString &value);
        QStringList toStringList() const;
        void dump() const;
    };

public:
    explicit SettingsFile(ApplicationHelper *helper);
    bool isNull() const;
    void import(const QQFileInfo &iniFileInfo);
    void import(const QStringList &keyValueStrings);
    void import(const  Map &keyValueStringMap);
    void import(const  QMap<QString, QVariant> &keyVariantMap);
    void set(const QString &key, const QString &value) const;
    void set(const QString &key, const QVariant &value) const;
    QString value(const QString &key, const QString &defaultValue=QString()) const;
    QVariant variant(const QString &key, const QVariant &defaultValue=QVariant()) const;
    int signedInt(const QString &key, const int &defaultValue=0) const;
    QString string(const QString &key, const QString &defaultValue=QString()) const;
    bool boolean(const QString &key, const bool &defaultValue=false) const;
    unsigned unsignedInt(const QString &key, const int &defaultValue=0) const;
    qreal real(const QString &key, const int &defaultValue=0) const;
    Rational rational(const QString &key, const Rational &defaultValue=Rational(0)) const;
    qreal realPerMille(const QString &key, const int &defaultValue=0) const;
    Map map() const;
    Map extract() const;
    Map extract(const QString groupKey, const bool keepKey=false) const;

private:
    QFile * mpTempIniFile=nullptr;
    QSettings * mpSettings=nullptr;
};

