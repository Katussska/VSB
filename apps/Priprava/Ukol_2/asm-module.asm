    bits 64

    section .data

    extern g_int_array
    extern g_int_array2
    extern g_int_array_lenght
    extern g_int_output
    extern g_neg_val_array
    extern g_char_array
    extern g_int_data
    extern g_int_count

    section .text

; ukol 01
    global count_even
count_even:
    enter 0, 0

    ; for ( int rdx = 0; rdx < 15; rdx++)
    xor rdx, rdx ; mov rdx, 0 ; sub rdx, rdx
    xor eax, eax ; vysledek

    .back:
        cmp rdx, 15
        jnl .endFor

        ; loop body
        xor ecx, ecx
        mov ecx, [ g_int_array + rdx * 4 ]
        test ecx, 1 ; ecx & 1 == ecx % 2
        ;cmp ecx, 0
        jz .isEven

        inc rdx
        jmp .back

    .isEven:
        inc eax
        inc rdx ;; !!!!!!!!!!!!!!
        jmp .back

    .endFor:
        ; bitove posunuti o 1 doprava je jako delit 2
        ; takze posunuti o 2 je jako delit 4 yay
        shr eax, 2
        not eax
        mov dword[ g_int_output ], eax

    leave
    ret

; ukol 02
    global move_negative
move_negative:
    enter 0,0

    ; for ( int rdx = 0; rdx < 15; rdx++)
    xor rdx, rdx ; mov rdx, 0 ; sub rdx, rdx
    xor eax, eax ; vysledek

    .back:
        cmp rdx, 15
        jnl .endFor

        ; loop body
        xor ecx, ecx
        mov ecx, [ g_int_array + rdx * 4 ]
        cmp ecx, 0 ; ecx & 1 == ecx % 2
        jl .isNegative

        inc rdx
        jmp .back

    .isNegative:
        mov ebx, [ g_int_array + rdx * 4 ]
        mov [ g_neg_val_array + eax * 4 ], ebx
        inc eax
        inc rdx ; !!!!!!!!!!!!!!
        jmp .back

    .endFor:

    leave
    ret

; ukol 03
    global count_vowels
count_vowels:
    enter 0,0

    ; for ( int rdx = 0; rdx < 15; rdx++)
    xor rdx, rdx ; mov rdx, 0 ; sub rdx, rdx
    xor eax, eax ; vysledek

    .back:
        cmp rdx, 32
        jnl .endFor

        ; loop body
        xor cl, cl
        mov cl, [ g_char_array + rdx ]

        cmp cl, 'a'
        jz .isVowel
        cmp cl, 'e'
        jz .isVowel
        cmp cl, 'i'
        jz .isVowel
        cmp cl, 'o'
        jz .isVowel
        cmp cl, 'u'
        jz .isVowel
        cmp cl, 'y'
        jz .isVowel

        inc rdx
        jmp .back

    .isVowel:
        inc eax
        inc rdx ; !!!!!!!!!!!!!!
        jmp .back

    .endFor:
        mov dword[ g_int_output ], eax

    leave
    ret


; ukol 04
    global replace_vowels
replace_vowels:
    enter 0,0

    ; for ( int rdx = 0; rdx < 15; rdx++)
    xor rdx, rdx ; mov rdx, 0 ; sub rdx, rdx
    xor eax, eax ; vysledek

    .back:
        cmp rdx, 32
        jnl .endFor

        ; loop body
        xor cl, cl
        mov cl, [ g_char_array + rdx ]

        cmp cl, 'a'
        jz .isVowel
        cmp cl, 'e'
        jz .isVowel
        cmp cl, 'i'
        jz .isVowel
        cmp cl, 'o'
        jz .isVowel
        cmp cl, 'u'
        jz .isVowel
        cmp cl, 'y'
        jz .isVowel

        inc rdx
        jmp .back

    .isVowel:
        inc eax
        cmp eax, 3
        je .replace
        inc rdx ; !!!!!!!!!!!!!!
        jmp .back

    .replace
        mov byte [ g_char_array + rdx*1 ], '3'
        inc rdx
        xor eax, eax
        jmp .back

    .endFor:
        mov dword[ g_int_output ], eax

    leave
    ret
    
; ukol 05
    global count_ones
count_ones:
    enter 0,0

    mov eax, 0
    mov rdx, 0
    mov rdi, 0
    mov edi, [g_int_data]
        
    .back:
        cmp rdx, 32
        je .endFor
        test edi, 0b1
        jnz .inc_count
        inc rdx
        shr edi, 1
        jmp .back

    .inc_count:
        inc eax
        inc rdx
        shr edi, 1
        jmp .back

    .endFor:
        mov [g_int_count],dword eax
        leave
        ret

; ukol 06
    global the_lowest
the_lowest:
    enter 0,0
    
    xor rdx, rdx ;i++
    xor rdi, rdi ;next
    xor rax, rax ;lowest
    movsx rax, dword [g_int_array2 + rdx * 4] ;first

    .back:
        cmp rdx, [g_int_array_lenght]
        jl .null
        movsx rdi,dword [g_int_array2 + rdx * 4]
        cmp rdi, rax
        jl .new_lowest
        inc rdx
        jmp .back

    .new_lowest:
        mov rax, rdi
        inc rdx
        jmp .back

    .null:
        xor rdx, rdx
        jmp .sub

    .sub:
        cmp rdx, [g_int_array_lenght]
        jl .end
        sub [g_int_array2 + rdx * 4] , rax
        inc rdx
        jmp .sub

    .end:
        leave
        ret
