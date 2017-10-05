COMPATIBLE_MACHINE = "(petersime-ihmi|hotraco-hrfocus)"


# tell yocto to find files here to copy in the workdir
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

#TODO port patches for Micrel switch for PS iHMI board
SRC_URI += "file://hmi_board.dts \
            file://hmi_board_quad.dts \
            file://hotraco_hrfocus.dts \
            file://0003-fix-ethernet-clock-disable-output-bit-in-GPR1.patch"

            
# then tell yocto to copy the copied dts file under the git linux dts folder
do_compile_prepend() {
       cp ${WORKDIR}/*.dts ${WORKDIR}/git/arch/arm/boot/dts/
}