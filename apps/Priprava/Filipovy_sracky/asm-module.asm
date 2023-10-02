    bits 64

    section .data

    extern g_long_array
    extern g_sum
    extern g_num_of_bits

    extern g_char_array
    extern g_to_replace
    extern g_new
    extern g_char_count

    extern g_mac_address
    extern g_vendor_oui
    extern g_vendor_name
    extern g_vendor

    section .text

;; 01
    global count_long_array
count_long_array:
    enter 0, 0

    ; for ( int rdx = 0; rdx < 5; rdx++)
    xor edx, edx ; counter
    xor rax, rax ; vysledek

    .back:
        cmp edx, 5
        jnl .endFor

        ; loop body
        add rax, [ g_long_array + edx * 8 ]
        ;cmp ecx, 0
        ;jz .isEven

        inc edx
        jmp .back

    ;.isEven:
    ;    inc eax
    ;    inc edx ;; !!!!!!!!!!!!!!
    ;    jmp .back

    ;; count 1s
    .isDivisible:
        xor edx, edx
        xor ecx, ecx
        .back3:
            cmp edx, 64
            jnl .endEnd

            shr rax, 1
            adc ecx, 0

            inc edx
            jmp .back3

    .endFor:
        mov qword [ g_sum ], rax

        xor rdx, rdx
        ;; check if divisible by 3
        mov rbp, 3
        idiv rbp ; rax / rbp
        cmp rdx, 0
        je .isDivisible
        ;; is not divisible => count zeroes
        xor edx, edx
        xor ecx, ecx
        .backNdiv: ;; loop non divisible
            cmp edx, 64
            jnl .endEnd

            shr rax, 1
            adc ecx, 0

            inc edx
            jmp .backNdiv

    .endEnd:
        mov dword [ g_num_of_bits ], ecx

    leave
    ret

;;  02
    global char_replace
char_replace:
    enter 0,0

    ;; for
    xor edx, edx ;; counter
    xor edi, edi ;; num of replaced chars

    .back:
        cmp edx, 99
        jnl .end

        ;; loop body
        xor al, al
        mov al, [ g_char_array + edx ]
        cmp al, [ g_to_replace ]
        je .replace

        inc edx
        jmp .back

    .replace:
        xor al, al
        ;; take char with which to replace
        mov al, [ g_new ]
        mov [ g_char_array + edx ], al
        inc edi

        inc edx
        jmp .back

    .end:
        mov [ g_char_count ], edi

    leave
    ret

;;  03
    global do_mac
do_mac:
    enter 0,0

    xor edx, edx ;; counter
    ;;xor eax, eax ;; mac addr

    .back:
        cmp edx, 5
        je .end

        ;; loop body
        mov rbx, [ g_mac_address ]
        shr rbx, 24
        cmp rbx, [ g_vendor_oui + edx * 4 ]
        je .match

        inc edx
        jmp .back

    .match:
        shl rbx, 24
        mov dx, word [ g_vendor_name +1 ]
        mov word [ g_vendor ], dx
        jmp .end

    .end:
        mov qword [ g_mac_address ], rbx

    leave
    ret