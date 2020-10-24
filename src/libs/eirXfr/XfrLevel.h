#pragma once
#include "eirXfr.h"

#include <eirType/DualMap.h>

class EIRXFR_EXPORT  XfrLevel
{
public:
    typedef qint32 Level;
    typedef QString Name; ;

public:
    XfrLevel();
    XfrLevel(const Level lvl);
    XfrLevel(const Name &nam);
    void set(const Level lvl);
    void set(const Name &nam);
    void clear();
    bool isNull() const;
    bool notNull() const;
    bool isValid() const;
    bool notValid() const;
    Level level() const { return mLevel; }
    Name name() const { return name(level()); }
    bool operator == (const XfrLevel &other);

private:
    Level mLevel;

    // -------- static -------
public:
    static Level level(const Name &name)
    { return mLevelNameDMap.at(name); }
    static QString name(const Level level)
    { return mLevelNameDMap.at(level); }
    static bool isValid(const Level level) { return mLevelNameDMap.contains(level); }
    static bool isValid(const Name name) { return mLevelNameDMap.contains(name); }
    static bool isUser(const Name name)
    { return level(name) >= level("Info") && level(name) < level("Enter"); }
    static bool isDebug(const Name name)
    { return level(name) >= level("Enter") && level(name) < level("Test"); }
    static bool isTest(const Name name)
    { return level(name) >= level("Test") && level(name) < level("Warning"); }
    static bool isWarning(const Name name)
    { return level(name) >= level("Warning") && level(name) < level("Error"); }
    static bool isError(const Name name, bool exact=false)
    { return level(name) >= level("Error") && level(name) < (exact ? level("Fatal") : level("Maximum")); }
    static bool isFatal(const Name name)
    { return level(name) >= level("Fatal") && level(name) < level("Maximum"); }

private:
    static void staticCtor();

private:
    static DualMap<Level, Name> mLevelNameDMap;
};

