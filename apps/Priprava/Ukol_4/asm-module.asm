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
    


    ;extern key
    ;extern extended

    ;global g_some_asm_var
    ;extern g_some_c_var

;g_some_asm_var dd ?

;***************************************************************************

    section .text

    ; functions


    ;global extend
    ;global some_asm_function
    ;extern some_c_function

;some_asm_function:
    ;ret

    global triple_nums;
triple_nums:
    enter 0,0;
    mov rax, dword 3;
    xor rbx,rbx;
    
    jmp .loop_ints;
    ret;

.loop_ints:
    cmp rbx, rdx;
    jge .done;

    mov r10, rdx;

    movsx rcx, word[ edi + ebx * 4 ];
    imul rcx;
    mov [rsi + rbx * 8 ], rax;

    mov rax, dword 3;
    mov rdx, r10;
    inc rbx;
    jmp .loop_ints;

.done:
    leave;
    ret;
;----------------------------------------------------

global void_str2int
void_str2int:
	enter 0,0
	mov rax, 0 ; helper
	mov rdx, 0
	mov r9, 0	;helper
	mov r10, 0
	mov [rsi], byte 0
.back:
	cmp [rdi + rdx], byte 0
	je .konec
	cmp rax, 0
	jne .shr
	sub [rdi + rdx], byte '0'
	movsx r10, byte [rdi + rdx]
	add rax, r10
	inc rdx
	jmp .back
.shr:
	mov r10, 0
	mov r9, rax
	shl rax, 3
	shl r9, 1
	add rax, r9
	movsx r10, byte [rdi + rdx]
	sub r10, byte '0'
	add rax, r10
	inc rdx
	jmp .back
.konec:
	mov [rsi], rax
	leave
	ret


global strlen
    strlen:
    enter 0,0
    mov rax, 0
.back:
    cmp byte [ rdi + rax ], 0
    je .done
    inc rax
    jmp .back
.done:
    leave
    ret

    global strmirror
strmirror:
    enter 0,0
    push rdi
    call strlen
    pop rdi
    mov rcx , rdi 
    mov rdx , rcx 
    add rdx , rax 
    dec rdx
.back :
    cmp rcx , rdx
    jae .end
    mov al,[rcx]
    mov ah, [ rdx ] 
    mov [rcx],ah 
    mov [ rdx ], al 
    inc rcx
    dec rdx
    jmp .back
.end :
    mov rax , rdi
    leave
    ret

;----------------------------------------------------

    global int2str
int2str: 
    enter 0,0
    mov rax , rdi
    mov rcx, 10 
    mov rdi , rsi 
    push rsi
    cmp rax, 0
    jg .positive
    jl .negative
    mov [ rsi ], word '0'
    jmp .ret
.negative :
    mov [ rsi ], byte '-'
    inc rdi
    neg rax
.back :
    inc rsi
.positive : test rax , rax
    je .end
    mov rdx, 0
    div rcx
    add dl, '0'
    mov [ rsi ], dl 
    jmp .back
.end :
    mov [ rsi ], byte 0
    call strmirror
.ret :
    pop rax
    leave
    ret

;----------------------------------------------------

global faktorialA
faktorialA:
    enter 16, 0          ; ???

    mov rax, 1
    test rdi, rdi        ; n == 0
    jz .tak_ret_0

    mov [rbp - 8], rdi   ; l_n = n
    dec rdi
    call faktorialA       ; ret faktorial (n - 1);

    imul qword [rbp - 8] ; n * faktorial(n - 1)

.tak_ret_0:
    leave
    ret

;----------------------------------------------------

    global faktorialB
faktorialB:
    
    mov rax, rdi
    mov rsi, 1

.body:
    cmp rsi, rdi
    je .end
    mul rsi
    jo .yes
    inc rsi
    jmp .body
    
.yes:
    mov rax, 0

.end:
    ret

;----------------------------------------------------

    global prvocislo
prvocislo:

.body:

    mov rax, rdi    ; Move the first argument to the rax register
    mov r8, 2       ; Move the value 2 to the r8 register
    cqo             ; Sign-extend rax into rdx:rax
    div r8          ; Divide rax by r8, quotient in rax, remainder in rdx
    cmp rdx, 0      ; Compare the remainder with zero
    je .neni        ; if the remainder is 0 (rax is divisible by 2)

    mov rax, rdi
    mov r8, 3
    cqo
    div r8
    cmp rdx, 0
    je .neni

    mov rax, rdi
    mov r8, 5
    cqo
    div r8
    cmp rdx, 0
    je .neni

    mov rax, rdi
    mov r8, 7
    cqo
    div r8
    cmp rdx, 0
    je .neni

    jmp .end

.neni:
    mov rax, 0
    ret

.end:
    mov rax, 1
    ret

;----------------------------------------------------
;----------------------------------------------------

    global int_str2int ; NEFUNGUJE
int_str2int:
    enter 0,0     ; function prologue: allocate stack space

    xor rax, rax  ; set accumulator to zero
    xor rbx, rbx  ; set negative flag to zero
    mov rdx, 0    ; initialize offset to zero

    cmp byte [rdi], '-'  ; check for negative sign at start of input string
    jne .loop_start      ; if none, jump to loop start

    inc rdi      ; increment pointer to skip over negative sign
    mov rbx, 1  ; set negative flag

.loop_start:
    cmp byte [rdi + rdx], 0 ; check for end of input string
    je .loop_end
    movzx r9, byte [rdi + rdx] ; get next character and convert to numeric value
    sub r9, '0'       ; convert ASCII value to numeric value
    mov r10, rax      ; save accumulator value
    mov rax, 10       ; multiply accumulator by 10
    mul r10
    add rax, r9       ; add digit value to accumulator
    inc rdx           ; increment offset
    jmp .loop_start   ; jump to beginning of loop

.loop_end:
    test rbx, rbx  ; check if negative flag is set
    jz .positive_result
    neg rax        ; if negative, negate result

.positive_result:
    leave        ; function epilogue: deallocate stack space
    ret          ; return accumulator value as function result

;----------------------------------------------------
  