### QT -= gui

TEMPLATE = lib
DEFINES += EIRXFR_LIBRARY

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../EIRC2.pri)

#LIBS *= -leir???5

SOURCES += \
    HexDump.cpp \
    StartupDebug.cpp \
    XerEntry.cpp \
    XerEntryList.cpp \
    XfrBaseEventReceiver.cpp \
    XfrEntry.cpp \
    XfrEvent.cpp \
    XfrEventQueue.cpp \
    XfrFilter.cpp \
    XfrFlags.cpp \
    XfrFunctionInfo.cpp \
    XfrLevel.cpp \
    XfrTrollEventReceiver.cpp \
    eirXfr.cpp \

HEADERS += \
    Debug.h \
    HexDump.h \
    StartupDebug.h \
    XerEntry.h \
    XerEntryList.h \
    XfrBaseEventReceiver.h \
    XfrEntry.h \
    XfrEvent.h \
    XfrEventQueue.h \
    XfrFilter.h \
    XfrFlags.h \
    XfrFunctionInfo.h \
    XfrLevel.h \
    XfrMacros.h \
    XfrTrollEventReceiver.h \
    eirXfr_global.h \
    eirXfr.h \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../XFR
