SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "CLOSED"

inherit update-rc.d

INITSCRIPT_NAME = "init_58100.sh"
INITSCRIPT_PARAMS = "start 99 2 3 4 5 ."

DEPENDS += "bash"
RDEPENDS:${PN} += "libgcc libstdc++ glibc"
RDEPENDS:${PN} += "bash"


SRC_URI = "file://init_58100.sh \
		file://init_58100 \
"


S = "${WORKDIR}"


do_install() {
    install -d ${D}${sysconfdir}/startup
    install -d ${D}${sysconfdir}/init.d

    install -m 0755 ${WORKDIR}/init_58100 ${D}${sysconfdir}/startup
    install -m 0755 ${WORKDIR}/init_58100.sh ${D}${sysconfdir}/init.d/
}



