global loader
extern kmain

MAGIC_NUMBER equ 0x1BADB002		;where the OS loaded
FLAGS		 equ 0x0
CHECKSUM	 equ -MAGIC_NUMBER
KERNEL_STACK_SIZE equ 4096

section .text:
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

loader:
	mov eax, 0xCAFEBABE

	mov esp, kernel_stack + KERNEL_STACK_SIZE
	call kmain
.loop:
	jmp .loop

section .bss
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE

