extern test
extern exit
extern printf

section .note.GNU-stack

section .data
	fmt   	   db '%d',10,0
	star  	   db '*',0
	new_line  db 10,0
section .bss

section .text
	global main

main:
	push 1
	push 2
	call test
	push eax
	mov ebx, fmt
	push ebx
	call printf
	pop ebx
	pop ebx
	pop eax
	pop eax
	
	mov ecx, 1
	mov edx, star

loop:
	cmp ecx, 5
	jg end

	mov ebx, 1
inner_loop:
	cmp ebx, ecx
	jg end_inner

	push ebx
	push ecx
	push edx

	call printf

	pop edx
	pop ecx
	pop ebx

	inc ebx
	jmp inner_loop

end_inner:

	push eax
	push ebx
	push ecx
	push edx

	mov edx, new_line
	push edx

	call printf
	
	pop edx
	pop edx
	pop ecx
	pop ebx
	pop eax

	inc ecx
	jmp loop

end:
	call exit
