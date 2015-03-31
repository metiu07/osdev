#! /bin/sh

make
cp myos.bin ../isodir/boot/
cp myos.bin ../isodir/efi.img
grub-mkrescue ../isodir -o myos.iso
