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
    extern enc_string
    extern slovo
    extern testik
    extern spojene
    extern spojene2
    extern data
    extern result
    extern data2
    extern key
    extern extended
    ;global g_some_asm_var
    ;extern g_some_c_var

;g_some_asm_var dd ?

;***************************************************************************

    section .text

    ; functions
    global decode
decode:
    enter 0,0
    mov AL, byte [enc_string+3]
    mov byte [slovo+1], AL
    mov AL, byte [enc_string+2]
    mov byte [slovo+0], AL
    mov AL, byte [enc_string+1]
    mov byte [slovo+2], AL
    mov AL, byte [enc_string+0]
    mov byte [slovo+3], AL
    leave
    ret
    ;global some_asm_function
    ;extern some_c_function
    global extend_and_merge
extend_and_merge:
    enter 0,0
    movsx EAX, byte [slovo+0]
    movsx EBX, byte [slovo+3]
    mov [spojene], EAX
    mov [spojene+4], EBX
    leave
    ret

    global swap_endiannes
swap_endiannes:
    mov AL, [data+0]
    mov BL, [data+1]
    mov CL, [data+2]
    mov DL, [data+3]
    mov [data+0], DL
    mov [data+1], CL
    mov [data+2], BL
    mov [data+3], AL
    ret
    global compose
compose:
    mov AL, [data+0]
    mov [result+3], AL

    mov AL, [data+1]
    mov [result+2], AL

    mov AL, [data+2]
    mov [result+1], AL

    mov AL, [data+3]
    mov [result+0], AL
    ret

    global replace
replace:
    mov byte [data2+0], 'B'
    mov byte [data2+1], 'A'
    mov byte [data2+2], 'I'
    mov byte [data2+3], '0'
    mov byte [data2+4], '0'
    mov byte [data2+5], '3'
    mov byte [data2+6], '3'
    ret

    global extend
extend:
    movsx RAX, word [key]
    mov [extended], RAX
    ret


