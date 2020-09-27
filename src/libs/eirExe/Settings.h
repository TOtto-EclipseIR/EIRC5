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

class EIREXE_EXPORT Settings : public QSettings
{
    Q_OBJECT
public:
    typedef MultiName Key;
    typedef QString Value;
    typedef QMap<QString, QString> Map;

public:
    explicit Settings(QObject *parent=nullptr);

public slots:
    void insert(const QQFileInfo &iniFileInfo);
    void insert(const QStringList &keyValueStrings);
    void insert(const Map &keyValueStringMap);
    void insert(const QSettings::SettingsMap &keyVariantMap);
    void set(const Key &key, const Value &valu);
    void set(const Key &key, const QVariant &vari);
    virtual void setValue(const QString &key, const QVariant &vari);
    virtual void remove(const QString &key);
    void setDefault(const Key &key, const Value &valu);
    void setDefault(const Key &key, const QVariant &vari);
    void beginGroup(const Key &key);
    void endGroup();

signals:
    void getting(const Key &key, const Value &valu) const;
    void importing(const Key &key, const Value &valu);
    void creating(const Key &key, const Value &valu);
    void defaulted(const Key &key, const Value &valu);
    void removing(const Key &key, const Value &oldValu);
    void changing(const Key &key, const Value &newValu, const Value &oldValu);
    void groupChanging(const Key &key);

private slots:
    void insert(const Key &key, const Value &valu);

public: // access
    bool contains(const Key &key) const;
    Value get(const Key &key, const Value &defaultValu=Value()) const;
    virtual QVariant value(const Key &key, const QVariant &defaultVari=QVariant()) const;
    MultiName::List keys() const;
    Map extract() const;
    Map extract(const Key groupKey, const bool keepKey=false) const;
    QStringList toStringList() const;
    void dump() const;

public: // values
    bool boolean(const Key &key, const bool &defaultValue=false) const;
    int signedInt(const Key &key, const signed &defaultValue=0) const;
    unsigned unsignedInt(const Key &key, const unsigned &defaultValue=0) const;
    qreal real(const Key &key, const qreal &defaultValue=0) const;
    qreal realPerMille(const Key &key, const int &defaultValue=0) const;
    QString string(const Key &key, const QString &defaultValu=QString()) const;


    /*
        Rational rational(const QString &key, const Rational &defaultValue=Rational(0)) const;
        Map extract(const QString groupKey, const bool keepKey=false) const;
        void import(const Map &keyValueStringMap);
        void operator += (const Map &keyValueStringMap);
        void dump() const;
    */

private:
};

