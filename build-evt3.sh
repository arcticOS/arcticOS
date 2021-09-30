#!/bin/bash
# Builds for EVT 3

rm -rf build/evt3
mkdir build/evt3
export PICO_SDK_PATH=~/.pico_sdk
export PICO_TOOLCHAIN_PATH=~/opt/arm/bin
cd build/evt3
cmake -D_MODEL=EVT3 ../..
BOARD=PICO_R1_3 RELEASE=1 make -j4
