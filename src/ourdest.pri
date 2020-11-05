# file: {EIRC2repo}./ourdest.pri

OURDEST = <base>/<bld>-<dbg>-<ver>-<trunk>
OURDEST = $$replace(OURDEST, <base>, $(QTBASEDESTDIR))
OURDEST = $$replace(OURDEST, <bld>, $$OURBLD)
CONFIG(debug, debug|release|profile) {
    OURDEST = $$replace(OURDEST, <dbg>, dbg)
}
CONFIG(release, debug|release|profile) {
    OURDEST = $$replace(OURDEST, <dbg>, bin)
}
CONFIG(profile, debug|release|profile) {
    OURDEST = $$replace(OURDEST, <dbg>, pro)
}
OURDEST = $$replace(OURDEST, <ver>, $$EIRC5_VER_STRING)
OURDEST = $$replace(OURDEST, <trunk>, $$EIRC5_VER_TRUNKNAME)
DESTDIR = $$OURDEST
LIBS *= -L$$OURDEST

#message(OURDEST = $$OURDEST)
