SUMMARY = "Serial Port Support for Python"
SECTION = "devel/python"

LICENSE = "PSF"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=c557c64905dac5b725980b9505bf8d7b"

SRCNAME = "pyserial"

SRC_URI = "https://pypi.python.org/packages/source/p/pyserial/pyserial-${PV}.tar.gz"
SRC_URI[md5sum] = "794506184df83ef2290de0d18803dd11"
SRC_URI[sha256sum] = "3542ec0838793e61d6224e27ff05e8ce4ba5a5c5cc4ec5c6a3e8d49247985477"

S = "${WORKDIR}/${SRCNAME}-${PV}"

inherit setuptools

RDEPENDS_${PN} = "\
    python-fcntl \
    python-io \
    python-stringold \
"