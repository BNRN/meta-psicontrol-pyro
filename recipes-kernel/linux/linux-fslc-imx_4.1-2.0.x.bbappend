COMPATIBLE_MACHINE = "(petersime-ihmi|hotraco-hrfocus|petersime-ihmi-quad)"


# tell yocto to find files here to copy in the workdir
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

#TODO port patches for Micrel switch for PS iHMI board
SRC_URI += "file://hmi_board.dts \
            file://hmi_board_quad.dts \
            file://hotraco_hrfocus.dts \
            file://0003-fix-ethernet-clock-disable-output-bit-in-GPR1.patch \
            file://0008-add-SPI-Flash-type-Adesto-at26sf081a.patch \
            file://0009-prevent-division-by-zero-in-ipu-pixel-clk-driver.patch"

            
# then tell yocto to copy the copied dts file under the git linux dts folder
do_compile_prepend() {
       cp ${WORKDIR}/*.dts ${WORKDIR}/git/arch/arm/boot/dts/
}