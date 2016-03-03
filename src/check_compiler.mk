#Check for system and the accordingly set compiler
UNAME_S := $(shell uname -s)

#Cross compiler location
CROSS_PREFIX := ~/opt/cross/bin/i686-elf-
CROSS_PREFIX := i386-elf-

#If system is linux
ifeq ($(UNAME_S),Linux)
	CC := $(CROSS_PREFIX)gcc
	AA := nasm
	LD := $(CROSS_PREFIX)gcc
	CT := ctags
	OC := $(CROSS_PREFIX)objcopy
endif

#If system is mac
ifeq ($(UNAME_S),Darwin)
	CC := $(CROSS_PREFIX)gcc
    AA := nasm
    LD := $(CROSS_PREFIX)gcc
	CT := ctags
	OC := $(CROSS_PREFIX)objcopy
endif

#C flags
CINCLUDES=-Iinclude/
CFLAGS := -g -std=gnu99 -ffreestanding -O2 -Wall -Wextra -ggdb

#Assembler flags
AFLAGS := -f elf

#Linker flags
LDFLAGS := -T linker.ld -ffreestanding -O2 -nostdlib -lgcc -g
