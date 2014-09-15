#! /bin/sh

make
qemu-system-x86_64 -c -kernel myos.bin
