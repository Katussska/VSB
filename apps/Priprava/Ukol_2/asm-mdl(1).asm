;***************************************************************************
;
; Program for education in subject "Assembly Languages" and "APPS"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; Empty project
;
;***************************************************************************

    bits 64

    section .data
	extern pole
	extern pole_int,g_N
	extern g_str, g_xor

    ;global g_some_asm_var
    ;extern g_some_c_var

;g_some_asm_var dd ?

;***************************************************************************

    section .text

;functions
	global zmen_znamenko
zmen_znamenko:
	enter 0,0
	mov rdx, 0 ;counter
.back:
	cmp rdx, 10
	je .end
	test [pole + rdx * 8], byte 0b1
	jz .sude
	inc rdx
	jmp .back
.sude:
	neg qword [pole + rdx * 8]
	inc rdx
	jmp .back
.end:
	leave
	ret

	global vydel
vydel:
	enter 0,0
	mov rdx, 0
	mov rax, 0
	mov cl, byte [g_N]
.back:
	cmp rdx, 10
	je .end
	sar dword [pole_int + rdx * 4], cl
	inc rdx
	jmp .back
.end:
	leave
	ret

	global xor_it
xor_it:
	enter 0,0
	mov rdx, 0
	mov rdi, 0
	mov dil, byte [g_xor]
.back:
	cmp [g_str + rdx], byte 0
	je .end
	xor [g_str + rdx], dil
	inc rdx
	jmp .back
.end:
	leave
	ret








