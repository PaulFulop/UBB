bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    A db 2, 1, 3, -3, -4, 2, -6
    lenA equ $ - A
    B db 4, 5, -5, 7, -6, -2, 1
    lenB equ $ - B
    R times lenA + lenB db 0

; our code starts here
segment code use32 class=code
    start:
        ;Two byte strings A and B are given. Obtain the string R that contains only the even negative elements of the two strings.
        ;A: 2, 1, 3, -3, -4, 2, -6
        ;B: 4, 5, -5, 7, -6, -2, 1
        ;R: -4, -6, -6, -2
        
        mov ecx, lenA
        xor esi, esi 
        xor ebx, ebx 
        jecxz End1
        RepeatA:
            mov al, [A + esi]
            cmp al, 0
            jl is_negativeA
            inc esi
        loop RepeatA
        jmp End1 
                
        is_negativeA:
           test al, 1
           jz is_evenA
           inc esi 
           loop RepeatA
        
        is_evenA:
            mov [R + ebx], al
            inc ebx 
            inc esi
            loop RepeatA
            
        End1:
        
        mov ecx, lenB        
        xor esi, esi
        jecxz End2
        RepeatB:
            mov al, [B + esi]
            cmp al, 0
            jl is_negativeB
            inc esi 
        loop RepeatB
        jmp End2
        
        is_negativeB:
           test al, 1
           jz is_evenB
           inc esi 
           loop RepeatB
           
        is_evenB:
            mov [R + ebx], al
            inc ebx
            inc esi
            loop RepeatB
                
        End2:
        ;mov al, [R]
        ;mov bl, [R + 1]
        ;mov cl, [R + 2]
        ;mov dl, [R + 3]
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
