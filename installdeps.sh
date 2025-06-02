#!/usr/bin/bash

checkdeps() {
    for dep in "$@"; do
        case "$distro_id" in
        debian | ubuntu)
            if ! dpkg -s "$dep" >/dev/null 2>&1; then
                sudo apt-get install "$1" -y
            fi
            ;;
        fedora | centos | rhel)
            if ! rpm -q "$dep" >/dev/null 2>&1; then
                sudo dnf install -y "$1" || sudo yum install -y "$dep"
            fi
            ;;
        arch | mingw)
            if ! pacman -Q "$dep" >/dev/null 2>&1; then
                sudo pacman -S "$dep" --noconfirm
            fi
            ;;
        *)
            echo "Unsupported System"
            exit 1
            ;;
        esac
    done
}

checkalldeps() {
    case "$distro_id" in
    debian | ubuntu)
        checkdeps "build-essential" "libpng-dev" "gcc-arm-none-eabi" "binutils-arm-none-eabi" "libnewlib-arm-none-eabi" "python3"
        ;;
    fedora | centos | rhel)
        checkdeps "glibc-devel" "plocate" "make" "clear" "gcc" "c++" "libpng-devel" "arm-none-eabi-gcc" "arm-none-eabi-binutils" "arm-none-eabi-newlib" "python3"
        ;;
    arch)
        checkdeps "base-devel" "libpng" "arm-none-eabi-gcc" "arm-none-eabi-binutils" "arm-none-eabi-newlib" "python"
        ;;
    mingw)
        checkdeps "make" "mingw-w64-x86_64-toolchain" "mingw-w64-x86_64-arm-none-eabi-toolchain" "mingw-w64-x86_64-libpng" "python3"
        ;;
    *)
        echo "Unsupported Linux distribution: $distro_id"
        exit 1
        ;;
    esac
}

if [[ "$(uname -s)" == "Linux" ]]; then
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        distro_id="$ID"
    else
        distro_id="unknown"
    fi
elif [[ "$(uname -s)" == "Darwin" ]]; then
    distro_id="macos"
elif [[ "$(uname -s)" == *"MINGW64"* ]] || [[ "$(uname -s)" == *"MSYS"* ]]; then
    distro_id="mingw"
else
    distro_id="unknown"
fi
checkalldeps
