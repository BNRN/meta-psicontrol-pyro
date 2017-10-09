DESCRIPTION = "U-Boot provided by PsiControl for the Petersime iHMI board"
require recipes-bsp/u-boot/u-boot.inc

PROVIDES += "u-boot"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=1707d6db1d42237583f50183a5651ecb"

SRC_URI = "file://hotraco_spl_firmware.17065.0.0.2.bin \
           file://COPYING"

LOCALVERSION = "2014.10-psicontrol"

UBOOT_BINARY = "hotraco_spl_firmware.17065.0.0.2.bin"

do_compile () {
    cp ${WORKDIR}/hotraco_spl_firmware.17065.0.0.2.bin ${WORKDIR}/build
}

S = "${WORKDIR}"

UBOOT_MACHINE = "hotraco-hrfocus"
COMPATIBLE_MACHINE = "(hotraco-hrfocus)"
