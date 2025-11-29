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
    S1 db 1, 2, 3, 4
    len equ $ - S1 
    S2 db 5, 6, 7, 8
    D times len db 0

; our code starts here
segment code use32 class=code
    start:
    ;Two byte strings S1 and S2 are given, having the same length.
    ;Obtain the string D in the following way: each element found on the even positions of D is the sum of the corresponding elements from S1 and S2,
    ;and each element found on the odd positions of D is the difference of the corresponding elements from S1 and S2.
    ;S1: 1, 2, 3, 4
    ;S2: 5, 6, 7, 8
    ;D: 6, -4, 10, -4
    
        mov ecx, len
        xor esi, esi 
        jecxz End
        Repeat:
           test esi, 1
           jz is_even
           mov al, [S1 + esi]
           mov bl, [S2 + esi]
           sub al, bl 
           mov [D + esi], al 
           inc esi
        loop Repeat
        jmp End 
        
    is_even:
        mov al, [S1 + esi]
        mov bl, [S2 + esi]
        add al, bl
        mov [D + esi], al
        inc esi 
        loop Repeat
                
        End:
        
        mov al, [D]
        mov bl, [D + 1]
        mov cl, [D + 2]
        mov dl, [D + 3]
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
