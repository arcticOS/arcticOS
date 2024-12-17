#!/bin/bash
echo "Setting up gcc-arm-none-eabi..."
mkdir -p ~/opt/arm/
cd ~/opt/arm
wget https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
tar xzvf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
cp -r gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/* ./

echo "Setting up pico-sdk..."
cd ~
git clone git@github.com:raspberrypi/pico-sdk
mv pico-sdk .pico_sdk
cd .pico_sdk
git submodule update --init

echo "Downloading build tools..."
sudo apt install cmake build-essential