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

;UKOL_1
    global fill_pyramid_numbers
fill_pyramid_numbers:
    enter 0,0
    xor rcx, rcx
    
    push rbx
    movsx rsi, esi

    .back:
        cmp rcx, rsi
        jge .finish
        xor r8, r8
        xor rbx, rbx
        mov r10, rcx
        inc r10

        .back2:
            cmp rbx, r10
            jge .end
            inc rbx
            mov rax, rbx
            mul rbx
            add r8, rax
            jmp .back2

        .end:
            mov [rdi + rcx * 8], r8
            inc rcx
            jmp .back
        
    .finish:
        pop rbx
        leave
        ret

;UKOL_2
    global  multiples
multiples:
    enter 0,0  
    xor rax, rax
    xor rcx, rcx
    xor r8, r8
    movsx rsi, esi 
    movsx r9, edx 
    
    .back:
        cmp rcx, rsi
        jge .end
        mov rax, [rdi + rcx * 8]
        xor rdx, rdx
        cdq
        idiv r9
        cmp rdx, 0
        je .multiple
        jne .not_multiple

    .multiple:
        inc r8
        inc rcx
        jmp .back

    .not_multiple:
        add [rdi + rcx * 8], byte 1
        jmp .back

    .end:
    mov rax, r8
    leave
    ret

;UKOL_4
   global change_array_by_avg
change_array_by_avg:
    enter 0,0
    xor rcx, rcx
    xor rax, rax
    movsx rsi, esi 

    .back:
        cmp rcx, rsi
        jge .end
        add rax, [rdi + rcx * 8]
        inc rcx
        jmp .back

        .end:
            cdq
            idiv rsi
            xor rcx, rcx
    
    .back2:
        cmp rcx, rsi
        jge .finish
        mov r8, [rdi + rcx * 8]
        cmp r8, rax
        mov r9, -1
        mov r10, 0
        mov r11, 1
        cmovl r8, r9
        cmove r8, r10
        cmovg r8, r11
        mov [rdi + rcx * 8], r8
        inc rcx
        jmp .back2
    
    .finish:
        leave
        ret