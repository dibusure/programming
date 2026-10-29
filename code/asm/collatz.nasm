global solution
section .text
solution:
; n is in rdi
; return is in rax
    mov r9, 0
    cmp rdi, 1 ; check whether n <= 1 
    mov rax, rdi
    jge COLLATZ ; jump if not above
    mov rax, -1 
    ret

COLLATZ:
    ; check if rdi is even or odd

    cmp rax, 1 ; check n <= 1
    jz ANS


    test rax, 1 ; if it is true then the number is odd
    jz COLLATZ_EVEN
    mov r10, 3
    mul r10
    inc rax

    inc r9
    jmp COLLATZ

ANS:
    mov rax, r9
    ret

COLLATZ_EVEN:
    mov r10, 2
    div r10
    inc r9
    jmp COLLATZ
    ret
    
