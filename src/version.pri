# file: {EIRC2 repo}./src/version.pri

EIRC2_VER_MAJOR = 5
EIRC2_VER_MINOR = 9
EIRC2_VER_RELEASE = 163
EIRC2_VER_BRANCH = 0
EIRC2_VER_STRING = "v5.09-Alpha3"
EIRC2_VER_TRUNKNAME = "develop"
EIRC2_VER_BRANCHNAME = ""
EIRC2_VER_QT = $${QT_VERSION}

windows:VERSION = 5.9.163.0
!windows:VERSION = 5.9.0
VER_MAJ = $${EIRC2_VER_MAJOR}
VER_MIN = $${EIRC2_VER_MINOR}
VER_PAT = $${EIRC2_VER_BRANCH}

#message("Version = $${EIRC2_VER_STRING}+$${EIRC_VER_BRANCHNAME} $${EIRC2_VER_TRUNKNAME}")
#message("QMAKESPEC = $${QMAKESPEC}")
