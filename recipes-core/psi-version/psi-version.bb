SUMMARY = "modprobe blacklist config file"
DESCRIPTION = "A blacklist for the evbug messages appearing in dmesg"
LICENSE = "LGPLv2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=39ec502560ab2755c4555ee8416dfe42"

SRC_URI = "file://version \
           file://LICENSE"

S = "${WORKDIR}"

DATE_NOW = "${@time.strftime('%Y-%m-%d %H:%M:%S',time.gmtime())}"

do_install() {
	install -d ${D}${bindir}
	install -m 0755 ${WORKDIR}/version ${D}${bindir}/version
    
    
    echo "\n\n echo built @ ${DATE_NOW}" >> ${D}${bindir}/version
}
