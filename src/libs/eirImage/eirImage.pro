#QT -= gui ### for QImage, etc.

TEMPLATE = lib
DEFINES += EIRIMAGE_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../EIRC2.pri)
INCLUDEPATH *= $(QTCVINCLUDEPATH)
LIBS *= -leirType5
LIBS *= -leirExe5
LIBS *= -leirObjDet5
LIBS *= -leirQtCV5

SOURCES += \
    BaseImagePak.cpp \
    BaseImageScene.cpp \
    BaseImageView.cpp \
    ColorWheel.cpp \
    FaceImagePak.cpp \
    FaceImageView.cpp \
    FrameImagePak.cpp \
    FrameImageScene.cpp \
    FrameImageView.cpp \
    GraphicsLayer.cpp \
    HeatmapMarker.cpp \
    Hue.cpp \
    ImageMarkerInterface.cpp \
    MarkManager.cpp \
    MarkerType.cpp \
    OutputManager.cpp \
    SimpleRectMarker.cpp \

HEADERS += \
    BaseImagePak.h \
    BaseImageScene.h \
    BaseImageView.h \
    ColorWheel.h \
    FaceImagePak.h \
    FaceImageView.h \
    FrameImagePak.h \
    FrameImageScene.h \
    FrameImageView.h \
    GraphicsLayer.h \
    HeatmapMarker.h \
    Hue.h \
    ImageMarkerInterface.h \
    MarkManager.h \
    MarkerType.h \
    OutputManager.h \
    SimpleRectMarker.h \
    eirImage_global.h \
    eirImage.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

QT += widgets
