SUMMARY = "A user tool to read/write registers from the processor"
SECTION = "base"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=39ec502560ab2755c4555ee8416dfe42"

PR = "r0"

S = "${WORKDIR}"


SRC_URI = "file://x.c \
           file://mfill.c \           
           file://LICENSE"

do_compile() {
	${CC} ${CFLAGS} ${LDFLAGS} x.c -o x
	${CC} ${CFLAGS} ${LDFLAGS} mfill.c -o mfill
}

do_install() {
	install -d ${D}${base_bindir}

	install -m 0755	${WORKDIR}/x	${D}${base_bindir}
	install -m 0755	${WORKDIR}/mfill	${D}${base_bindir}
}
