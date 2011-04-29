;
;    Calculate how many sectors the second stage is, and load enough sectors. Algorith used:
;	sectors to read = (endptr - (stage15Offset + stage15Size)) / sectorSize
;
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

dynamicloader:
	mov cx, 5

.checkextensions:
	mov ah, 0x41	; check ext
	mov dl, 0x80	; HDD0
	mov bx, 0x55AA
	int 0x13
	jc .checkextensions

.calcsectors:
	xor dx, dx
	lea ax, [endptr]
	sub ax, 0x8200 ; stage 1.5 offset + its file size
	mov bx, 0x200 ; sector size
	idiv bx ; divide size by sector size
	or dx, dx
	jz .extread
	
	inc ax

.extread:
	mov [lbar+2], ax
	mov ah,0x42
	mov dl,0x80
	lea si,[lbar]        
	int 0x13
	jnc .return

	loop .extread

; .oldreset:
; 	xor ah, ah ; function 0 = reset
; 	mov dl, 0x80
; 	int 0x13
; 	jc .oldreset

; .oldload:
; 	call .calcsectors
; 
; 	mov  bx, 0x7E0
; 	mov es, bx
; 	mov bx, 0x400
; 
; 	mov ah, 0x02 ; func 2
; 	; mov al, sectorcount -> done by calcsectors
; 	xor ch, ch ; track
; 	mov cl, 0x4 ; sector to start
; 	xor dh, dh ; head
; 	mov dl, 0x80 ; drive
; 	int 0x13

.return:
	ret

lbar:
	db 0x10
	db 0x0
	dw 0x01   ; ptr to amount of sectors to read
	dw 0x400	; offset
	dw 0x7E0	; segment
	dq 0x3