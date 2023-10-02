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
    extern data
    extern data2
    extern result
    extern data3
    extern key
    extern extended

;g_some_asm_var dd ?

;***************************************************************************

    section .text

    ; functions

    ;global some_asm_function
    ;extern some_c_function
    
    global swap_endiannes
;some_asm_function:
swap_endiannes:
    mov AL, [data+0]
    mov BL, [data+1]
    mov CL, [data+2]
    mov DL, [data+3]
    mov [data+0], DL
    mov [data+1], CL
    mov [data+2], BL
    mov [data+3], AL
    ;ret
    ret

    global compose
compose:
    mov AL, [data2+0]
    mov [result+0], AL

    mov AL, [data2+1]
    mov [result+1], AL

    mov AL, [data2+2]
    mov [result+2], AL

    mov AL, [data2+3]
    mov [result+3], AL
    ret

    global replace
replace: 
    mov byte [data3 + 0], 'B'
    mov byte [data3 + 1], 'A'
    mov byte [data3 + 2], 'I'
    mov byte [data3 + 3], '0'
    mov byte [data3 + 4], '0'
    mov byte [data3 + 5], '3'
    mov byte [data3 + 6], '3'
    ret

    global extend
extend:
    movsx RAX, word [key]
    mov [extended], RAX
    ret