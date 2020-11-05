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
#include <eirType/QQSize.h>
#include <eirType/QQString.h>
#include <eirType/Rational.h>
#include <eirType/ValueMap.h>

#include <eirType/VarMap.h>
class ApplicationHelper;

class EIREXE_EXPORT Settings : public QSettings
{
    Q_OBJECT
public:
    typedef QQString Key;
    typedef QQString Valu;
    typedef QVariant Vari;
    typedef ValueMap Map;

public:
    explicit Settings(QObject *parent=nullptr);

public slots:
    void insert(const QQFileInfo &iniFileInfo);
    void insert(const QStringList &keyValueStrings);
    void insert(const Map &keyVariantMap);
    void set(const Key &key, const Valu &vu);
    void set(const Key &key, const QVariant &vari);
    virtual void setValue(const QString &key, const QVariant &vari);
    virtual void remove(const QString &key);
    void setDefault(const Key &key, const Valu &valu);
    void setDefault(const Key &key, const QVariant &vari);
    void beginGroup(const Key &key);
    void endGroup();

signals:
    void getting(const Key &key, const Valu &valu) const;
    void importing(const Key &key, const Valu &valu);
    void creating(const Key &key, const Valu &valu);
    void defaulted(const Key &key, const Valu &valu);
    void removing(const Key &key, const Valu &oldValu);
    void changing(const Key &key, const Valu &newValu, const Valu &oldValu);
    void groupChanging(const Key &key);

private slots:
    void insert(const Key &key, const Valu &valu);

public: // access
    bool contains(const Key &key) const;
    Valu valu(const Key &key, const Valu &defaultValu=Valu()) const;
    Vari vari(const Key &key, const QVariant &defaultVari=QVariant()) const;
    QStringList keys() const        { return QSettings::allKeys(); }
    Map extract() const;
    Map extract(const Key groupKey, const bool keepKey=false) const;
    QStringList toDebugStringList(const Key &groupKey=Key());
    static QStringList toDebugStringList(const Map &map);
    void dump(const Key &groupKey=Key());
    static void dump(const QSettings::SettingsMap &map);

public: // values
    Vari vari(const Key key) { return QSettings::value(key); }
    Valu valu(const Key key) { return QSettings::value(key).toString(); }
    bool boolean(const Key &key, const bool &defaultValue=false) const;
    signed signedInt(const Key &key, const signed &defaultValue=0) const;
    unsigned unsignedInt(const Key &key, const unsigned &defaultValue=0) const;
    qreal real(const Key &key, const qreal &defaultValue=0) const;
    qreal realPerMille(const Key &key, const signed &defaultValue=0) const;
    QString string(const Key &key, const QString &defaultValu=QString()) const;
    QQSize size(const Key &key, const QQSize &defaultValu=QQSize()) const;
    static qreal perMille(const signed sValue, bool unitBound=true);

    /*
        Rational rational(const QString &key, const Rational &defaultValue=Rational(0)) const;
        Map extract(const QString groupKey, const bool keepKey=false) const;
        void import(const Map &keyValueStringMap);
        void operator += (const Map &keyValueStringMap);
        void dump() const;
    */

private:
};

