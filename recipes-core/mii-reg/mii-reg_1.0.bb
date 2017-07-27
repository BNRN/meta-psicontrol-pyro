SUMMARY = "A user tool to read/write registers from micrel ksz8873 ethernet switch"
SECTION = "base"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=751419260aa954499f7abaabaa882bbe"

PR = "r0"

S = "${WORKDIR}"


SRC_URI = "file://mii-reg.c \
           file://GPLv2.patch \
"

do_compile() {
	${CC} ${CFLAGS} ${LDFLAGS} mii-reg.c -o mii-reg
}

do_install() {
	install -d ${D}${base_bindir}

	install -m 0755	${WORKDIR}/mii-reg	${D}${base_bindir}
}
