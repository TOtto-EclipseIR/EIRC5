#QT -= gui # for QImage

TEMPLATE = lib
DEFINES += EIROBJDET_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../EIRC2.pri)
LIBS *= -leirBase5
LIBS *= -leirType5
LIBS *= -leirExe5
LIBS *= -leirQtCV5

SOURCES += \
    CascadeType.cpp \
    ObjDetPak.cpp \
    ObjDetResultItem.cpp \
    ObjDetResultList.cpp \
    ObjectDetector.cpp \
    RectangleFinder.cpp \
    RectangleGrouper.cpp \
    eirObjDet.cpp

HEADERS += \
    CascadeType.h \
    ObjDetPak.h \
    ObjDetResultItem.h \
    ObjDetResultList.h \
    ObjectDetector.h \
    RectangleFinder.h \
    RectangleGrouper.h \
    eirObjDet_global.h \
    eirObjDet.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
