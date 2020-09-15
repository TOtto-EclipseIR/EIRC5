TEMPLATE = subdirs

SUBDIRS += \
        ../../libs/eirXfr \
        ../../libs/eirBase \
        ../../libs/eirType \
        ../../libs/eirExe \
        ../../libs/eirCascade \
        ../../libs/eirQtCV \
        ../FaceConsole \


eirBase.depends     = eirXfr
eirType.depends     = eirBase eirXfr
eirExe.depends      = eirType eirBase ierXfr
eirCascade.depends  = eirExe eirType
eirQtCV.depends     = eirCascade eirExe eirType eirXfr
FaceConsole.depends = eirQtCV eirExe eirType eirBase eirXfr

