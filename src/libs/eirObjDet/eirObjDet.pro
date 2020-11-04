#QT -= gui # for QImage

TEMPLATE = lib
DEFINES += EIROBJDET_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../EIRC2.pri)
include(../../opencv4.pri)
LIBS *= -leirXfr5
LIBS *= -leirBase5
LIBS *= -leirType5
LIBS *= -leirExe5
LIBS *= -leirQtCV5

SOURCES += \
    ObjDetEnum.cpp \
    ObjDetManager.cpp \
    ObjDetProcessor.cpp \
    ObjDetResultItem.cpp \
    ObjDetResultList.cpp \
    ObjectDetection.cpp \
    PreScanResult.cpp \
    RectangleFinder.cpp \
    RectangleGrouper.cpp \
    eirObjDet.cpp

HEADERS += \
    ObjDetEnum.h \
    ObjDetManager.h \
    ObjDetProcessor.h \
    ObjDetResultItem.h \
    ObjDetResultList.h \
    ObjectDetection.h \
    PreScanResult.h \
    RectangleFinder.h \
    RectangleGrouper.h \
    eirObjDet_global.h \
    eirObjDet.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
