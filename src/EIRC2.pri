# file: {EIRC2 repo}./src/EIRC2.pri

#message(QT5INCLUDEBASE = $$(QT5INCLUDEBASE))
#message(QTBASEDESTDIR = $$(QTBASEDESTDIR))
#message(QTCVINCLUDEPATH = $$(QTCVINCLUDEPATH))
###message(PATH = $$(PATH))

#DEFINES *= QTCV_SETTINGS_HACK
include(version.pri)
include(ourbld.pri)
include(ourdest.pri)
include(ipath.pri)

#message(OURDEST = $$OURDEST)
#message(LIBS = $$LIBS)
