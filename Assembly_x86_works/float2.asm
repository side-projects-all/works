section .data
	x dd 3.14
	y dd 2.1

section .bss

section .text
	global _start

_start:
	movss xmm0, [x]
	movss xmm1, [y]
	ucomiss xmm0, xmm1
	jl greater
	jmp end

greater:
	mov ecx, 1

end:
	mov eax, 1
	int 80h
