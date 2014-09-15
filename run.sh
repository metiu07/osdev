#! /bin/sh

make
qemu-system-x86_64 -s -kernel myos.bin
