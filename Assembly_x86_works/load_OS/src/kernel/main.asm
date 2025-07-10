ORG 0x0
BITS 16
	
;main:
	;mov ax, 0
	;mov ax, 0x2000
	;mov ds, ax
	;mov es, ax
	;mov ss, ax

	;mov sp, 0X7C00
start:
	;mov ax, 0x2000
	mov si, os_boot_msg
	call print
	HLT

halt:
	JMP halt

print:
	push si
	push ax
	push bx

print_loop:
	LODSB
	OR al, al
	JZ done_print

	mov ah, 0x0e
	mov bh, 0
	int 0x10

	JMP print_loop

done_print:
	pop bx
	pop ax
	pop si
	ret
	
os_boot_msg: db 'first OS has booted!', 13, 10, 0

;TIMES 510-($-$$) DB 0
;DW 0AA55h
