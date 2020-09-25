#pragma once
#include "eirExe.h"

#include <eirType/VarMap.h>


class EIREXE_EXPORT Configuration : public VarMap
{
public:
    Configuration(const MultiName &name=MultiName());
    Configuration(const VarMap &other);
    void setDefault(const MultiName &key, const QVariant &defaultValue);
    QString string(const MultiName &key, const QString &defValue=QString()) const;
    signed signedInt(const MultiName &key, const signed defValue=0) const;
    unsigned unsignedInt(const MultiName &key, const unsigned defValue=0) const;
    bool boolean(const MultiName &key, const bool defValue=false) const;
    qreal real(const MultiName &key, const qreal &defValue=0.0) const;
    qreal realPermille(const MultiName &key, const unsigned &defValue=0) const;
};

