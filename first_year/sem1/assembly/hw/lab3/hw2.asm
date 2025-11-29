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
    b dw 1
    c dd 3
    d dq 6
    ; 01 0001 00000003 0000000000000006

; our code starts here
segment code use32 class=code
    start:
        ;(d+d)-(a+a)-(b+b)-(c+c) = 12 - 2 - 2 - 6 = 2
        mov eax, [d]
        mov edx, [d + 4] ;edx:eax = d 
        add eax, eax
        adc edx, edx ;edx:eax = d + d 
        
        sub al, [a]
        sbb ah, 0
        sub al, [a]
        sbb ah, 0 ;edx:eax = d + d - (a + a)
        
        mov ebx, 0
        mov ecx, 0
        mov bx, [b]
        add bx, bx
        adc cx, 0 ;CX:BX = b + b
        
        sub eax, ebx
        sbb edx, ecx; edx = d + d - (a + a) - (b + b)
        
        sub eax, [c]
        sbb edx, 0
        sub eax, [c]
        sbb edx, 0 ;edx:eax = d + d - (a + a) - (b + b) - (c + c)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
