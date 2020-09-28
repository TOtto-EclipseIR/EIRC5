#QT -= gui # QImage

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../EIRC2.pri)
include(../../opencv4.pri)

LIBS *= -leirXfr5
LIBS *= -leirBase5
LIBS *= -leirType5
LIBS *= -leirExe5
LIBS *= -leirQtCV5
#LIBS *= -leirObjDet5
#LIBS *= -leirImage5

SOURCES += \
        QtcvConsole.cpp \
        main.cpp

HEADERS += \
    QtcvConsole.h

message(DESTDIR = $$DESTDIR)
message(LIBS = $$LIBS)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

