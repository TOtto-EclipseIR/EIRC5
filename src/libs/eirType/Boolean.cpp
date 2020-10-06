#include "Boolean.h"

#include <QtDebug>
#include <QString>

Boolean::Boolean() {;}
Boolean::Boolean(const bool is) : mValid(true), mBool(is) {;}

bool Boolean::isNull() const
{
    return ! mValid && ! mBool;
}

bool Boolean::isValid() const
{
    return mValid;
}

bool Boolean::isInvalid() const
{
    return ! isValid();
}

bool Boolean::is() const
{
    return mValid && mBool;
}

bool Boolean::operator ()() const
{
    return is();
}

QString Boolean::toString() const
{
    if (mValid)
        return mBool ? "true" : "false";
    else
        return mBool ? "{invalid}" : "{null}";
}

Boolean::operator QString() const
{
    return toString();
}

bool Boolean::set(const bool b)
{
    mBool = b, mValid = true;
    return is();
}

bool Boolean::unset(const bool isNot)
{
    mBool = ! isNot, mValid = true;
    return is();
}

bool Boolean::operator =(const bool b)
{
    set(b);
    return is();
}

void Boolean::invalidate()
{
    mValid = false, mBool = true;
}

void Boolean::nullify()
{
    mValid = false, mBool = false;
}

Boolean::operator bool() const
{
    return is();
}

QDebug operator<<(QDebug dbg, const Boolean &boolean)
{
    dbg << boolean.toString();
    return dbg;
}
