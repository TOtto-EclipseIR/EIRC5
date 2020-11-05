#pragma once

#include "BaseImagePak.h"

class QByteArray;
class QImage;

class FaceImagePak : public BaseImagePak
{
public:
    FaceImagePak(const Id id=Id());
    FaceImagePak(const QByteArray &ba, const Id id=Id());
    FaceImagePak(const QImage &qi, const Id id=Id());
};

