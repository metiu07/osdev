#Target - name of executable
TARGET := myos.bin

#Check for operating system and determine compiler
include check_compiler.mk

#Directories
SRCDIRS := kernel lib keyboard shell 
ASMSOURCES := $(foreach DIR, $(SRCDIRS), $(wildcard $(DIR)/*.asm))
CSOURCES := $(foreach DIR, $(SRCDIRS), $(wildcard $(DIR)/*.c))
COBJECTS := $(CSOURCES:%.c=%.c.o)
ASMOBJECTS := $(ASMSOURCES:%.asm=%.a.o)

#Default target
.PHONY : all
all : $(TARGET)

#Linking
$(TARGET) :  $(ASMOBJECTS) $(COBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^
	
#Compiling ASM Sources
%.a.o : %.asm
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

#Generate ctags file
ctags : 
	$(CT) -R .

#Remove executables and object files
clean : 
	$(RM) myos.bin
	$(foreach DIR, $(SRCDIRS), $(RM) $(DIR)/*.o)
