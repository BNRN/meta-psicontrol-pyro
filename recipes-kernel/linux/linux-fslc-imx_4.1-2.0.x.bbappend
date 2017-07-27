COMPATIBLE_MACHINE = "(petersime-ihmi)"

# tell yocto to find files here to copy in the workdir
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://hmi_board.dts \
            file://hmi_board_quad.dts \
            file://0003-fix-ethernet-clock-disable-output-bit-in-GPR1.patch"

# then tell yocto to copy the copied dts file under the git linux dts folder
do_compile_prepend() {
       cp ${WORKDIR}/*.dts ${WORKDIR}/git/arch/arm/boot/dts/
}


#file://0001-changes-for-micrel-ksz8873-switch.patch 
#file://0002-implemented-SMI-protocol-over-MDIO-using-temporary-b.patch 
#file://0005-workaround-execute-ifconfig-ethX-up-when-link-comes-.patch
#file://0004-lower-drive-strength-of-the-I2C-busses.patch
#file://0006-ENGR00304402-video-mxc-LDB-Enable-LDB-channel-after-.patch
#file://0007-ilitek-driver-customised-Psi.patch