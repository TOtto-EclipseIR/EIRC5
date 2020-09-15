# file: {EIRC2repo}./ourdest.pri

OURDEST = <base>/<bld>-<dbg>-<ver>
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
OURDEST = $$replace(OURDEST, <ver>, $$EIRC2_VER_STRING)
DESTDIR = $$OURDEST
LIBS *= -L$$OURDEST

#message(OURDEST = $$OURDEST)
