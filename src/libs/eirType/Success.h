#pragma once
#include "eirType.h"

#include <QString>

class EIRTYPE_EXPORT Success
{
public:
    Success(void);
    Success(const bool yes);
    bool set(const bool isTrue=true);
    bool is(void) const;
    bool result(void) const;
    bool yes(void);
    bool no(void);
    bool expect(const bool isTrue);
    bool test(const bool isTrue);
    bool testNot(const bool isFalse);
    bool isNull(void) const;
    void nullify(void);
    Success tested(void);
    QString toString(void) const;
    QString toString(const QString & trueString,
                     const QString & falseString,
                     const QString & unknownString) const;
    operator bool (void) const;
    operator QString () const;

private:
    bool mSuccess = false;
    bool mIsInitialized = false;
};


