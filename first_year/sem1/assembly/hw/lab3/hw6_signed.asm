bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db -1
    b db -2
    c db 3
    e dd 4
    x dq -5

; our code starts here
segment code use32 class=code
    start:
        ;(a+a+b*c*100+x)/(a+10)+e*a = (-2 - 600 - 5) / 9 - 4 = -67 - 4 = -71 = B9
        
        mov eax, 0
        mov edx, 0
        
        mov al, [b]
        cbw
        mov bl, [c]
        imul bl ;dx:ax = ax * bx = b * c
        mov bx, 100
        imul bx ;dx:ax = ax * bx = b * c * 100
        
        add al, [a]
        add al, [a]
        ;dx:ax = a + a + b * c * 100
        
        add eax, [x]
        cdq
        adc edx, [x + 4]
        ;edx:eax = a + a + b * c * 100 + x
        
        mov ebx, 0
        mov bl, [a]
        add bl, 10
        adc bh, 0 ;ebx = (a + 10)
        
        idiv ebx ; eax = edx:eax / ebx = (a + a + b * c * 100 + x) / (a + 10) = 37h, edx = (a + a + b * c * 100 + x) % (a + 10) = 2
        
        mov ebx, eax
        mov eax, [e]
        mov ecx, 0
        mov cl, [a]
        imul ecx; edx:eax = eax * ecx = e * a = 4
        
        add eax, ebx
        adc edx, 0
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
