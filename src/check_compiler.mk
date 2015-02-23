#Check for system and the accordingly set compiler
UNAME_S := $(shell uname -s)

#If system is linux
ifeq ($(UNAME_S),Linux)
	CC := ~/opt/cross/bin/i686-elf-gcc
	AA := nasm
	LD := ~/opt/cross/bin/i686-elf-gcc
endif

#If system is mac
ifeq ($(UNAME_S),Darwin)
	CC := ~/opt/cross/bin/i686-elf-gcc
    AA := /usr/local/bin/nasm
    LD := ~/opt/cross/bin/i686-elf-gcc
endif


#C flags
CINCLUDES=-Iinclude/
CFLAGS := -g -std=gnu99 -ffreestanding -O2 -Wall -Wextra

#Assembler flags
AFLAGS := -f elf

#Linker flags
LDFLAGS := -T linker.ld -ffreestanding -O2 -nostdlib -lgcc