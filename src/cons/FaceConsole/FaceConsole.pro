#QT -= gui # QImage
Qt *= xml

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = INDI5console

include(../../EIRC2.pri)
include(../../opencv4.pri)

LIBS *= -leirXfr5
LIBS *= -leirBase5
LIBS *= -leirType5
LIBS *= -leirExe5
LIBS *= -leirQtCV5
LIBS *= -leirObjDet5
LIBS *= -leirImage5

SOURCES += \
    FaceConsole.cpp \
    main.cpp

HEADERS += \
    ../../version.h \
    FaceConsole.h

DISTFILES += \
    ../../../../../bin/config/DetectCascades.txt \
    ../../../../../bin/config/DetectRD.txt \
    ../../../../../bin/config/I5c.bat \
    ../../../../../bin/config/Input01.txt \
    ../../../../../bin/config/OutputRD.txt \
    ../../../../../bin/config/SkyPlex.txt \
    ../../../../../bin/config/fodder.txt \
    Notes.txt \
    T:/bin/DetectCascades.txt \
    T:/bin/DetectRD.txt \
    T:/bin/Input01.txt \
    T:/bin/OutputRD.txt


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

