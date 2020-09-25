QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

LIBS += -leirXfr5
include(../../EIRC2.pri)

TEMPLATE = app

SOURCES +=  tst_eirxfr.cpp
