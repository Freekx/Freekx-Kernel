#!/bin/tcsh

echo FREEKX KERNEL BUILD

if ( -d "./build/" ) then

echo clean build
rm -rf build
mkdir build

endif

if (! -d "./build/") then

echo new build
mkdir build

endif

clang -target i686-elf -std=c11 -ffreestanding -c ./src/C/kernel.c -o kernel.o
clang -target i686-elf -std=c11 -ffreestanding -c ./src/ASM/boot.asm -o boot.o

mv boot.o kernel.o ./build
cd ./build
pwd

ld.lld boot.o kernel.o -o freekx.bin

