TEMPLATE = subdirs

include(./EIRC2.pri)

SUBDIRS += \
    ./libs/eirXfr           \
    ./libs/eirBase          \
    ./libs/eirType          \
    ./libs/eirExe           \
    ./libs/eirQtCV          \
    ./libs/eirFrame         \
    ./libs/eirFinder        \
    ./libs/eirImageIO       \
#    ./cons/If2Console       \
    ./cons/FaceConsole      \
    ./cons/HelloConsole     \
    cons/QtCVmain \
    libs/eirCascade

eirType.depends     = eirBase
eirExe.depends      = eirBase eirType
eirQtCV.depends     = eirBase eirType eirXfr
eirXfr.depends      =
HelloConsole.depends    = eirExe
