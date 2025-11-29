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
    b dw 2
    c dd 5
    d dq 2
    ; 03 0002 00000005 0000000000000002

; our code starts here
segment code use32 class=code
    start:
        ;(a-b)+(c-b-d)+d = a - b + c - b = 1 + 3 = 4
        mov EAX, 0
        mov AL, [a]
        mov AH, 0
        mov BX, [b]
        sub AX, BX ;AX = a - b = EAX
        
        mov EBX, [c]
        mov ECX, 0
        mov CX, [b]
        sub EBX, ECX ;ECX = c - b
        add EBX, EAX ;EBX = a - b + c - b
        
        mov EAX, [d + 4]
        mov EDX, [d]
        sub EBX, EDX
        sbb EAX, 0 ; EAX:EDX = a - b + c - b - d
        
        add EDX, [d]
        adc EAX, [d + 4]; EAX:EDX = a - b + c - b - d + d = 0000000000000004h
            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
