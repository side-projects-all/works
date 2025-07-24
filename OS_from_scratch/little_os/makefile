
C_COMPILER = gcc
C_FLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror

LD_FLAGS = -T link.ld -melf_i386
ASM_COMPILER = nasm
ASM_FLAGS = -f elf32

KERNEL = kernel.elf
IMAGE = myos.iso

$(IMAGE): $(KERNEL)
	mv $(KERNEL) ./iso_files/boot/
	grub-mkrescue -o ./iso_files/$(IMAGE) ./iso_files/

$(KERNEL): loader.o kmain.o video.o 
	ld $(LD_FLAGS) loader.o kmain.o video.o -o $(KERNEL)

loader.o: loader.s 
	$(ASM_COMPILER) $(ASM_FLAGS) loader.s -o loader.o

kmain.o: kmain.c
	$(C_COMPILER) $(C_FLAGS) -c kmain.c -o kmain.o

video.o: video.c
	$(C_COMPILER) $(C_FLAGS) -c video.c -o video.o

clean:
	rm *.o ./iso_files/boot/$(KERNEL) ./iso_files/$(IMAGE)

