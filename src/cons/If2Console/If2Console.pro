#QT -= gui ### get QImage back
QT *= xml

CONFIG += c++11 console
CONFIG -= app_bundle

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
#INCLUDEPATH *= F:\lang\OpenCV4\opencv\build\include


LIBS *= -leirBase5
LIBS *= -leirType5
#LIBS *= -leirImage5
LIBS *= -leirExe5
#LIBS *= -leirHaar5
LIBS *= F:\lang\OpenCV4\opencv\build\x64\vc15\lib\opencv_world440d.lib

SOURCES += \
        INDIfaceConsole.cpp \
        If2CommandLine.cpp \
    ImageMarker.cpp \
    MarkedFrame.cpp \
    RectCascade.cpp \
    RectFinder.cpp \
    RectFinderClass.cpp \
    RectFinderParameters.cpp \
    cvMat.cpp \
    cvRect.cpp \
#    cvRectStdVector.cpp \
    cvSize.cpp \
        main.cpp \

HEADERS += \
    ../../version.h \
    INDIfaceConsole.h \
    If2CommandLine.h \
    ImageMarker.h \
    MarkedFrame.h \
    RectCascade.h \
    RectFinder.h \
    RectFinderClass.h \
    RectFinderParameters.h \
    cvMat.h \
    cvRect.h \
 #   cvRectStdVector.h \
    cvSize.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    T:/bin/DetectCascades.txt \
    T:/bin/DetectRD.txt \
    T:/bin/Input01.txt \
    T:/bin/OutputRD.txt


