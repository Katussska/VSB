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

    extern g_char_array
    extern g_int_result_num
    extern g_int_iterations
    extern g_int_array
    extern g_int_array_lenght
    extern g_int_lowest

;***************************************************************************

    section .text

    ; functions

    ;global some_asm_function
    ;extern some_c_function

;some_asm_function:
    ;ret

;UKOL_1
    global is_palidrom
is_palidrom:
    enter 0,0

    xor rdx, rdx ;lenght
	xor rax, rax ;right 
	xor rdi, rdi ;left 
	xor rsi, rsi

    .back:
        cmp [g_char_array + rdx],byte  0
        je .lenght_counted
        inc rdx
        jmp .back

    .lenght_counted:
        mov rax, rdx
        sub rax, 1

    .back2:
        cmp rax, rdi
        je .good_end
        mov sil, [g_char_array + rdi]
        cmp [g_char_array + rax], sil
        jne .bad_end
        inc rdi
        dec rax
        jmp .back2

    .bad_end:
        mov rdx ,0

    .back3:
        cmp [g_char_array + rdx], byte 0
        je .good_end
        mov [g_char_array + rdx], byte 'X'
        inc rdx
        jmp .back3

    .good_end:
        leave
        ret

;UKOL_2
 global fibb
fibb:
    enter 0,0

    mov edx, [ g_int_iterations ] ; i
    mov ecx, 0 ; prev
    mov ebx, 1 ; next

.back:
    dec edx  
    mov eax, ecx ;  
    add eax, ebx  
    mov ecx, ebx  
    mov ebx, eax 
    
    cmp edx, 0
    je .end
    jg .back

.end:
    mov [ g_int_result_num ], ebx
    leave
    ret

;UKOL_3
    global the_lowest
the_lowest:
    enter 0,0
    
    xor rdx, rdx ;i++
    xor rdi, rdi ;next
    xor rax, rax ;lowest
    mov eax, dword [g_int_array + rdx * 4] ;first

    .back:
        cmp rdx, [g_int_array_lenght]
        je .null
        movsx rdi, dword [g_int_array + rdx * 4]
        cmp rdi, rax
        jl .new_lowest
        inc rdx
        jmp .back

    .new_lowest:
        mov eax, dword [g_int_array + rdx * 4]
        inc rdx
        mov dword [g_int_lowest], eax
        jmp .back

    .null:
        mov rdx, 0

    .sub:
        mov eax, [g_int_lowest]
        cmp rdx, [g_int_array_lenght]
        jl .end
        sub [g_int_array + rdx * 4] , eax
        inc rdx
        jmp .sub

    .end:
        leave
        ret