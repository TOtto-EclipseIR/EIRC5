#pragma once
#include "eirXfr.h"

#include <QPair>
#include "XerEntry.h"

template <class VAR> class XerReturn
{
public:
    XerReturn(const QString name=QString()) : mName(name) {;}
    ~XerReturn()                            {;}
    XerReturn(const VAR var)                { mPair.first  = var; }
    XerReturn(const XerEntry err)           { mPair.second = err; }
    XerReturn<VAR> set(const VAR var)       { mPair.first  = var; return *this; }
    XerReturn<VAR> set(const XerEntry &err) { mPair.second = err; return *this; }
    XerReturn<VAR> set(const XerReturn &other)
    { mName = other.mName, set(other.result()), set(other.error()); return *this; }
    bool isSuccess() const                  { return mPair.first != VAR(); }
    bool isError() const                    { return mPair.second.isError(); }
    bool isNull() const                     { return ! isError() && ! isSuccess(); }
    VAR result() const                      { return mPair.first; }
    XerEntry error() const                  { return mPair.second; }
    QString toDebugString() const
    {
        if (isNull())       return mName + ": is Null";
        if (isError())      return mName + ":" + error().toString();
        if (isSuccess())    return mName + ":" + result().toDebugString();
                            return mName + ": is Wierd";
    }

private:
    QString mName;
    QPair<VAR, XerEntry> mPair;
};

