#include "XfrEvent.h"

XfrEvent::XfrEvent(const XfrEntry &entry, const XfrEvent::Type type)
    : QEvent(QEvent::Type(type))
    , cmEntryUid(entry.uid())
{

}

bool XfrEvent::operator ==(const XfrEvent &other)
{
    return cmEntryUid == other.cmEntryUid;
}
