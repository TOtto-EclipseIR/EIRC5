#include "Configuration.h"

#include <eirXfr/Debug.h>

Configuration::Configuration(const MultiName &name) : VarMap(name) {;}
Configuration::Configuration(const VarMap &other) : VarMap(other) {;}

void Configuration::setDefault(const MultiName &key,
                               const QVariant &defaultValue)
{
    insert(Var(key, defaultValue));
}

QString Configuration::string(const MultiName &key,
                              const QString &defValue) const
{
    QString strValue = value(key).value().toString();
    return notContains(key)
            ? defValue
            : strValue;
}

signed Configuration::signedInt(const MultiName &key,
                                const signed defValue) const
{
    bool ok;
    signed sintValue = value(key).value().toInt(&ok);
    return  (ok && contains(key))
            ? sintValue
            : defValue;
}

unsigned Configuration::unsignedInt(const MultiName &key,
                                    const unsigned defValue) const
{
    TRACEQFI << key() << defValue;
    bool ok;
    unsigned uintValue = value(key).value().toUInt(&ok);
    TRACE << ok << contains(key) << uintValue;
    return  (ok && contains(key))
            ? uintValue
            : defValue;
}

bool Configuration::boolean(const MultiName &key,
                            const bool defValue) const
{
    bool boolValue = value(key).value().toBool();
    return notContains(key)
            ? defValue
            : boolValue;
}

qreal Configuration::real(const MultiName &key,
                          const qreal &defValue) const
{
    TRACEQFI << key() << defValue;
    bool ok;
    qreal realValue = value(key).value().toDouble(&ok);
    TRACE << ok << contains(key) << realValue;
    return  (ok && contains(key))
            ? realValue
            : defValue;
}


