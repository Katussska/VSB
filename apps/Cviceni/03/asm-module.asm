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

    cislo dq 0

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

;UKOL_1
    global my_strchr:
my_strchr:
    enter 0, 0
    mov r10, 0
    mov r11, 0 ;count
    mov r9, 0 ;first
    mov r8b, sil
    sub r8b, 32 ;ASCII 

    .mainloop:
        cmp byte[rdi+r10*1], 0
        je .end

        cmp byte[rdi+r10*1], sil 
        je .increase

        cmp byte[rdi+r10*1], r8b 
        je .increase

        inc r10
        jmp .mainloop
        
    .increase:
        inc r11
        cmp r9, 0
        je .first
        inc r10
        jmp .mainloop

    .first:
        mov rax, r10 ;rax = first
        inc r10
        inc r9
        jmp .mainloop

    .end:
    mov [rdx], r11
    leave
    ret

    global str2int
str2int:
    enter 0, 0
    mov r10, 0 ;strlen
    mov r11, 0
    mov r12, 0
    mov rax, 0

    .getlength: 
        cmp byte[rdi+r10*1], 0
        je .prepare10
        inc r10 
        mov r12, r10
        jmp .getlength

    .prepare10: 
        dec r10
        cmp r10, 0 ;10^0
        je .end
        xor r9, r9
        mov r9b, byte[rdi+r11*1] ;ASCII number
        sub r9b, 48 ;ASCII 'number'
        jmp .multiplyloop 

    .multiplyloop:
        cmp rax, r10 
        je .addtonumber
        mov r8, r9
        shl r9, 3 
        shl r8, 1 
        add r9, r8 
        inc rax
        jmp .multiplyloop

    .addtonumber: 
        mov rax, 0
        add [cislo], r9
        inc r11 
        jmp .prepare10

    .end:
        xor r9, r9
        mov r9b, byte[rdi+r11*1] 
        sub r9b, 48 
        add [cislo], r9 
        mov rax, [cislo] 
        mov [rsi], rax ;num
        leave
        ret

    global my_strcpy
my_strcpy:
    enter 0, 0
    mov r9, 0
    ;v rdx end

    .mainloop:
        cmp r9, rdx
        je .end
        mov r8b, byte [rsi+r9*1]
        mov byte [rdi+r9*1], r8b
        inc r9
        jmp .mainloop

    .end:
        leave
        ret