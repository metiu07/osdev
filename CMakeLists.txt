cmake_minimum_required(VERSION 2.8.11)
project(test)

include(CMakeForceCompiler)
#SET(CMAKE_SYSTEM_NAME Generic)
#set(CMake_LINKER ~/opt/cross/bin/i686-elf-gcc)
#CMAKE_FORCE_LINKER(/home/mato/opt/cross/bin/i686-elf-gcc linker)
CMAKE_FORCE_C_COMPILER(/home/mato/opt/cross/bin/i686-elf-gcc gcc)
set(CMAKE_C_FLAGS "-g -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra")
set(CMAKE_LINK_FLAGS "-T linker.ld -ffreestanding -O2 -nostdlib -lgcc")
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
#SET(CMAKE_C_EXECUTABLE "~/opt/cross/bin/i686-elf-gcc <OBJECTS> -o  <TARGET> <CMAKE_C_FLAGS> ")
#SET(CMAKE_C_LINK_EXECUTABLE "~/opt/cross/bin/i686-elf-gcc <LINK_FLAGS> <OBJECTS> -o  <TARGET> <CMAKE_C_LINK_FLAGS> <LINK_LIBRARIES>")
enable_language(ASM_NASM)


# ~/opt/cross/bin/i686-elf-gcc -T linker.ld -ffreestanding -O2 -nostdlib -lgcc CMakeFiles/myos.bin.dir/boot.asm.o CMakeFiles/myos.bin.dir/kernel.c.o  -o myos.bin


add_executable(myos.bin boot.asm kernel.c)
