#include "ImageMarkerInterface.h"

#include <eirXfr/Debug.h>

ImageMarkerInterface::ImageMarkerInterface(const MarkerType type,
                                           const Settings::Key baseMarkerKey)
    : cmType(type)
    , cmMarkerKey(baseMarkerKey.appended(type.name()))
{
    TRACEQFI << type.name() << cmMarkerKey;
}

// virtual
void ImageMarkerInterface::mark(BaseImagePak &pak, const VarMap &inputData) const
{
    TRACEQFI << pak << inputData.name()();
    MUSTDO(it);
}
