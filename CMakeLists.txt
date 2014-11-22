cmake_minimum_required(VERSION 2.8.11)

PROJECT(kernel C ASM_NASM)
SET(CMAKE_VERBOSE_MAKEFILE ON)

INCLUDE(CMakeForceCompiler)
CMAKE_FORCE_C_COMPILER(/home/mato/opt/cross/bin/i686-elf-gcc gcc)
SET(CMAKE_C_FLAGS "-g -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra")
SET(CMAKE_EXE_LINKER_FLAGS "-T linker.ld -ffreestanding -O2 -nostdlib -lgcc")
SET(CMAKE_ASM_NASM_FLAGS "-felf")

enable_language(ASM_NASM)

add_executable(myos.bin boot.asm kernel.c)


