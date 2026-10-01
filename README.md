# NVMe Tool Kit #


## Getting started

### bind uio driver to nvme device

  $ sudo ./scripts/setup_uio.sh 
  or
  $ sudo ./scripts/setup_uio.sh config


### setup udma driver

  $ sudo ./scripts/setup_udma.sh 


### reset

  $ sudo ./scripts/setup_uio.sh reset
  $ sudo ./scripts/setup_udma.sh reset


## build options

### MakeFile

  $ sudo make all
  $ sudo ./build/nvmeTool  
  $ sudo make clean

### CMake

  $ sudo cmake -B ./build
  $ cd build
  $ sudo make all
  $ sudo ./nvmeTool
  $ sudo make clean  


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



ELY 2026
