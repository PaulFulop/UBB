bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern printf
import printf msvcrt.dll

extern convert_base2

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nums dd 15, 1234, 39, 13
    len equ ($ - nums) / 4
    format1 db "%x, ", 0
    base16_str db "Base 16: ", 0
    base2_str db "Base 2: ", 0
    newline db 10, 13, 0
    copy resd 1

; our code starts here
segment code use32 class=code    
    start:
        push dword base16_str
        call [printf]
        add esp, 4
        
        cld
        mov ecx, len
        mov esi, nums
        print_hexa_values:
            lodsd
            push dword eax
            push dword format1
            mov [copy], ecx
            call [printf]
            mov ecx, [copy]
            add esp, 8
        loop print_hexa_values

        push dword newline
        call [printf]
        add esp, 4
        
        push dword base2_str
        call [printf]
        add esp, 4
        
        mov ecx, len
        mov esi, nums
        print_bin_values:
            lodsd
            push dword eax
            mov [copy], ecx
            
            call convert_base2
          
            mov ecx, [copy]
        loop print_bin_values

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
