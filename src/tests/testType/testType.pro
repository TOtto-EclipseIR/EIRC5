QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -leirType5
include(../../EIRC2.pri)

SOURCES +=  tst_multiname.cpp
