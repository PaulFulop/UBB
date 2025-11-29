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
    b dd 0
    c dd 0
    text db "Read the numbers here: ", 0
    format db "%d %d %d", 0
    out_msg db "The result of the expression is: %d", 0

; our code starts here
segment code use32 class=code
    compute_sum:
        mov eax, [esp + 4]
        mov ebx, [esp + 8]
        mov ecx, [esp + 12]
        add eax, ebx
        sub eax, ecx
        ret
        
    start:
        push dword text
        call [printf]
        add esp, 4
        
        push dword c
        push dword b
        push dword a
        push dword format
        call [scanf]
        add esp, 4 * 4
        
        push dword [c]
        push dword [b]
        push dword [a]
        call compute_sum
        add esp, 4 * 3
        
        push eax
        push dword out_msg
        call [printf]
        add esp, 4 * 2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
