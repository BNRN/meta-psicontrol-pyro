SUMMARY = "modprobe blacklist config file"
DESCRIPTION = "A blacklist for the evbug messages appearing in dmesg"
LICENSE = "LGPLv2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=39ec502560ab2755c4555ee8416dfe42"

SRC_URI = "file://blacklist.conf.sample \
           file://LICENSE"

S = "${WORKDIR}"

do_install() {
	install -d ${D}${sysconfdir}/modprobe.d
	install -m 0755 ${WORKDIR}/blacklist.conf.sample ${D}${sysconfdir}/modprobe.d/blacklist.conf
}
