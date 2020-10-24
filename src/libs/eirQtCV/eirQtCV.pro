QT *= gui xml

TEMPLATE = lib
DEFINES += EIRQTCV_LIBRARY

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../EIRC2.pri)
include(../../opencv4.pri)

LIBS *= -leirXfr5
LIBS *= -leirBase5
LIBS *= -leirType5
LIBS *= -leirExe5

SOURCES += \
    cvBGRA.cpp \
    cvClassifier.cpp \
    cvClassifierPool.cpp \
    cvMat.cpp \
    cvRect.cpp \
    cvRectVector.cpp \
    cvSize.cpp \
    cvString.cpp \
    cvVersion.cpp \
    eirQtCV.cpp

HEADERS += \
    cvBGRA.h \
    cvClassifier.h \
    cvClassifierPool.h \
    cvMat.h \
    cvRect.h \
    cvRectVector.h \
    cvSize.h \
    cvString.h \
    cvVersion.h \
    eirQtCV_global.h \
    eirQtCV.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
