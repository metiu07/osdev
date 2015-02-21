#C compiler
CINCLUDES=-Iinclude/
CC := ~/opt/cross/bin/i686-elf-gcc
CFLAGS := -g -std=gnu99 -ffreestanding -O2 -Wall -Wextra

#Assembler
AA := /usr/local/bin/nasm
AFLAGS := -f elf

#Linker
LD := ~/opt/cross/bin/i686-elf-gcc
LDFLAGS := -T linker.ld -ffreestanding -O2 -nostdlib -lgcc

#Target
TARGET := myos.bin

#Directories
SRCDIRS := kernel lib keyboard shell 
ASMSOURCES := $(foreach DIR, $(SRCDIRS), $(wildcard $(DIR)/*.asm))
CSOURCES := $(foreach DIR, $(SRCDIRS), $(wildcard $(DIR)/*.c))
ASMOBJECTS := $(CSOURCES:%.c=%.c.o)
COBJECTS := $(ASMSOURCES:%.asm=%.asm.o)

.PHONY : all
all : $(TARGET)

#Linking
$(TARGET) : $(COBJECTS) $(ASMOBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^
	
#Compiling ASM Sources
%.asm.o : %.asm
	$(AA) $(AFLAGS) -o $@ $<

#Compiling C Sources
%.c.o : %.c
	$(CC) $(CFLAGS) $(CINCLUDES) -o $@ -c $<

#Remove executables and object files
clean : 
	$(RM) myos.bin
	$(foreach DIR, $(SRCDIRS), $(RM) $(DIR)/*.o)
