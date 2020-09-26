// file: {repo: EIRC5}./src/libs/eirExe/QSettings.h
#pragma once
#include "eirExe.h"

#include <QObject>
#include <QMap>
#include <QSettings>
#include <QString>
#include <QVariant>
class QTemporaryDir;
class QTemporaryFile;

#include <eirType/MultiName.h>
#include <eirType/QQFileInfo.h>
#include <eirType/Rational.h>

class ApplicationHelper;

class EIREXE_EXPORT Settings : public QObject
{
    Q_OBJECT
public:
    typedef MultiName Key;
    typedef QString Value;
    typedef QMap<QString, QString> Map;

public:
    explicit Settings(QObject *parent=nullptr);
    explicit Settings(const Map &otherMap, QObject *parent=nullptr);
    bool isNull() const;

public slots:
    void import(const QQFileInfo &iniFileInfo);
    void import(const QStringList &keyValueStrings);
    void import(const Map &keyValueStringMap);
    void import(const QSettings::SettingsMap &keyVariantMap);
    void set(const Key &key, const Value &valu);
    void set(const QString &key, const QVariant &vari);
    void setDefault(const Key key, const Value &valu);
    void setDefault(const Key key, const QVariant &vari);

signals:
    void imported(const Key &key, const Value &value);
    void created(const Key &key, const Value &value);
    void defaulted(const Key &key, const Value &value);
    void removed(const Key &key, const Value &oldValue);
    void changed(const Key &key, const Value &newValue, const Value &oldValue);

private slots:
    void import(const Key &key, const Value &value);

public: // access
    bool contains(const Key &key) const;
    Value value(const Key &key, const Value &defaultValue=Value()) const;
    QVariant variant(const Key &key, const QVariant &defaultValue=QVariant()) const;
    Map extract() const;
    Map extract(const Key groupKey, const bool keepKey=false) const;
    QStringList toStringList() const;
    void dump() const;
    static void dump(const Map map);

public: // values
    bool boolean(const QString &key, const bool &defaultValue=false) const;
    int signedInt(const QString &key, const signed &defaultValue=0) const;
    unsigned unsignedInt(const QString &key, const unsigned &defaultValue=0) const;
    qreal real(const QString &key, const qreal &defaultValue=0) const;
    qreal realPerMille(const QString &key, const int &defaultValue=0) const;
    QString string(const QString &key, const QString &defaultValue=QString()) const;


    /*
        Rational rational(const QString &key, const Rational &defaultValue=Rational(0)) const;
        Map extract(const QString groupKey, const bool keepKey=false) const;
        void import(const Map &keyValueStringMap);
        void operator += (const Map &keyValueStringMap);
        void dump() const;
    */

private:
    QFile * mpTempIniFile=nullptr;
    QSettings * mpSettings=nullptr;
    Map mLiveMap;
};

