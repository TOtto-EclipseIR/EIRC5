//! \file Flags.h
#pragma once
#include "eirType.h"

#include <QBitArray>
#include <QChar>
#include <QList>
#include <QString>

#include  <eirType/BasicName.h>
#include <eirType/DualMap.h>

class EIRTYPE_EXPORT BitFlags
{
public:
    BitFlags(const int size=0, const bool is=false);
    // status
    int size() const;
    void clear();
    void resize(const int newSize, const bool truncate=false);
    void fill(const bool is=true);
    bool isAll(const bool is) const;
    bool isAllUnset() const;
    bool isAllSet() const;
    bool contains(const int index) const;
    bool contains(const BasicName & name) const;
    bool at(const int index) const;
    bool at(const BasicName &name) const;
    bool operator [] (const int index) const;
    bool operator [] (const BasicName &name) const;
    QBitArray bits() const;
    // manipulation
    QBitRef bitRef(const int index);
    QBitRef bitRef(const BasicName &name);
    void unset(const int index);
    void unset(const BasicName &name);
    void unsetAll();
    void set(const int index, const bool is=true);
    void set(const BasicName &name, const bool is=true);
    void setAll();
    // setup
    void registerFlag(const int newIndex, const BasicName &name);
    void registerFlag(const BasicName &name);
    void registerFlags(const int newIndex, const BasicName::List &names);
    void registerFlags(const int newIndex, const QStringList &names);
    void registerFlags(const BasicName::List &names);
    void registerFlags(const int newIndex, QString &names);
    void registerFlags(const QString &names);
    // access
    BasicName name(const int index) const;
    const char *namePch(const int index) const;
    int index(const BasicName &name) const;
    BasicName::List names() const;
    BasicName::List namesSet() const;
    QString namesSetString(const QChar delimeter=QChar(' '));
    QList<int> indiciesSet() const;

protected:
    const int cmFlagsUserBase           = 1024;
    const int cmImageFlagsBase          = 256 + cmFlagsUserBase;
    const int cmImageFormatFlagsBase    =   0 + cmImageFlagsBase;
    const int cmImageFormatFlagsEnd     = 127 + cmImageFormatFlagsBase;
    const int cmImageOutputFlagsBase    =   1 + cmImageFormatFlagsEnd;
    const int cmImageFlagsEnd           = 271 + cmImageFlagsBase;

    const int cmImageFlagsNext          = 272 + cmImageFlagsBase;


private:
    QBitArray mBits;
    DualMap<int, BasicName> mIndexNameDMap;


};

