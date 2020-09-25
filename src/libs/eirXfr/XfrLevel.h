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
    XfrLevel(const Level level);
    Level level() const { return mLevel; }
    Name name() const { return name(level()); }


private:
    Level mLevel;

    // -------- static -------
public:
    static Level level(const Name &name)
    { return mLevelNameDMap.at(name); }
    static QString name(const Level level)
    { return mLevelNameDMap.at(level); }
    static bool isUser(const Name name)
    { return level(name) >= level("Info") && level(name) < level("Enter"); }
    static bool isDebug(const Name name)
    { return level(name) >= level("Enter") && level(name) < level("Test"); }
    static bool isTest(const Name name)
    { return level(name) >= level("Test") && level(name) < level("Warning"); }
    static bool isWarning(const Name name)
    { return level(name) >= level("Warning") && level(name) < level("Error"); }
    static bool isError(const Name name)
    { return level(name) >= level("Error") && level(name) < level("Fatal"); }
    static bool isFatal(const Name name)
    { return level(name) >= level("Fatal") && level(name) < level("Maximum"); }

private:
    static void staticCtor();

private:
    static DualMap<Level, Name> mLevelNameDMap;
};

