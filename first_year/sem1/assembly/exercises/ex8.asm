bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 0
    m dd 0
    n dd 0
    text1 db "Read the numbers here: ", 0
    text2 db "The final number is: %d", 0
    format db "%d %d %d", 0

; our code starts here
segment code use32 class=code
    start:
        push dword text1
        call [printf]
        add esp, 4
        
        push dword n
        push dword m
        push dword a
        push dword format
        call [scanf]
        add esp, 4 * 4
        
        mov eax, [a]
        mov cl, [n]
        shr eax, cl
        
        xor edx, edx
        sub edx, 1
        
        mov cl, 32
        sub cl, [m]
        add cl, [n]
        
        shr edx, cl
        and eax, edx
        
        push eax
        push dword text2
        call [printf]
        add esp, 4 * 2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
