#include "MarkManager.h"

#include <eirXfr/Debug.h>

#include "BaseImagePak.h"
#include "FaceImagePak.h"
#include "FrameImagePak.h"

MarkManager::MarkManager(QObject *parent)
    : QObject(parent)
{
    TRACEQFI << QOBJNAME(parent);
    setObjectName("MarkManager");
}

void MarkManager::add(const FrameImagePak &framepak)
{
    TRACEQFI << framepak.id();
    add(BaseImagePak(framepak));
}

void MarkManager::add(const FaceImagePak &facepak)
{
    TRACEQFI << facepak.id();
    add(BaseImagePak(facepak));
}

void MarkManager::add(const BaseImagePak &imagepak)
{
    TRACEQFI << imagepak.id();
    mIdImagePakMap.insert(imagepak.id(), imagepak);
}
