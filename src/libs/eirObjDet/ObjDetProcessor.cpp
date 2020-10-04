#include "ObjDetProcessor.h"

#include <eirXfr/Debug.h>

ObjDetProcessor::ObjDetProcessor(const cvCascade::Type cascadeType)
    : cmType(cascadeType) , cmpCascade(new cvCascade(cmType)) {;}


void ObjDetProcessor::configure(const Settings::Key rectKey, const Settings::Key groupKey)
{
    TRACEQFI << rectKey() << groupKey();
    mRectSettings.read(rectKey);
    mGroupSettings.read(groupKey);
}
