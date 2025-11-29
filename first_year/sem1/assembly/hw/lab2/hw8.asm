bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 1
    b db 2
    c db 3
    d dw 4

; our code starts here
segment code use32 class=code
    start:
        ;[(a-b)*3+c*2]-d = -3 + 6 - 4 = -1 = FFFF
        mov AL, [a]
        sub AL, [b]
        mov AH, 0
        mov CL, 3
        imul CL
        mov BL, [c]
        add BL, [c]
        mov BH, 0
        add AX, BX
        sub AX, [d]        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
