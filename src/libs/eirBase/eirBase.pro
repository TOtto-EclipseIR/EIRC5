# QT -= gui ### QColor

TEMPLATE = lib
DEFINES += EIRBASE_LIBRARY

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../../EIRC2.pri)
LIBS *= -leirXfr5

SOURCES += \
    UInt128.cpp \
    Uuid.cpp \
    Version.cpp \
    eirBase.cpp \

HEADERS += \
    ../../version.h \
    ../APP \
    Typedefs.h \
    UInt128.h \
    Uuid.h \
    Version.h \
    eirBase_global.h \
    eirBase.h \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../depends.pri \
    ../../../ourdest.pri \
    ../../EIRC2.pri \
    ../../apps/apps.pri \
    ../../apps/cons/cons.pri \
    ../../depends.pri
