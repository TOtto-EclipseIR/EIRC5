#pragma once
#include "eirImage.h"

#include <eirType/QQImage.h>
#include <eirType/VarPak.h>

class EIRIMAGE_EXPORT BaseImagePak : public VarPak
{
public:
    enum ImageIndex
    {
        Original = 0,
    };

public:
    BaseImagePak(const Id id=Id());
    BaseImagePak(const QByteArray &ba, const Id id=Id());
    BaseImagePak(const QString &fileName, const Id id=Id());
    BaseImagePak(const QImage &qi, const Id id=Id());
    Id id() const       { return VarPak::id(); }
    bool operator < (const BaseImagePak &other)
    { return id().toDebugString() < other.id().toDebugString(); }
    QQImage image(const ImageIndex iix=Original) const;
};

