SUMMARY = "library with testcommands for PsiControl testsystem"
DESCRIPTION = "python linuxtestlib.py COMMAND"
LICENSE = "LGPLv2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=39ec502560ab2755c4555ee8416dfe42"

SRC_URI = "file://15015.0.0.14.zip \
           file://LICENSE"

S = "${WORKDIR}"

do_install() {
	install -d ${D}/home/root
	install -d ${D}/home/root/lib
    install -m 0755	${WORKDIR}/__init__.py	${D}/home/root/
    install -m 0755	${WORKDIR}/version.py	${D}/home/root/
    install -m 0755	${WORKDIR}/Commands.py	${D}/home/root/
    install -m 0755	${WORKDIR}/linuxtestlib.py	${D}/home/root/
    install -m 0755	${WORKDIR}/lib/__init__.py	${D}/home/root/lib/
    install -m 0755	${WORKDIR}/lib/TypeChecking.py	${D}/home/root/lib/
    install -m 0755	${WORKDIR}/lib/utils.py	${D}/home/root/lib/
}

FILES_${PN} = "/home/root"

RDEPENDS_${PN} = "python psi-version u-boot-fw-utils i2c-tools python-misc net-tools mtd-utils memtester"
PROVIDES += "linuxtestlib"