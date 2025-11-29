bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          
extern fopen, fread, fclose, printf
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

extern build_array

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    filename db "numbers.txt", 0
    r db "r", 0
    len equ 100
    file_descriptor db -1
    nums times len db 0
    format db "%d, ", 0
    copy db 0

; our code starts here
segment code use32 class=code
    start:
        push dword r
        push dword filename
        call [fopen]
        add esp, 8
        
        mov [file_descriptor], eax
        cmp eax, 0
        je end
        
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword nums
        call [fread]
        add esp, 16
        
        lea ebx, [nums]
        push dword eax
        push dword ebx
        call build_array
        add esp, 8
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        end:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
