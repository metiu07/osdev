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

#Target - name of executable
TARGET := myos.bin

#Directories
SRCDIRS := kernel lib keyboard shell 
ASMSOURCES := $(foreach DIR, $(SRCDIRS), $(wildcard $(DIR)/*.asm))
CSOURCES := $(foreach DIR, $(SRCDIRS), $(wildcard $(DIR)/*.c))
ASMOBJECTS := $(CSOURCES:%.c=%.c.o)
COBJECTS := $(ASMSOURCES:%.asm=%.asm.o)

#Default target
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

#Run Qemu with os binary
qemu : $(TARGET)
	qemu-system-i386 -s -kernel myos.bin

#Run Qemu in debug mode -> default $gdb myos.bin
#								   $target remote localhost:1234
qemu-debug : $(TARGET)
	qemu-system-i386 -s -S -kernel myos.bin

#Run Qemu in curses mode
qemu-curses : $(TARGET)
	qemu-system-i386 -s -curses -kernel myos.bin

#Remove executables and object files
clean : 
	$(RM) myos.bin
	$(foreach DIR, $(SRCDIRS), $(RM) $(DIR)/*.o)
