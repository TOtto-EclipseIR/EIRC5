# QT -= gui ### QImage

TEMPLATE = lib
DEFINES += EIRTYPE_LIBRARY

CONFIG += c++17

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

SOURCES += \
    ArgumentItem.cpp \
    Enumeration.cpp \
    FunctionInfo.cpp \
    Id.cpp \
    MultiName.cpp \
    QQByteArray.cpp \
    QQColor.cpp \
    QQDir.cpp \
    QQFile.cpp \
    QQFileInfo.cpp \
    QQFileInfoList.cpp \
    QQImage.cpp \
    QQRect.cpp \
    QQRectF.cpp \
    QQRectList.cpp \
    QQSize.cpp \
    QQString.cpp \
    Rational.cpp \
    Real.cpp \
    RealMath.cpp \
    Region.cpp \
    Sortable.cpp \
    BitFlags.cpp \
    Value.cpp \
    ValuePak.cpp \
    Var.cpp \
    VarMap.cpp \
    VarMapMap.cpp \
    VarPak.cpp \
    VersionInfo.cpp \
    BasicName.cpp \
    Boolean.cpp \
    Milliseconds.cpp \
    Success.cpp \
    eirType.cpp \

HEADERS += \
    ../../version.h \
    ArgumentItem.h \
    BitFlags.h \
    DProperty.h \
    Enumeration.h \
    EnumerationArray.h \
    EnumerationMask.h \
    FunctionInfo.h \
    Id.h \
    MinMaxTPair.h \
    MultiName.h \
    Named.h \
    NamedArray.h \
    NamedEnum.h \
    NamedMap.h \
    QQByteArray.h \
    QQColor.h \
    QQDir.h \
    QQFile.h \
    QQFileInfo.h \
    QQFileInfoList.h \
    QQImage.h \
    QQRect.h \
    QQRectF.h \
    QQRectList.h \
    QQSize.h \
    QQString.h \
    Rational.h \
    Real.h \
    RealMath.h \
    Region.h \
    Sortable.h \
    Value.h \
    ValuePak.h \
    Var.h \
    VarMap.h \
    VarMapMap.h \
    VarPak.h \
    VersionInfo.h \
    BasicName.h \
    Boolean.h \
    DualMap.h \
    Milliseconds.h \
    Success.h \
    eirType_global.h \
    eirType.h \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
