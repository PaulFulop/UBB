bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    A dw 0110101010111001b
    B dd 0

; our code starts here
segment code use32 class=code
    start:
        ;the bits 28-31 of B have the value 1
        mov eax, [B]
        or eax, 0xF0000000
        mov [B], eax
        
        ;the bits 24- 25 and 26-27 of B are the same as the bits 8-9 of A
        mov eax, [B]
        and eax, 0xF0FFFFFF ;clear the bits 24-27
        mov [B], eax
        
        mov ax, [A]
        and ax, 0000_0011_0000_0000 
        mov cl, 8
        shr ax, cl 
        
        xor ebx, ebx 
        mov bl, al 
        mov eax, [B]
        mov cl, 18h ;  00011000 = 24
        shl ebx, cl 
        or eax, ebx 
        
        mov cl, 2
        shl ebx, cl 
        or eax, ebx 
        mov [B], eax
        
        ;the bits 20-23 of B are the invert of the bits 0-3 of A 
        mov eax, [B]
        and eax, 0xFF0FFFFF ;clear the bits 20-23
        xor ebx, ebx 
        mov bx, [A]
        not bx
        and bx, 0x000F 
        mov cl, 14h
        shl ebx, cl 
        or eax, ebx
        mov [B], eax
        
        ;the bits 16-19 of B have the value 0
        mov eax, [B]
        and eax, 0xFFF0FFFF ;clear the bits 16-19
        mov [B], eax
        
        ;the bits 0-15 of B are the same as the bits 16-31 of B.
        mov eax, [B]
        and eax, 0xFFFF0000
        mov cl, 10h
        shr eax, cl
        
        xor ebx, ebx 
        mov bx, ax 
        mov eax, [B]
        xor ax, ax
        or eax, ebx
        mov [B], eax 
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
