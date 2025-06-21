extern exit

section .note.GNU-stack

section .data
	file db 'data.txt',0

section .bss
	buf resb 20
	fd  resb 1

section .text
	global main

main:
	;open file
	mov eax, 5
	mov ebx, file
	mov ecx, 0
	int 80h

	;store file descriptor
	mov [fd], eax

	;lseek file
	mov ebx, [fd]
	mov eax, 19
	mov ecx, 20
	mov edx, 0
	int 80h

	;read file
	mov eax, 3
	mov ebx, [fd]
	mov ecx, buf
	mov edx, 10
	int 80h

	;output to stdout
	mov eax, 4
	mov ebx, 1
	mov ecx, buf
	mov edx, 10
	int 80h

	;close file
	mov eax, 6
	mov ebx, [fd]
	int 80h

end:
	call exit
