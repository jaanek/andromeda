;
;    Entry point for stage 1.5. This sector will use a dynamic sector loader to load the second stage and the micro kernel.
;    Copyright (C) 2011 Michel Megens
;
;    This program is free software: you can redistribute it and/or modify
;    it under the terms of the GNU General Public License as published by
;    the Free Software Foundation, either version 3 of the License, or
;    (at your option) any later version.
;
;    This program is distributed in the hope that it will be useful,
;    but WITHOUT ANY WARRANTY; without even the implied warranty of
;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;    GNU General Public License for more details.
;
;    You should have received a copy of the GNU General Public License
;    along with this program.  If not, see <http://www.gnu.org/licenses/>.
;

[BITS 16]
[SECTION .stage1]
[EXTERN endptr]
; ; [EXTERN int13_read]

%include "boot/x86/include/masterboot.asmh"

jmp short main
nop

main:
	mov di, 0x7c00
	mov si, OL_BUFOFF+OL_PART_TABLE
	push di
	mov cx, 0x40
	cld
	rep movsw
	push dx

	jmp .loadstage2

.bailout:
	mov si, failed
	call println
	cli
	jmp $

.loadstage2:
	call calcsectors
	mov cx, ax
	mov eax, dword [0x7c00+8]
	add eax, 2	; third sector
	xor ebx, ebx

	mov bx, 0x7e0
	mov es, bx
	mov di, 0x200

	call int13_read
	jc .bailout

; 	call dynamicloader
; 	jc .bailout

	pop dx
	pop si
	jmp 0x7E0:0x200

	jmp .bailout

;
; Dynamic disk reader
;

; %include 'boot/x86/stage1/stage1.5/dynamicloader.asm'

%include 'boot/x86/interface/disk.asm'

;
; Print routine
;

%include 'boot/x86/println.asm'
	
	failed db '0x2', 0x0

times 512 - ($ - $$) db 0
