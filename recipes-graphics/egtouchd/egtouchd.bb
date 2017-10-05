SUMMARY = "egTouchD UART driver for eGalaxTouch products"
DESCRIPTION = "http://www.eeti.com.tw/LinuxDriverDownload.html"
LICENSE = "LGPLv2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=39ec502560ab2755c4555ee8416dfe42"

SRC_URI = "file://eGTouchD \
           file://eGTouchL.ini \
           file://eUpdatePro_ARMhf \
           file://Rocktouch_12p1_30x40_7856v1000_2pt_T1.egxp \
           file://LICENSE"

S = "${WORKDIR}"

do_install() {
	install -d ${D}${sysconfdir}
	install -d ${D}${sysconfdir}/rocktouch_calib
	install -m 0755 ${WORKDIR}/eGTouchL.ini ${D}${sysconfdir}/eGTouchL.ini
	install -m 0755 ${WORKDIR}/Rocktouch_12p1_30x40_7856v1000_2pt_T1.egxp ${D}${sysconfdir}/rocktouch_calib/Rocktouch_12p1_30x40_7856v1000_2pt_T1.egxp
    install -d ${D}${bindir}
	install -m 0755 ${WORKDIR}/eGTouchD ${D}${bindir}/eGTouchD
	install -m 0755 ${WORKDIR}/eUpdatePro_ARMhf ${D}${bindir}/eUpdatePro_ARMhf
    
}
