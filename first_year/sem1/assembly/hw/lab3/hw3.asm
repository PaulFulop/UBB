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
    b dw 5
    c dd 8
    d dq 0Ah
    ;01 0001 00000003 0000000000000006
; our code starts here
segment code use32 class=code
    start:
        ; (b+b)-c-(a+d) = 10 - 8 - 13 = -11
        
        mov ecx, [c] 
        neg ecx ;-c
        
        mov ebx, 0
        mov bx, [b] 
        
        add ecx, ebx 
        add ecx, ebx ;ecx = b + b - c 
        
        mov eax, [d]
        mov edx, [d + 4]; edx:eax = d 
        add al, [a]
        adc ah, 0
        ;edx:eax = d + a
        
        mov ebx, 0 ;ebx:ecx = quadoword
        sub ecx, eax
        sbb ebx, 0
        sub ebx, edx ; ecx = b + b - c - (a + d)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
