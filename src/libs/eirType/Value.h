//! \file BasicName.h
#pragma once
#include "eirType.h"

#include <QList>
#include <QMap>
#include <QPair>
#include <QVariant>
#include "MultiName.h"


class EIRTYPE_EXPORT Value : public QPair<MultiName, QVariant>
{
public:
    typedef QPair<MultiName, QVariant> Type;
    typedef QList<Value> List;
    typedef QMap<MultiName, QVariant> Map;

public:
    Value();
    Value(const MultiName &name,
          const QVariant &variant=QVariant());
    Value(const MultiName &name,
          const QVariant::Type vtype);
    void set(const MultiName &name,
             const QVariant &variant);
    MultiName name() const;
    QVariant value() const;
};

