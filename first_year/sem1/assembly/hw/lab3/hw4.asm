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

; our code starts here
segment code use32 class=code
    start:
        ; (d+a)-(c-b)-(b-a)+(c+d) = d + a + a + d = d + d + a + a = 20 + 6 = 26
        
        mov eax, [d]
        mov edx, [d + 4] ;edx:eax = d 
        
        add eax, [d]
        adc edx, 0
        add edx, [d + 4]
        
        add al, [a]
        adc ah, 0
        add al, [a]
        adc ah, 0
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
