#pragma once
#include "eirXfr.h"

#include <QPair>
#include "XerEntry.h"

template <class RTN> class XerReturn
{
public:
    XerReturn()                             {;}
    ~XerReturn()                            {;}
    XerReturn(const RTN rtn)                { mPair.first  = rtn; }
    XerReturn(const XerEntry err)           { mPair.second = err; }
    XerReturn<RTN> set(const RTN rtn)       { mPair.first  = rtn; return *this; }
    XerReturn<RTN> set(const XerEntry err)  { mPair.second = err; return *this; }
    bool isSuccess() const                  { return mPair.first != RTN(); }
    bool isError() const                    { return mPair.second.isError(); }
    bool isNull() const                     { return ! isError() && ! isSuccess(); }
    RTN result() const                      { return mPair.first; }
    XerEntry error() const                  { return mPair.second; }

private:
    QPair<RTN, XerEntry> mPair;
};

