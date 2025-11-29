bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, printf, fclose              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          
import fopen msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "ex5_file.txt", 0
    access_mode db "r", 0
    format db "The number of vowels is: %d", 0
    file_descriptor dd -1
    len equ 100
    text times len db 0

; our code starts here
segment code use32 class=code
    start:
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je final
        
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4 * 4
        
        mov esi, text
        mov ecx, eax
        xor edx, edx
        
        count_vowels:
            lodsb
            cmp al, 0
            je finish
            
            cmp al, 'a'
            je increment
            cmp al, 'e'
            je increment
            cmp al, 'i'
            je increment 
            cmp al, 'o'
            je increment
            cmp al, 'u'
            je increment
            
            cmp al, 'A'
            je increment
            cmp al, 'E'
            je increment
            cmp al, 'I'
            je increment 
            cmp al, 'O'
            je increment
            cmp al, 'U'
            je increment
        jmp count_vowels 
        
        increment:
            inc edx
            jmp count_vowels
                
        finish:
        
        push edx
        push dword format
        call [printf]
        add esp, 4 * 2
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
