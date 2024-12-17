#!/bin/bash
# Builds for EVT 5

rm -rf build/evt5
mkdir build/evt5
export PICO_SDK_PATH=~/.pico_sdk
export PICO_TOOLCHAIN_PATH=~/opt/arm/bin
cd build/evt5
cmake -D_MODEL=EVT5 ../..
BOARD=PICO_R1_3 RELEASE=1 make -j4
