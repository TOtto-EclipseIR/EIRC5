#include "Value.h"

#include <eirXfr/Debug.h>

Value::Value()
{

}

Value::Value(const MultiName &name, const QVariant &variant)
{
    TRACEQFI << name() << variant;
    set(name, variant);
}

void Value::set(const MultiName &name, const QVariant &variant)
{
    TRACEQFI << name() << variant;
    first = name, second = variant;
}

MultiName Value::name() const
{
    return first;
}

QVariant Value::value() const
{
    return second;
}
