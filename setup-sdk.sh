#!/bin/bash
echo "Setting up gcc-arm-none-eabi..."
mkdir -p ~/opt/arm/
cd ~/opt/arm
wget https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
tar xzvf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
cp -r gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/* ./

echo "Setting up pico-sdk..."
mkdir -p ~/.pico_sdk
cd ~/.pico_sdk
wget https://github.com/raspberrypi/pico-sdk/releases/download/2.1.0/pico-sdk-2.1.0.tar.gz
tar xzvf pico-sdk-2.1.0.tar.gz

echo "Downloading build tools..."
sudo apt install cmake build-essential