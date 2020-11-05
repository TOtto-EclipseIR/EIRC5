QT -= gui

TEMPLATE = lib
DEFINES += EIRWGT_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../EIRC2.pri)
LIBS *= -leirType5

SOURCES += \
    GraphicsMainWindow.cpp \
    StackedGraphicsMainPage.cpp \
    StackedGraphicsMainWindow.cpp \
    StackedGridMainWindow.cpp \
    eirWgt.cpp

HEADERS += \
    GraphicsMainWindow.h \
    StackedGraphicsMainPage.h \
    StackedGraphicsMainWindow.h \
    StackedGridMainWindow.h \
    eirWgt_global.h \
    eirWgt.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

QT += widgets
