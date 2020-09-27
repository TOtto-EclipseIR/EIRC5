TEMPLATE = subdirs

SUBDIRS += \
        ../../libs/eirXfr \
        ../../libs/eirBase \
        ../../libs/eirType \
        ../../libs/eirWgt \
        ../../libs/eirExe \
        ../../libs/eirImage \
        ../../libs/eirQtCV \
        ../../libs/eirObjDet \
        ../../tests/testXfr \
        ../FaceConsole \


eirBase.depends     = eirXfr
eirType.depends     = eirBase eirXfr
eirWgt.depends      = eirType eirBase eirXfr
eirExe.depends      = eirType eirBase ierXfr
eirQtCV.depends     = eirExe eirType eirBase eirXfr
eirObjDet.depends   = eirQtCV eirExe eirType eirBase eirXfr
eirImage.depends    = eirObjDet eirQtCV eirExe eirType eirXfr
FaceConsole.depends = eirImage eirObjDet eirQtCV eirExe eirType eirBase eirXfr

