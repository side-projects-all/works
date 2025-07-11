section .data
	ttydev db "/dev/tty",0
	msg db "Type keys (q to quit):",10
	msglen equ $-msg
	msgbye db 10,"Bye!",10
	msgbyelen equ $-msgbye

;section .note.GNU-stack 
section .bss
old_termios resb 60
raw_termios resb 60
buf resb 1
ttyfd resd 1

section .text
global _start ;main

;main:
_start:
	; open /dev/tty to get fd
	mov rax, 2
	mov rdi, ttydev
	mov rsi, 2
	syscall
	mov [ttyfd], eax

	;get current terminal setting
	mov rax, 0x1a
	mov rdi, [ttyfd]
	mov rsi, old_termios
	syscall

	;copy old_termios to raw_termios
	mov rcx, 60
	mov rsi, old_termios
	mov rdi, raw_termios
	rep movsb

	;set raw mode (clean ICANON, ECHO, set VMIN/VTIME)
	mov rbx, raw_termios
	add rbx, 12		; c_lflag offset
	mov eax, [rbx]
	and eax, ~(1<<3)	; ~ICANON
	and eax, ~(1<<1)	; ~ECHO
	mov [rbx], eax

	sub rbx, 12
	mov byte [rbx+17], 1	; VMIN = 1
	mov byte [rbx+16], 0	; VTIME = 0

	; use raw mode
	mov rax, 0x1b
	mov rdi, [ttyfd]
	mov rsi, 0
	mov rdx, raw_termios
	syscall

	; print hint
	mov rax, 1
	mov rdi, 1
	mov rsi, msg
	mov rdx, msglen
	syscall

.loop:
	mov rax, 0
	mov rdi, [ttyfd]
	mov rsi, buf
	mov rdx, 1
	syscall
	
	cmp rax, 1
	jne .loop

	mov al, [buf]
	cmp al, 'q'
	je .restore

	mov rax, 1
	mov rdi, 1
	mov rsi, buf
	mov rdx, 1
	syscall
	jmp .loop

.restore:
	; restore terminal setting
	mov rax, 0x1b
	mov rdi, [ttyfd]
	mov rsi, 0
	mov rdx, old_termios
	syscall

	; print end msg
	mov rax, 1
	mov rdi, 1
	mov rsi, msgbye
	mov rdx, msgbyelen
	syscall

	; close /dev/tty fd
	mov rax, 3
	mov rdi, [ttyfd]
	syscall

	; leave
	mov rax, 60
	xor rdi, rdi
	syscall

