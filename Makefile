all: test

test: boot.o kernel.o
	~/opt/cross/bin/i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o \
	kernel.o -lgcc

boot.o: boot.s
	~/opt/cross/i686-elf/bin/as boot.s -o boot.o

kernel.o: kernel.c
	~/opt/cross/bin/i686-elf-gcc -g -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
