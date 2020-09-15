#pragma once
#include "eirType.h"

#include "VarMap.h"

class EIRTYPE_EXPORT VarMapMap
{
public:
    VarMapMap();
    void insert(const BasicName &name,
                const VarMap &map);
    VarMap value(const MultiName &name) const;
    bool contains(const MultiName &name) const;
    MultiName::List names() const;

private:
    VarMap::Map mNameMapMap;
};

