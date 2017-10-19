SUMMARY = "Qt5 demo 10 inch"
DESCRIPTION = "Demo for 10 inch display"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=751419260aa954499f7abaabaa882bbe"

SRC_URI += "file://GPLv2.patch \
            file://QtDemo-Picanol-0.5.zip"
            
S = "${WORKDIR}"


DEPENDS = "qtdeclarative qtgraphicaleffects qtwebkit qtquickcontrols"
RDEPENDS_${PN} = "qtdeclarative-qmlplugins qtgraphicaleffects-qmlplugins qtquickcontrols-qmlplugins"

require recipes-qt/qt5/qt5.inc

do_install() {
    install -d ${D}${datadir}/${P}
    install -m 0755 ${B}/display/application/application ${D}${datadir}/${P}/QtDemoPicanol    
    cp ${S}/display/application/allIdFile.rc ${D}${datadir}/${P}
    
    install -d ${D}${datadir}/${P}/ModelPlugin
    install -m 0755 ${B}/display/model_plugin/libModelPlugin.so ${D}${datadir}/${P}/ModelPlugin
    cp ${S}/display/model_plugin/qmldir ${D}${datadir}/${P}/ModelPlugin
   
}

INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"

FILES_${PN}-dbg += "${datadir}/${P}/.debug"
FILES_${PN} += "${datadir}/${P}/QtDemoPicanol ${datadir}"
