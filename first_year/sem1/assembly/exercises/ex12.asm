bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, printf, scanf, fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
import fprintf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    access_mode db "a", 0
    file_descriptor dd -1
    number dd 0
    text db "Read numbers below: ", 10, 13, 0
    format1 db "%d", 0
    format2 db "%d, ", 0
    file_name db "ex12_txt_file.txt", 0

; our code starts here
segment code use32 class=code
    start:
        push dword text
        call [printf]
        add esp, 4
        
        xor ebx, ebx
        mov bl, 7
        
        get_numbers:
            push dword number
            push dword format1
            call [scanf]
            add esp, 4 * 2
            
            mov eax, [number]
            cmp eax, 0
            je final
            
            div bx
            cmp dl, 0
            je add_num_to_file
        jmp get_numbers
        
        
        add_num_to_file:
            mul ebx
            push eax
            push dword access_mode
            push dword file_name
            call [fopen]
            add esp, 4 * 2
            
            mov [file_descriptor], eax
            cmp eax, 0
            je skip
            
            push dword format2
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 3
            
            skip:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
        jmp get_numbers
            
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
