bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 1
    b dw 2
    c dw 3
    d dw 4

; our code starts here
segment code use32 class=code
    start:
    ;b+a-(4-d+2)+c+(a-b) = 3 - 2 + 3 - 1 = 3
        mov AX, [b]
        add AX, [a] ;b + a
        add BX, 6
        sub BX, [d]; 6 - d
        mov CX, [c]
        add CX, [a]
        sub CX, [b] ; c + a - b
        sub AX, BX
        add AX, CX
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
