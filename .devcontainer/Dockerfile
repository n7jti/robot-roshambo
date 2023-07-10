FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive && apt-get -y install --no-install-recommends \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    build-essential \
    libstdc++-arm-none-eabi-newlib \
    ninja-build \
    gdb-multiarch \
    automake \
    autoconf \
    texinfo \
    libtool \
    libftdi-dev \
    libusb-1.0-0-dev

RUN git clone https://github.com/raspberrypi/pico-sdk.git /pico/pico-sdk && \
    cd /pico/pico-sdk && \
    git submodule update --init

ENV PICO_SDK_PATH=/pico/pico-sdk

RUN git clone https://github.com/raspberrypi/openocd.git --branch rp2040 --depth=1 /pico/openocd && \
    cd /pico/openocd && \
    ./bootstrap && \
    ./configure && \
    make -j$(nproc)
