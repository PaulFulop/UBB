bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fprintf, fread             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fread msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    len equ 100
    text times len db 0
    out_messae db "The final sum is: %d", 0
    access_mode1 db "r", 0
    access_mode2 db "w", 0
    file_name_in db "ex9_in.txt", 0
    file_name_out db "ex9_out.txt", 0
    file_descriptor dd -1

; our code starts here
segment code use32 class=code
    start:
        push dword access_mode1
        push dword file_name_in
        call [fopen]
        add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je final1
        
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4 * 4
        
        mov esi, text
        xor ebx, ebx
        xor eax, eax
        
        cld
        add_digits:
            lodsb
            cmp al, 0
            je final1
            
            cmp al, "0"
            jb skip
            
            cmp al, "9"
            ja skip
            
            sub al, "0"
            add ebx, eax
        jmp add_digits
        
        skip:
            jmp add_digits
        
        final1:
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        push dword access_mode2
        push dword file_name_out
        call [fopen]
        add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je final2
        
        push dword ebx
        push dword out_messae
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 3
        
        final2:
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
