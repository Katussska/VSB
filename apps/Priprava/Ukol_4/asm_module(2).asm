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



;***************************************************************************

    section .text

    ; functions

    global fill_pyramid_numbers
fill_pyramid_numbers:
        ;   rdi     rsi     edx     ecx     r8d     r9d
        ;   array   size

        push rbx

        movsx rsi, esi

        mov rcx, 0

    .back:
        cmp rcx, rsi
        jge .end

        mov r8, 0
        mov rbx, 0

        mov r10, rcx
        inc r10

        .inner_back:
            cmp rbx, r10
            jge .inner_end

            inc rbx

            mov rax, rbx
            mul rbx

            add r8, rax

            jmp .inner_back
        .inner_end:

        mov [rdi + rcx * 8], r8

        inc rcx
        jmp .back
    .end:

        pop rbx

        ret



    global multiples
multiples:
        ;   rdi     rsi     edx     ecx     r8d     r9d
        ;   arr[]   size    factor

        mov rax, 0
        mov rcx, 0
        movsx rsi, esi
        movsx r9, edx

        mov r8, 0

    .back:
        cmp rcx, rsi
        jge .end

        mov rax, [rdi + rcx * 8]
        mov rdx, 0

        cdq
        idiv r9
        cmp rdx, 0
        je .multiple
        jne .not_multiple

    .multiple:
        inc r8
        jmp .continue

    .not_multiple:
        mov qword [rdi + rcx * 8], -1
        jmp .continue

    .continue:

        inc rcx
        jmp .back
    .end:

        mov rax, r8

        ret


    global factorial
factorial:
        ;   rdi     rsi     edx     ecx     r8d     r9d
        ;   arr[]   size
        ;push rbx

        mov rcx, 0
        mov rax, 0
        mov r9d, 0

    .back:
        cmp rcx, rsi
        jge .end

        mov r8d, [rdi + rcx * 4]
        mov eax, 1
        mov rdx, 0


        mov r11, 1
        .inner_back:
            cmp r11, r8
            jg .inner_end

            mul r11

            inc r11
            jmp .inner_back
        .inner_end:

        cmp edx, 0
        je .okay

        mov eax, 0
        inc r9d

    .okay:
        mov [rdi + rcx * 4], eax

        inc rcx
        jmp .back
    .end:

        mov eax, r9d
        ;pop rbx

        ret


    global change_array_by_avg
change_array_by_avg:
        ;   rdi     rsi     edx     ecx     r8d     r9d
        ;   *arr    len

        mov rcx, 0
        mov rax, 0
        movsx rsi, esi

        ; 

    .back:
        cmp rcx, rsi
        jge .end

        add rax, [rdi + rcx * 8]

        inc rcx
        jmp .back
    .end:

        cdq
        idiv rsi

        mov rcx, 0

    .back2:
        cmp rcx, rsi
        jge .end2

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
    .end2:


        ret