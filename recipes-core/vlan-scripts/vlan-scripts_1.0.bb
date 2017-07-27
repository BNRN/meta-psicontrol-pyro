SUMMARY = "shell scripts used for initializing micrel switch and route tables"
SECTION = "base"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=751419260aa954499f7abaabaa882bbe"

PR = "r0"

S = "${WORKDIR}"


SRC_URI = "file://petersime-switch.sh \
           file://petersime-route.sh \
		   file://petersime-vlan.sh \
           file://GPLv2.patch \
"


do_install() {
	install -d ${D}${datadir}/vlan-scripts

	install -m 0755	${WORKDIR}/petersime-switch.sh	${D}${datadir}/vlan-scripts
	install -m 0755	${WORKDIR}/petersime-route.sh	${D}${datadir}/vlan-scripts
	install -m 0755	${WORKDIR}/petersime-vlan.sh	${D}${datadir}/vlan-scripts
}
