#pragma once
#include "eirImage.h"

#include "BaseImagePak.h"

class EIRIMAGE_EXPORT FrameImagePak : public BaseImagePak
{
public:
    FrameImagePak(const Id id=Id());
    FrameImagePak(const QString &fileName, const Id id=Id());
    FrameImagePak(const QByteArray &ba, const Id id=Id());
    FrameImagePak(const QImage &qi, const Id id=Id());
};

