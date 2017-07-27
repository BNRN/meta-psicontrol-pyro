SUMMARY = "Qt5 color test"
DESCRIPTION = "Simple colortest application for petersime"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=751419260aa954499f7abaabaa882bbe"

SRC_URI += "file://ColorTest.qml \
            file://Error.qml \
            file://GPLv2.patch \
            file://main.cpp \
            file://main.qml \
            file://mainview.cpp \
            file://mainview.h \
            file://PetersimeColorTest.pro \
            file://qml.qrc \
            file://Qt5_CinematicExperience.qml \
            file://resultlogger.h \
            file://resultlogger.cpp \
            file://SendColorTestResult.sh \
            file://content.tar \
            "
            
S = "${WORKDIR}"


DEPENDS = "qtdeclarative qtgraphicaleffects"
RDEPENDS_${PN} = "qtdeclarative-qmlplugins qtgraphicaleffects-qmlplugins"

require recipes-qt/qt5/qt5.inc

do_install() {
    install -d ${D}${datadir}/${P}
    install -m 0755 ${B}/PetersimeColorTest ${D}${datadir}/${P}
    cp -a ${S}/content ${D}${datadir}/${P}
    install -m 0755 ${S}/SendColorTestResult.sh ${D}${datadir}/${P}
    install -m 0644 ${S}/*.qml ${D}${datadir}/${P}
    
    install -d ${D}${bindir}
    install -m 0755 ${S}/SendColorTestResult.sh ${D}${bindir}
    echo "#!/bin/sh" > ${D}${bindir}/PetersimeColorTest
    echo "export QML_IMPORT_PATH=${datadir}/${P}" >> ${D}${bindir}/PetersimeColorTest
    echo "export QML2_IMPORT_PATH=${datadir}/${P}" >> ${D}${bindir}/PetersimeColorTest
    echo "${datadir}/${P}/PetersimeColorTest \$* " >> ${D}${bindir}/PetersimeColorTest
    chmod +x ${D}${bindir}/PetersimeColorTest

}

FILES_${PN}-dbg += "${datadir}/${P}/.debug"
FILES_${PN} += "${datadir}"