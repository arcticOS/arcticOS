#!/bin/bash
# Builds for EVT 4

rm -rf build
mkdir build
export PICO_SDK_PATH=~/.pico_sdk
export PICO_TOOLCHAIN_PATH=~/opt/arm/bin
cd build
cmake -D_MODEL=EVT3 ..
BOARD=PICO_R1_3 RELEASE=1 make -j4
