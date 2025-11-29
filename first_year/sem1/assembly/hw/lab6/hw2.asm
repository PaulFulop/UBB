bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s1 db 1, 2, 3, 1, 2, 3, 1, 2, 3
    lens1 equ $ - s1
    s2 db 1, 2, 3
    lens2 equ $ - s2
    d times lens1 db 0

; our code starts here
segment code use32 class=code
    start:
        ;Being given two strings of bytes, compute all positions where the second string appears as a substring in the first string.
        ;s1 = 1, 2, 3, 1, 2, 3, 1, 2, 3
        ;s2 = 1, 2, 3
        ;d = 0, 3, 6
        
        cld
        mov ecx, lens1
        jecxz End 
        xor ebx, ebx
        xor eax, eax 
        
        find_substr:
            mov ecx, lens2
            mov edi, s2 ;reset to the beginning of s2
            mov esi, s1 ;reset to s1
            add esi, ebx ;move by 1 to verify the next substring 
            
            sub edi, esi
            cmp edi, lens2
            jl End ;if we dont have enough remaining elements in s1 to compare s2 with
            
            mov edi, s2
            
            xor edx, edx 
            verify_substr:
                inc edx
                cmpsb  
                jnz not_substring 
            loop verify_substr
            
            mov [d + eax], ebx 
            inc eax 
             
            inc ebx
            mov ecx, lens1
            sub ecx, ebx 
        loop find_substr
        jmp End
        
        not_substring:
            inc ebx 
            mov ecx, lens1
            sub ecx, ebx
            loop find_substr 
            
        End:
        
        ;mov al, [d]
        ;mov bl, [d + 1]
        ;mov cl, [d + 2]
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
