#!/bin/sh

#clean up first
rm -rf hotraco_delivery

mkdir -p hotraco_delivery

mkdir -p hotraco_delivery/kernel
cp recipes-kernel/linux/linux-fslc-imx/hotraco-hrfocus/defconfig hotraco_delivery/kernel/
cp recipes-kernel/linux/linux-fslc-imx/0003-fix-ethernet-clock-disable-output-bit-in-GPR1.patch hotraco_delivery/kernel/
cp recipes-kernel/linux/linux-fslc-imx/0008-add-SPI-Flash-type-Adesto-at26sf081a.patch hotraco_delivery/kernel
cp recipes-kernel/linux/linux-fslc-imx/0009-prevent-division-by-zero-in-ipu-pixel-clk-driver.patch hotraco_delivery/kernel

mkdir -p hotraco_delivery/devicetree
cp recipes-kernel/linux/linux-fslc-imx/hotraco_hrfocus.dts hotraco_delivery/devicetree/

mkdir -p hotraco_delivery/u-boot
cp recipes-bsp/u-boot/u-boot-psi-hotraco/*.bin hotraco_delivery/u-boot
cp recipes-bsp/u-boot/u-boot-psi-hotraco/environment hotraco_delivery/u-boot
cp recipes-bsp/u-boot-fw-utils/files/fw_env.config hotraco_delivery/u-boot
cp recipes-bsp/u-boot-fw-utils/files/fw_printenv hotraco_delivery/u-boot

mkdir -p hotraco_delivery/touchscreen_driver/
cp recipes-graphics/egtouchd/files/eGTouchD hotraco_delivery/touchscreen_driver/
cp recipes-graphics/egtouchd/files/eGTouchL.ini hotraco_delivery/touchscreen_driver/
cp recipes-graphics/egtouchd/files/eUpdatePro_ARMhf hotraco_delivery/touchscreen_driver/

tar czf hotraco_delivery_1.0.tar.gz hotraco_delivery