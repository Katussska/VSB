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

    extern data, count
    extern result_num, iterations, result
    extern text, from, replace_to

;***************************************************************************

    section .text


    global count_ones
count_ones:
    enter 0,0

    mov ecx, 0
    mov edx, 0b1        ; mask
    mov eax, 0

.back:
    cmp ecx, 32
    je .end

    test [ data ], edx  ; pokud obsahuje 1, pripocitej ji
    jnz .count
.continue:
    inc ecx
    shl edx, 1          ; bitove posun mask
    jmp .back

.count:
    inc eax
    mov [ count ], eax
    jmp .continue
.end:
    leave
    ret






    global fibb
fibb:
    enter 0,0

    mov edx, [ iterations ]     ; i
    mov ecx, 0                  ; prev
    mov ebx, 1                  ; next

.back:
    dec edx                     ; i--

    mov eax, ecx                ; rax = prev
    add eax, ebx                ; prev + next
    
    mov ecx, ebx                ; prev = next
    mov ebx, eax                ; next = new
    
    ; do-while je cyklus s podminkou na konci
    cmp edx, 0
    je .end

    jg .back

.end:
    mov [ result ], ebx
    leave
    ret

; C-code

;int i = iterations;
;int prev = 0;
;int next = 1;
;do
;{
;    i--;
;    int new = prev + next;
;    prev = next;
;    next = new;
;}
;while (i);
;result = next;








    global replace_char
replace_char:
	enter 0,0
	mov edx, 0
    mov bl, [ from ]           ; X
    mov cl, [ replace_to ]     ; e

.back:
    cmp [text + edx], byte 0b0
	je .end

	cmp [text + edx], bl
	je .replace
.continue:
	inc edx
	jmp .back

.replace:
	mov [text + edx], cl
	jmp .continue
.end:
	leave
	ret
