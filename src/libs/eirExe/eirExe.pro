#QT -= gui ### QIcon
QT *= xml

TEMPLATE = lib
DEFINES += EIREXE_LIBRARY

CONFIG += c++11

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

LIBS *= -leirBase5
LIBS *= -leirType5

SOURCES += \
    ActionManager.cpp \
    ApplicationHelper.cpp \
    ArgumentId.cpp \
    ArgumentItem.cpp \
    ArgumentManager.cpp \
    ArgumentType.cpp \
    BaseArgumentHandler.cpp \
    CommandLine.cpp \
    CommandLineClientInterface.cpp \
    Console.cpp \
    FileExtension.cpp \
    FileInfoQueue.cpp \
    FileName.cpp \
    FileWriteQueue.cpp \
    QQDirIterator.cpp \
    Settings.cpp \
    StdStreams.cpp \
    XmlFile.cpp \
    eirExe.cpp

HEADERS += \
    ../../version.h \
    ../APP \
    ActionManager.h \
    ApplicationHelper.h \
    ArgumentId.h \
    ArgumentItem.h \
    ArgumentManager.h \
    ArgumentType.h \
    BaseArgumentHandler.h \
    CommandLine.h \
    CommandLineClientInterface.h \
    Console.h \
    FileExtension.h \
    FileInfoQueue.h \
    FileName.h \
    FileWriteQueue.h \
    QQDirIterator.h \
    Settings.h \
    StdStreams.h \
    XmlFile.h \
    eirExe_global.h \
    eirExe.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
