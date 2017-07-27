SUMMARY = "the u-boot fw_printenv and fw_setenv binaries"
DESCRIPTION = "Access the U-boot environment in Flash from within Linux"
LICENSE = "LGPLv2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=39ec502560ab2755c4555ee8416dfe42"

SRC_URI = "file://fw_printenv \
           file://fw_env.config \
           file://LICENSE"

S = "${WORKDIR}"
INSANE_SKIP_${PN} += "ldflags"
INSANE_SKIP_${PN} += "already-stripped"

do_install () {
    install -d ${D}${sysconfdir}
    install -m 644 ${WORKDIR}/fw_env.config ${D}${sysconfdir}/fw_env.config

    install -d ${D}${base_sbindir}
    install -m 755 ${S}/fw_printenv ${D}${base_sbindir}/fw_printenv
    install -m 755 ${S}/fw_printenv ${D}${base_sbindir}/fw_setenv
}