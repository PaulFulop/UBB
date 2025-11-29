bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fprintf, fread, fclose, fopen               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          
import fprintf msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_in db "in.txt", 0
    file_out db "out.txt", 0
    access_r db "r", 0
    access_w db "w", 0
    format_w db "The sum of all the digits in the text is: %d", 0
    file_descriptor db -1
    len equ 100
    text times len db 0
    

; our code starts here
segment code use32 class=code
    start:
        ;A file name and a text (which can contain any type of character) are given in data segment.
        ;Calculate the sum of digits in the text. Create a file with the given name and write the result to file.
        ;final sum should be 46 for the given in.txt file
        
        push dword access_r
        push dword file_in 
        call [fopen]
        add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je end
        
        push dword [file_descriptor]
        push dword len 
        push dword 1
        push dword text
        call [fread]
        add esp, 4 * 4
        
        mov ecx, eax
        xor eax, eax
        xor ebx, ebx
        mov esi, text
        
        add_digits:
            lodsb
            cmp al, '0'
            jb not_digit
            cmp al, '9'
            ja not_digit
            
            sub al, '0'
            add ebx, eax
        loop add_digits
        jmp write_to_file
        
        not_digit:
            loop add_digits
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
            
        write_to_file:
            push dword access_w
            push dword file_out
            call [fopen]
            add esp, 4 * 2
            
            mov [file_descriptor], eax
            cmp eax, 0
            je end
            
            push dword ebx
            push dword format_w
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 3
            
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
            
        end:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
