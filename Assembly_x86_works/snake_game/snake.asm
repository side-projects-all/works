section .data
	x	  db 5
	y	  db 5
	dx1   db 1
	dy1	  db 0
	clear db 27, '[2J'

section .bss
	old_termios resb 60		;keep original terminal mode
	raw_termios resb 60		;
	escstr resb 16
	buf resb 1		; buffer for keyboard input

section .text
	global _start

_start:

.change_termios:
	mov rax, 0x1a
	mov rdi, 0
	mov rsi, old_termios
	syscall

	;copy old mode
	mov rcx, 60
	mov rsi, old_termios
	mov rdi, raw_termios
	rep movsb
	
	mov rbx, raw_termios
	; set raw mode, clear ECHO, ICANON flag
	add rbx, 12
	mov eax, [rbx]
	and eax, ~(1<<3)
	and eax, ~(1<<1)
	mov [rbx], eax
	
	; set VMIN/VTIME	(to non-blocking)
	sub rbx, 12
	mov byte [rbx+17], 0
	mov byte [rbx+16], 0

	; start raw mode
	mov rax, 0x1b
	mov rdi, 0
	mov rsi, 0
	mov rdx, raw_termios
	syscall

.loop:

	mov rax, 1
	mov rdi, 1
	mov rsi, clear
	mov rdx, 4
	syscall

	mov rsi, escstr
	mov byte [rsi], 27
	mov byte [rsi+1], '['
	mov al, [y]
	add al, '0'
	mov byte [rsi+2], al
	mov byte [rsi+3], ';'
	mov al, [x]
	add al, '0'
	mov byte [rsi+4], al
	mov byte [rsi+5], 'H'
	mov byte [rsi+6], '@'
	mov byte [rsi+7], 0

	mov rax, 1
	mov rdi, 1
	mov rsi, escstr
	mov rdx, 7
	syscall

	;read keyboard, wasd
.read_keyboard:
	mov rax, 0	; read
	mov rdi, 0	; stdin
	mov rsi, buf
	mov rdx, 1
	syscall

	;jump to move if not the same
	cmp rax, 1
	jne .move

	mov al, [buf]

;check if q, then quit game
.chk_q:
	cmp al, 'q'
	jne .chk_w

.restore_mode:
	;restore mode
	mov rax, 0x1b
	mov rdi, 0
	mov rsi, 0
	mov rdx, old_termios
	syscall

	;continue to end game
	mov rax, 60
	xor rdi, rdi
	syscall

.chk_w:
	cmp al, 'w'
	jne .chk_s
	mov byte [dx1], 0
	mov byte [dy1], -1
	jmp .move

.chk_s:
	cmp al, 's'
	jne .chk_a
	mov byte [dx1], 0
	mov byte [dy1], 1
	jmp .move

.chk_a:
	cmp al, 'a'
	jne .chk_d
	mov byte [dx1], -1
	mov byte [dy1], 0
	jmp .move

.chk_d:
	cmp al, 'd'
	jne .move
	mov byte [dx1], 1
	mov byte [dy1], 0

.move:
	mov al, [x]
	add al, [dx1]
	mov [x], al
	mov al, [y]
	add al, [dy1]
	mov [y], al

;simple boundary check
.xtest:
	cmp byte [x], 1
	jge .xok1
	mov byte [x], 9

.xok1:
	cmp byte [x], 9
	jle .ytest
	mov byte [x], 1

.ytest:
	cmp byte [y], 1
	jge .yok1
	mov byte [y], 9

.yok1:
	cmp byte [y], 9
	jle .delay
	mov byte [y], 1

.delay:
	mov rcx, 50000000

.delayloop:
	loop .delayloop

	jmp .loop
