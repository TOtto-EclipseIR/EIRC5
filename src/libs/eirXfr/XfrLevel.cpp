#include "XfrLevel.h"

DualMap<XfrLevel::Level, XfrLevel::Name> XfrLevel::mLevelNameDMap;

XfrLevel::XfrLevel()
{
    staticCtor();
}

XfrLevel::XfrLevel(const Level lvl)
    : mLevel(lvl)
{
    staticCtor();
}

XfrLevel::XfrLevel(const XfrLevel::Name &nam)
    : mLevel(level(nam))
{
    staticCtor();
}

void XfrLevel::set(const XfrLevel::Level lvl)
{
    mLevel = lvl;
}

void XfrLevel::set(const XfrLevel::Name &nam)
{
    mLevel = XfrLevel::level(nam);
}

void XfrLevel::clear()
{
    mLevel = 0;
}

bool XfrLevel::isNull() const
{
    return level("NoLevel") == mLevel;
}

bool XfrLevel::notNull() const
{
    return ! isNull();
}

bool XfrLevel::isValid() const
{
    return mLevelNameDMap.contains(mLevel) && ! isNull();
}

bool XfrLevel::notValid() const
{
    return ! isValid();
}

void XfrLevel::staticCtor()
{
    if (mLevelNameDMap.isEmpty())
    {
        mLevelNameDMap.insertUnique(0x00000000, "NoLevel");
        mLevelNameDMap.insertUnique(0x10000000, "Info");
        mLevelNameDMap.insertUnique(0x20000000, "Enter");
        mLevelNameDMap.insertUnique(0x20000010, "FunctionEnter");
        mLevelNameDMap.insertUnique(0x20000011, "FunctionArg1");
        mLevelNameDMap.insertUnique(0x20000012, "FunctionArg2");
        mLevelNameDMap.insertUnique(0x20000013, "FunctionArg3");
        mLevelNameDMap.insertUnique(0x20000014, "FunctionArg4");
        mLevelNameDMap.insertUnique(0x2000001D, "FunctionReturn");
        mLevelNameDMap.insertUnique(0x2000001E, "FunctionReturnVoid");
        mLevelNameDMap.insertUnique(0x2000001F, "FunctionLeave");
        mLevelNameDMap.insertUnique(0x30000000, "Todo");
        mLevelNameDMap.insertUnique(0x40000000, "Dump");
        mLevelNameDMap.insertUnique(0x48000000, "Trace");
        mLevelNameDMap.insertUnique(0x50000000, "Debug");
        mLevelNameDMap.insertUnique(0x58000000, "Test");
        mLevelNameDMap.insertUnique(0x60000000, "Warning");
        mLevelNameDMap.insertUnique(0x68000000, "Error");
        mLevelNameDMap.insertUnique(0x70000000, "Fatal");
        mLevelNameDMap.insertUnique(0x72000000, "Process");
        mLevelNameDMap.insertUnique(0x74000000, "System");
        mLevelNameDMap.insertUnique(0x76000000, "Host");
        mLevelNameDMap.insertUnique(0x78000000, "Site");
        mLevelNameDMap.insertUnique(0x7A000000, "Enterprise");
        mLevelNameDMap.insertUnique(0x7F000000, "Universal");
        mLevelNameDMap.insertUnique(0x7FFFFFFF, "Maximum");
    }
}
