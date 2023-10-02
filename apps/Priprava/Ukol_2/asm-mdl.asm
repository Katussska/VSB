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

    ; variables
    extern data, count
    extern pole, velikost
    extern string
    ;global g_some_asm_var
    ;extern g_some_c_var


;g_some_asm_var dd ?

;***************************************************************************

    section .text
    global count_ones
count_ones:
	enter 0,0
	mov rax, 0
	mov rdx, 0
	mov rdi, 0
	mov edi, [data]
.back:
	cmp rdx, 32
	je .konec
	test edi, 0b1
	jnz .inc_count
	inc rdx
	shr edi, 1
	jmp .back
.inc_count:
	inc rax
	inc rdx
	shr edi, 1
	jmp .back
.konec:
	mov [count],dword eax
	leave
	ret

	global arr_min
arr_min:
	enter 0,0
	mov rdx, 0
	mov rdi, 0
	mov rax, 0
	movsx rax, dword [pole + 4 * rdx] ;minimum
.back:
	cmp rdx, [velikost]
	je .end
	movsx rdi,dword [pole + 4 * rdx]
	cmp rdi, rax
	jl .new_lowest
	inc rdx
	jmp .back
.new_lowest:
	mov rax, rdi
	inc rdx
	jmp .back
.end:
	mov rdx, 0
.end2:
	cmp rdx, [velikost]
	je .end_fr
	sub [pole + 4  * rdx] , eax
	inc rdx
	jmp .end2
.end_fr:
	leave
	ret

	global is_palidrom
is_palidrom:
	enter 0,0
	mov rdx, 0 ;counter
	mov rax, 0 ;right counter
	mov rdi, 0 ;left counter
	mov rsi, 0
.back:
	cmp [string + rdx],byte  0
	je .we_have_str_len
	inc rdx
	jmp .back
.we_have_str_len:
	mov rax, rdx
	sub rax, 1
.back2:
	cmp rax, rdi
	je .end_is_palidrom
	mov sil, [string + rdi]
	cmp [string + rax], sil
	jne .end_is_not_palidrom
	inc rdi
	dec rax
	jmp .back2
.end_is_not_palidrom:
	mov rdx ,0
.back3:
	cmp [string + rdx], byte 0
	je .end_is_palidrom
	mov [string + rdx], byte 'X'
	inc rdx
	jmp .back3
.end_is_palidrom:
	leave
	ret

    ;global some_asm_function
    ;extern some_c_function

;some_asm_function:
    ;ret


