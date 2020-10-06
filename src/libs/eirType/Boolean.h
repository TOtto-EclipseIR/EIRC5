#pragma once
#include "eirType.h"

class EIRTYPE_EXPORT Boolean
{
public:
    Boolean();
    Boolean(const bool is);
    bool isNull() const;
    bool isValid() const;
    bool isInvalid() const;
    bool is() const;
    operator bool () const;
    bool operator ()() const;
    QString toString() const;
    operator QString () const;

    bool set(const bool b=true);
    bool unset(const bool isNot=true);
    bool operator = (const bool b);
    void invalidate();
    void nullify();

private:
    bool mValid=false;
    bool mBool=false;
};

EIRTYPE_EXPORT QDebug operator<<(QDebug dbg, const Boolean &pak);
