SUMMARY = "SpiDev Support for Python"
SECTION = "devel/python"

LICENSE = "GPL"
LIC_FILES_CHKSUM = "file://LICENSE.md;md5=54bdb9022ebb75ab68399cdaab97da60"

SRCNAME = "spidev"

SRC_URI = "https://pypi.python.org/packages/source/s/spidev/spidev-${PV}.tar.gz"
SRC_URI[md5sum] = "f601676f1bb48b9aa3b3897f95216365"

S = "${WORKDIR}/${SRCNAME}-${PV}"

inherit setuptools

RDEPENDS_${PN} = "\
    python-fcntl \
    python-io \
    python-stringold \
"