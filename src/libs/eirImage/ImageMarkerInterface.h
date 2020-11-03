#pragma once

#include <eirExe/Settings.h>

#include "BaseImagePak.h"
#include "MarkerType.h"

class ImageMarkerInterface
{
public:
    ImageMarkerInterface(const MarkerType type,
                         const Settings::Key baseMarkerKey=Settings::Key());
    virtual void mark(/* non-const */ BaseImagePak &pak,
                         const VarMap &inputData) const;

protected:
    virtual MarkerType inputImageType() const = 0;
    virtual QQImage mark(const QQImage &inputImage, const VarMap &inputData) const = 0;

private:
    const MarkerType cmType=MarkerType::Null;
    const Settings::Key cmMarkerKey;
};

