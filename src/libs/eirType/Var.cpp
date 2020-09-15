#include "Var.h"

#include <eirXfr/Debug.h>

Var::Var(const MultiName &name) : mName(name) {;}

Var::Var(const MultiName &name,
         const QVariant &defValue,
         const QVariant &curValue)
    : mName(name)
    , mDefault(defValue)
    , mCurrent(curValue) {;}

Var::Var(const char *name,
         const QVariant &defValue,
         const QVariant &curValue)
    : mName(QString(name))
    , mDefault(defValue)
    , mCurrent(curValue) {;}

bool Var::isNull() const
{
    return mName.isEmpty();
}

MultiName Var::name() const
{
    return mName;
}

void Var::set(const MultiName &newName)
{
    mName = newName;
}

void Var::prependName(const MultiName &groupName)
{
    mName.prependName(groupName);
}

QVariant Var::currentVari() const
{
    return mCurrent;
}

QVariant Var::defaultVari() const
{
    return mCurrent;
}

QVariant Var::value() const
{
    return mCurrent.isValid() ? mCurrent : mDefault;
}

bool Var::operator ==(const Var &other)
{
    return name() == other.name()
            && value() == other.value();
}

QString Var::dumpString() const
{
    return QString("%1 = %2 [%3]").arg(mName)
            .arg(mCurrent.toString()).arg(mDefault.toString());
}

void Var::dump() const
{
    DUMP << dumpString();
}
