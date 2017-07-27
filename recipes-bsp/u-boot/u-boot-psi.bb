DESCRIPTION = "U-Boot provided by PsiControl for the Petersime iHMI board"
require recipes-bsp/u-boot/u-boot.inc

PROVIDES += "u-boot"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=1707d6db1d42237583f50183a5651ecb"

SRC_URI = "file://petersime_spl_firmware.14081.1.1.0.bin \
           file://COPYING"

LOCALVERSION = "2014.10-psicontrol"

UBOOT_BINARY = "petersime_spl_firmware.14081.1.1.0.bin"

do_compile () {
    cp ${WORKDIR}/petersime_spl_firmware.14081.1.1.0.bin ${WORKDIR}/build
}

S = "${WORKDIR}"

UBOOT_MACHINE = "petersime_ihmi"
COMPATIBLE_MACHINE = "(petersime-ihmi)"
