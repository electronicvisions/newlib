#!/bin/bash -x
set -o errexit

target="powerpc-ppu"

prefix="$PWD/install"

export PATH="$prefix/bin:$PATH"
export C_INCLUDE_PATH=""
export CPLUS_INCLUDE_PATH=""
export CPATH=""
export CPATH="$prefix/lib/gcc/$target/8.1.0/include:$CPATH"
export CPATH="$prefix/lib/gcc/$target/8.1.0/include-fixed:$CPATH"

newlib_options="--disable-multilib --enable-target-optspace"

CFLAGS="-ffunction-sections"

# check existance and version
which $target-as
$target-as --version

# check existance and version
which $target-gcc
$target-gcc --version

mkdir -p build_newlib
cd build_newlib

../newlib/configure --prefix=/ --target="$target" ${newlib_options}
make -j$(nproc) all-target-newlib
make DESTDIR="$prefix" install-target-newlib

cd ..
