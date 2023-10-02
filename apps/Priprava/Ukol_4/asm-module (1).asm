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

    ;global g_some_asm_var
    ;extern g_some_c_var
   

;g_some_asm_var dd ?

;***************************************************************************

    section .text

    ; functions

    ;global some_asm_function
    ;extern some_c_function

;some_asm_function:
    ;ret

    global faktorial
faktorial:
    
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


    global nulovani_cisel
nulovani_cisel:

    mov r8d, edx
    mov ecx, 0

.body:
    cmp ecx, esi
    je .end
    mov eax, [rdi + rcx * 4]
    cdq 
    div r8d
    cmp edx, 0
    jne .nenula
    mov [rdi + rcx * 4], dword 0
    mov edx, 0

.nenula:
    inc ecx
    jmp .body

.end:
    ret


    global prvocislo
prvocislo:

.body:

    mov rax, rdi
    mov r8, 2
    cqo
    div r8
    cmp rdx, 0
    je .neni

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



    