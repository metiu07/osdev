#! /bin/sh

make
qemu-system-x86_64 -kernel myos.bin
