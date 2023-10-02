    bits 64

    ;variables
    section .data
    cislo dq 0
    section .text

    global strcat2:
strcat2:
    enter 0, 0
    mov r10, 0
    mov r11, 0 ;count
    mov r9, 0 ;bylnaleznutprvni
    mov r8b, sil
    sub r8b, 32 ;odečtu 32, protože v ascii je velké o 32 dřív

    .mainloop:
        cmp byte[rdi+r10*1], 0 ;kontrola konce stringu
        je .end

        cmp byte[rdi+r10*1], sil ;cmp s 'e'
        je .increase

        cmp byte[rdi+r10*1], r8b ;cmp s 'E'
        je .increase

        inc r10
        jmp .mainloop
        
    .increase:
        inc r11
        cmp r9, 0 ;pokud jestě nebyl zapisprvni, tak ho volam
        je .zapisprvni
        inc r10
        jmp .mainloop

    .zapisprvni:
        mov rax, r10; ;rax je výstup
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
    mov r10, 0 ;delkastringu
    mov r11, 0
    mov rax, 0
    .getlength: ;získám délku pole, zapíšu do r10
        cmp byte[rdi+r10*1], 0 ;kontrola konce stringu
        je .prepare
        inc r10 
        jmp .getlength

    .prepare: ;nachystám si číslo pro násobení desítkou
        dec r10
        cmp r10, 0 ;pokud bych násobil deset na 0
        je .end
        xor r9, r9 ;vynuluju r9
        mov r9b, byte[rdi+r11*1] ;zapíšu tam ascii hodnotu čísla
        sub r9b, 48 ;odečtu 48 -> '5' = 5
        jmp .multiplyloop ;jdu násobit

    .multiplyloop:
        cmp rax, r10 ;rax je counter kolikrát už jsem násobil 10
        je .addtonumber
        mov r8, r9
        shl r9, 3 ;násobení 8
        shl r8, 1 ;násobení 2
        add r9, r8 ;sečtu
        inc rax
        jmp .multiplyloop

    .addtonumber: ;přičtení k celkovému číslu
        mov rax, 0
        add [cislo], r9
        inc r11 ;posunu index v stringu
        jmp .prepare

    .end:
        xor r9, r9
        mov r9b, byte[rdi+r11*1] ;naposled přičtu hodnotu, co by měla 10^0
        sub r9b, 48 ;opět odečtu 48
        add [cislo], r9 ;přičtu
        mov rax, [cislo] 
        mov [rsi], rax ;zapíšu do num
        leave
        ret

    global my_strcpy
my_strcpy:
    enter 0, 0
    mov r9, 0
    ;v rdx uz je end
.mainloop:
    cmp r9, rdx
    jnl .end
    mov r8b, [rsi+r9*1]
    mov [rdi+r9*1], r8b
    inc r9
    jmp .mainloop
.end:
    leave
    ret