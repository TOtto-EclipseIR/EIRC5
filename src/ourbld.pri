# file: {EIRC2repo}./ourbld.pri

OURBLD = "{???}"
windows:OURBLD = "windows"

contains(QMAKE_TARGET.arch, x86_64):{
    OURBLD = "win64-msvc"
#    message( "Building for 64 bit")
}
! contains(QMAKE_TARGET.arch, x86_64):{
    OURBLD = "win32-msvc"
#    message( "Building for 64 bit")
}
#message(OURBLD = $$OURBLD)
