#!/bin/bash
# Builds for EVT 4

rm -rf build/evt4
mkdir build/evt4
export PICO_SDK_PATH=~/.pico_sdk
export PICO_TOOLCHAIN_PATH=~/opt/arm/bin
cd build/evt4
cmake -D_MODEL=EVT4 ../..
BOARD=PICO_R1_3 RELEASE=1 make -j4
