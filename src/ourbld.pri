# file: {EIRC2repo}./ourbld.pri

#message(QMAKE_CXX = $$QMAKE_CXX)

OURBLD = "{???}"
windows:{
    OURBLD = "win<bits><spec>"

    contains(QMAKE_TARGET.arch, x86_64):{
        OURBLD = $$replace(OURBLD, <bits>, 64)
    } else {
        OURBLD = $$replace(OURBLD, <bits>, 32)
    }

    equals(QMAKE_CXX, "g++"): {
        OURBLD = $$replace(OURBLD, <spec>, G)
    }
    equals(QMAKE_CXX, "cl"): {
        OURBLD = $$replace(OURBLD, <spec>, V)
    }
}
#message(OURBLD = $$OURBLD)
