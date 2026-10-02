# NVMe Tool Kit #

## Getting Started

### bind uio driver to nvme device

* $ sudo ./scripts/setup_uio.sh 
or
* $ sudo ./scripts/setup_uio.sh config


### setup udma driver

* $ sudo ./scripts/setup_udma.sh 


### reset

* $ sudo ./scripts/setup_uio.sh reset
* $ sudo ./scripts/setup_udma.sh reset


## Build Options

### makefile

* $ sudo make all
* $ sudo ./build/nvmeTool  
* $ sudo make clean

### cmake

* $ sudo cmake -S . -B build
* $ cd build
* $ sudo make all
* $ sudo ./nvmeTool
* $ sudo make clean  
* $ sudo rm -rf build


## Troubleshoot

### module fail to build

error message: 
* "ERROR: Kernel configuration is invalid. include/generated/autoconf.h or include/config/auto.conf are missing. Run 'make oldconfig && make prepare' on kernel src to fix it."

solution:
* re-install linux-headers:
* shell$ sudo apt install --reinstall linux-headers-$(uname -r)


### device fail to bind

error message:
* uio_resource0_fd failed to open!

solution:
* run binary as superuser
* shell$ sudo ./build/nvmeTool

## Compatibility

Ubuntu 26.04.1 LTS
Linux 7.0.0-38-generic x86_64


ELY 2026
