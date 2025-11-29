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
    c db 2
    e dw 3
    f dw 4
    g dw 5
    h dw 6

; our code starts here
segment code use32 class=code
    start:
        ; (e + g) * 2 / (a * c) + (h – f) + b * 3 = 8 + 2 + 6 = 16 = 10h
        mov EAX, 0
        mov AX, [e]
        add AX, [g]
        mov BL, 2
        imul BL
        mov ECX, EAX
        ;(e + g) * 2
        
        mov AL, [a]
        mov BL, [c]
        imul BL
        mov BX, AX
        mov EAX, ECX
        cwd
        idiv BX
        
        add AX, [h]
        sub AX, [f]
        mov ECX, EAX
        
        mov AL, [b]
        mov AH, 0
        mov BL, 3
        imul BL
        add CX, AX
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
