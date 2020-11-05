#include "FrameImagePak.h"

FrameImagePak::FrameImagePak(const Id id)
    : BaseImagePak(id)
{

}

FrameImagePak::FrameImagePak(const QString &fileName, const Id id)
    : BaseImagePak(fileName, id)
{
}

FrameImagePak::FrameImagePak(const QByteArray &ba, const Id id)
    : BaseImagePak(ba, id)
{

}
