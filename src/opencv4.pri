# file: {EIRC2repo}./src/opencv4.pri

INCLUDEPATH *= $(QTCVINCLUDEPATH)
LIBS *= -L$(QTCVLIBPATH)
CONFIG(debug, debug|release) {
    LIBS *= -lopencv_world$(QTCVFILENAMEVER)d
    DISTFILES *= $(QTCVLIBPATH)/../bin/opencv_world$(QTCVFILENAMEVER)d.dll
} else {
    LIBS *= -lopencv_world$(QTCVFILENAMEVER)
    DISTFILES *= $(QTCVLIBPATH)/../bin/opencv_world$(QTCVFILENAMEVER).dll
}
#message(INCLUDEPATH = $${INCLUDEPATH})
#message(LIBS = $${LIBS})
#message(DISTFILES = $${DISTFILES})
