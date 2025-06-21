
section .note.GNU-stack
extern exit

section .data
	fname db 'test_f.txt',0
	msg db 'write file message',0ah,0dh,'$'
	len equ $-msg

section .bss
	fd resb 1	;file descriptor
	file_msg resb 30	;buffer store data from file

section .text
	global main

main:
	mov eax, 8			;create file
	mov ebx, fname
	mov ecx, 0o777
	int 80h

	mov [fd], eax		;move file descriptor to reserved space			

	;write file
	mov eax, 4
	mov ebx, [fd]
	mov ecx, msg
	mov edx, len
	int 80h

	;close file
	mov eax, 6
	mov ebx, [fd]
	int 80h

	;open file
	mov eax, 5
	mov ebx, fname
	mov ecx, 0
	mov edx, 0o777
	int 80h

	mov [fd], eax

	;read file
	mov eax, 3
	mov ebx, [fd]
	mov ecx, file_msg
	mov edx, 20
	int 80h

	;close file
	mov eax, 6
	mov ebx, [fd]
	int 80h
	
	;output message to stdout
	mov eax, 4
	mov ebx, 1
	mov ecx, file_msg
	mov edx, 20
	int 80h

end:
	call exit
