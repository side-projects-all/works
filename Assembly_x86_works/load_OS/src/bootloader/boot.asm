ORG 0x7C00
BITS 16

JMP SHORT main
NOP

;disk headers for FAT12
bdb_oem:					DB 		'MSWIN4.1'
bdb_bytes_per_sector:		DW		512
bdb_sectors_per_cluster: 	DB		1
bdb_reserved_sectors:		DW		1
bdb_fat_count:				DB		2
bdb_dir_entries_count:		DW		0E0h
bdb_total_sectors:			DW		2880
bdb_media_descriptor_type:	DB		0F0h
bdb_sectors_per_fat:		DW		9
bdb_sectors_per_track:		DW		18
bdb_heads:					DW		2
bdb_hidden_sectors:			DD		0
bdb_large_sector_count:		DD		0

ebr_drive_number:			DB		0
							DB		0
ebr_signature:				DB		29h
ebr_volumn_id:				DB		12h,34h,56h,78h
ebr_volumn_label:			DB		'  STUDYOS  '	;11bytes
ebr_system_id:				DB		'FAT12   '		;8bytes

main:
	mov ax, 0
	mov ds, ax
	mov es, ax
	mov ss, ax

	mov sp, 0X7C00

	;mov [ebr_drive_number], dl	
	;mov ax, 1	;lba index
	;mov cl, 1	;sector number
	;mov bx, 0x7e00	;buffer
	;call disk_read

	mov si, os_boot_msg
	call print

	;4 segments
	;reserved segment: 1 sector
	;FAT: 9 * 2 = 18 sectors
	;Root directory: at 19 sector
	;Data

	mov ax, [bdb_sectors_per_fat]
	mov bl, [bdb_fat_count]
	xor bh, bh
	mul bx
	add ax, [bdb_reserved_sectors]	;LBA of the root directory
	push ax

	mov ax, [bdb_dir_entries_count]
	shl ax, 5
	xor dx, dx
	div word [bdb_bytes_per_sector] ; (32 * num of entries) / bytes per sector

	test dx, dx
	jz root_dir_after
	inc ax

root_dir_after:
	mov cl, al
	pop ax
	mov dl, [ebr_drive_number]
	mov bx, buffer
	call disk_read

	xor bx, bx
	mov di, buffer

search_kernel:
	mov si, file_kernel_bin
	mov cx, 11
	push di
	repe cmpsb
	pop di
	je found_kernel

	add di, 32
	inc bx
	cmp bx, [bdb_dir_entries_count]
	jl search_kernel

	jmp kernel_not_found

kernel_not_found:
	mov si, msg_kernel_not_found
	call print

	hlt
	jmp halt
	
found_kernel:
	mov ax, [di+26]	;to first cluster
	mov [kernel_cluster], ax

	mov ax, [bdb_reserved_sectors]
	mov ax, buffer
	mov cl, [bdb_sectors_per_fat]
	mov dl, [ebr_drive_number]

	call disk_read

	mov bx, kernel_load_segment
	mov es, bx
	mov bx, kernel_load_offset

load_kernel_loop:
	mov ax, [kernel_cluster]
	add ax, 31	;offset
	mov cl, 1
	mov dl, [ebr_drive_number]
	
	call disk_read

	add bx, [bdb_bytes_per_sector]

	mov ax, [kernel_cluster] ;(kernel cluster * 3)/2
	mov cx, 3
	mul cx
	mov cx, 2
	div cx

	mov si, buffer
	add si, ax
	mov ax, [ds:si]

	or dx, dx
	jz even

odd:
	shr ax, 4
	jmp next_cluster_after

even:
	and ax, 0x0fff

next_cluster_after:
	
	cmp ax, 0x0ff8
	jae read_finish

	mov [kernel_cluster], ax
	jmp load_kernel_loop

read_finish:

	mov dl, [ebr_drive_number]
	mov ax, [kernel_load_segment]
	mov ds, ax
	mov es, ax

	jmp kernel_load_segment:kernel_load_offset

	hlt

halt:
	JMP halt

;input: LBA index in ax
;output: cx [bits 0-5]: sector number
;			[bits 6-15]: cylinder
;dh: head
lba_to_chs:
	push ax
	push dx
	
	xor dx, dx
	div word [bdb_sectors_per_track]	; (LBA % sectors per track) + 1 <- sector
	inc dx	;sector  ;remainder in dx register
	mov cx, dx	; tmp store

	xor dx, dx
	div word [bdb_heads]

	mov dh, dl	; head number for run int 13h
	mov ch, al	; track/cylinder number for run int 13h
	shl ah, 6	
	or cl, ah	;cylinder

	; head: (LBA / sectors_per_track) % number_of_heads
	; cylinder: (LBA / sectors_per_track) / number of heads
	pop ax
	mov dl, al
	pop ax

	ret

disk_read:
	push ax
	push bx
	push cx
	push dx
	push di

	call lba_to_chs

	mov ah, 02h
	mov di, 3	; counter

retry:
	stc
	int 13h
	jnc done_read

	call disk_reset

	dec di
	test di, di
	jnz retry

fail_disk_read:
	mov si, read_failure
	call print
	hlt
	jmp halt

disk_reset:
	pusha
	mov ah, 0	;for interrupt, do reset flag
	stc
	int 13h
	jc fail_disk_read
	popa
	ret

done_read:
	pop di
	pop dx
	pop cx
	pop bx
	pop ax

	ret

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
	
os_boot_msg: db 'Loading...!', 0x0d, 0x0a, 0
read_failure: db 'Failed to read disk!', 0x0d, 0x0a, 0
file_kernel_bin DB 'KERNEL  BIN'
msg_kernel_not_found DB 'KERNEL.BIN not found!'
kernel_cluster DW 0

kernel_load_segment EQU 0x2000
kernel_load_offset EQU 0

TIMES 510-($-$$) DB 0
DW 0AA55h

buffer: 
