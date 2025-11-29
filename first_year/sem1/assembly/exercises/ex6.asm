bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fprintf, fread              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fread msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    len equ 100
    text1 times len db 0
    text2 times len db 0
    access_mode1 db "r", 0
    access_mode2 db "w", 0
    file_name1 db "ex6_file_in.txt", 0
    file_name2 db "ex6_file_out.txt", 0
    file_descriptor dd -1

; our code starts here
segment code use32 class=code
    start:
        push dword access_mode1
        push dword file_name1
        call [fopen]
        add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je final
        
        push dword [file_descriptor]
        push dword len
        push dword 1
        push text1
        call [fread]
        add esp, 4 * 4
        
        mov ecx, eax
        mov esi, text1
        mov edi, text2
        
        cld
        jecxz final
        convert_lowercase_letters:
            lodsb
            cmp al, 97
            jb skip
            
            cmp al, 122
            ja skip
            sub al, 32
            stosb
        loop convert_lowercase_letters
        jmp print_to_file
        
        skip:
            stosb
        loop convert_lowercase_letters
        
        print_to_file:
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        push dword access_mode2
        push dword file_name2
        call [fopen]
        add esp, 4 * 2
        mov [file_descriptor], eax
        cmp eax, 0
        je final
        
        push dword text2
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 2
        
        final:
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
