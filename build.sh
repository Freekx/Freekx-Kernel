#!/bin/tcsh

echo FREEKX KERNEL BUILD

#if ( -e ".build/" ) then
#
#	echo clean build 
#	rm -rf build
#	mkdir build
#
#else 
#
#	echo new build
#	mkdir build
#
#endif

clang -target i686-elf -std=c11 -ffreestanding -c ./src/C/kernel.c -o kernel.o

clang -target i686-elf -std=c11 -ffreestanding -c ./src/ASM/boot.asm -o boot.o

clang -target i686-elf -T /bin/lld src/linker.lld -v -v -v boot.o kernel.o -o freekx.bin
