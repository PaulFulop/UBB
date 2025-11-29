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
    num dd -1
    format db "%d", 0
    text1 db "Read numbers below:", 10, 13, 0    
    text2 db "The minimum number is: %d", 0    

; our code starts here
segment code use32 class=code
    start:
        push dword text1
        call [printf]
        add esp, 4
        
        xor ebx, ebx ;storing the minimum value here
        sub ebx, 1
        
        read_numbers:
            push dword num
            push dword format
            call [scanf]
            add esp, 4 * 2
            
            mov eax, [num]
            cmp eax, 0
            je final
            
            cmp ebx, eax
            jg update_min
       jmp read_numbers
        
        update_min:
            mov ebx, eax
            jmp read_numbers
            
        final:
            push dword ebx
            push dword text2
            call [printf]
            add esp, 4 * 2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
