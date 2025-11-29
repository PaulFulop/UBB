bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 3
    b db 2
    c db 1; 03 02 01

; our code starts here
segment code use32 class=code
    start:
        ;(a-c)*3+b*b = 2 * 3 + 4 = 10 = 000A
        
        mov AL, [a]
        sub AL, [c]
        mov BL, 3
        mul BL ;AX = (a-c) * 3
        
        mov CX, AX ;CX = (a - c) * 3
        mov AL, [b]
        mov BL, [b]
        mul BL ;AX = AL * b
        add CX, AX ;CX = (a - c) * 3 + b * b
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
