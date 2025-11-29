bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    A db 01011101b
    B db 0
    C dd 0
    n db 0

; our code starts here
segment code use32 class=code
    start:
       ;obtain the integer number n represented on the bits 2-4 of A
       mov al, [A]
       and al, 00011100
       shr al, 2
       mov [n], al 
       
       ;obtain the byte B by rotating A n positions to the right
       mov al, [A]
       mov cl, [n]
       ror al, cl 
       mov [B], al
       
       ;mov dl, [A]
       ;mov dh, [B]
       
       ;the bits 8-15 of C have the value 0
       mov eax, [C]
       and eax, 0xFFFF00FF ;clear the bits 8-15
       mov [C], eax 
       
       ;the bits 16-23 of C are the same as the bits of B
       mov ebx, [C]
       xor eax, eax
       mov al, [B]
       mov cl, 10h ;16
       shl eax, cl 
       and ebx, 0xFF00FFFF ;clear the bits 16-23
       or ebx, eax
       mov [C], ebx 
       
       ;the bits 24-31 of C are the same as the bits of A
       mov ebx, [C]
       xor eax, eax
       mov al, [A]
       mov cl, 18h
       shl eax, cl 
       and ebx, 0x00FFFFFF ;clear the bits 24-31
       or ebx, eax
       mov [C], ebx 
       
       ;the bits 0-7 of C have the value 1
       mov eax, [C]
       or eax, 0x000000FF
       mov [C], eax
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
