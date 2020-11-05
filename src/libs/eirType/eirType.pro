# QT -= gui ### QImage
QT += network

TEMPLATE = lib
DEFINES += EIRTYPE_LIBRARY

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(../../EIRC2.pri)

LIBS *= -leirXfr5
LIBS *= -leirBase5

SOURCES += \
    Enumeration.cpp \
    FunctionInfo.cpp \
    Id.cpp \
    JsonItem.cpp \
    MultiName.cpp \
    Palette.cpp \
    QQByteArray.cpp \
    QQColor.cpp \
    QQDir.cpp \
    QQFile.cpp \
    QQFileInfo.cpp \
    QQFileInfoList.cpp \
    QQImage.cpp \
    QQPoint.cpp \
    QQRect.cpp \
    QQRectF.cpp \
    QQRectList.cpp \
    QQSize.cpp \
    QQString.cpp \
    QQStringList.cpp \
    QQStringStdList.cpp \
    Ratio32.cpp \
    Rational.cpp \
    Real.cpp \
    RealMath.cpp \
    Region.cpp \
    Sortable.cpp \
    BitFlags.cpp \
    SystemId.cpp \
    Value.cpp \
    ValueMap.cpp \
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
    BitFlags.h \
    DProperty.h \
    Enumeration.h \
    EnumerationArray.h \
    EnumerationMask.h \
    FunctionInfo.h \
    Id.h \
    JsonItem.h \
    MinMaxTPair.h \
    MultiName.h \
    Named.h \
    NamedArray.h \
    NamedEnum.h \
    NamedMap.h \
    Palette.h \
    QQByteArray.h \
    QQColor.h \
    QQDir.h \
    QQFile.h \
    QQFileInfo.h \
    QQFileInfoList.h \
    QQImage.h \
    QQList.h \
    QQPoint.h \
    QQRect.h \
    QQRectF.h \
    QQRectList.h \
    QQSize.h \
    QQString.h \
    QQStringList.h \
    QQStringStdList.h \
    Ratio32.h \
    Rational.h \
    Real.h \
    RealMath.h \
    Region.h \
    Sortable.h \
    SystemId.h \
    Value.h \
    ValueMap.h \
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
