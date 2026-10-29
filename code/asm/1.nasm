          global    _start

          section   .text
_start:
        mov rsi, "abc"
        mov rax, 1
        mov rdi, 1 ; STDOUT is 1
        mov rdx, 8
        syscall

        mov rax, 60
        xor rdi, rdi
        syscall
