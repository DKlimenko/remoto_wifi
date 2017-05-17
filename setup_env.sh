
#please make sure to connect to the company proxy server before launching script
echo "Installing OpenWRT toolchain"
TOOLCHAIN_URL="http://downloads.openwrt.org/attitude_adjustment/12.09-rc1/ar71xx/generic/OpenWrt-Toolchain-ar71xx-for-mips_r2-gcc-4.6-linaro_uClibc-0.9.33.2.tar.bz2"
TOOLCHAIN_FILE_NAME="OpenWrt-Toolchain-ar71xx-for-mips_r2-gcc-4.6-linaro_uClibc-0.9.33.2.tar.bz2"
TOOLCHAIN_FOLDER_PATH="${HOME}/OpenWrt-Toolchain"
if [[ -d "${TOOLCHAIN_FOLDER_PATH}" ]]; then
    echo "OpenWRT toolchain is already installed"
else
    if [ ! -d "${TOOLCHAIN_FOLDER_PATH}" ]; then
        mkdir "${TOOLCHAIN_FOLDER_PATH}"
    fi

    echo "Downloading OpenWRT toolchain..."
    wget -P ${TOOLCHAIN_FOLDER_PATH} ${TOOLCHAIN_URL}

    echo "Unzipping..."
    cd "${TOOLCHAIN_FOLDER_PATH}"
    tar -jxf "${TOOLCHAIN_FILE_NAME}"
    rm "${TOOLCHAIN_FILE_NAME}"

    echo "Done"
fi


#export STAGING_DIR=/home/dklimenko/projects/github/remoto_wifi_build/external/openwrt/toolchain