bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db 5, 25, 55, 127
    lens equ $ - s 
    d times lens db 0

; our code starts here
segment code use32 class=code
    start:
        ; A byte string s is given. Build the byte string d such that every byte d[i] is equal to the count of ones in the corresponding byte s[i] of s.
        ;s: 5, 25, 55, 127
        ;s in bniary: 101, 11001, 110111, 1111111
        ;d: 2, 3, 5, 7
        
        cld ;clear direction flag
        mov ecx, lens 
        mov esi, s 
        mov edi, d
        xor bl, bl ;counter
        jecxz End
        
        Repeat:
            lodsb ;al = [esi], inc esi 
            jmp count_ones 
        
        count_ones:
            test al, 1 ;verify last bit 
            jz skip
            inc bl  
        
        skip:
           shr al, 1
           jnz count_ones 
           jmp add_count 
        
        add_count:
            mov al, bl
            xor bl, bl
            stosb ;[edi] = al, inc edi
            loop Repeat 
        
        End:
        
        ;mov al, [d]
        ;mov bl, [d + 1]
        ;mov cl, [d + 2]
        ;mov dl, [d + 3]
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
