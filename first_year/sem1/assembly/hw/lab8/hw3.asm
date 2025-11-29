bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "file1.txt", 0
    access_mode db "r", 0
    
    file_descriptor db -1
    len equ 100
    text times (len + 1) db 0
    result_text db "The number of even digits is: %d", 0

; our code starts here
segment code use32 class=code
    start:
    ;A text file is given. Read the content of the file, count the number of odd digits and display the result on the screen.
    ;The name of text file is defined in the data segment.
        mov edx, 0
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        mov [file_descriptor], eax
        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final2

        ; read the text from file using fread()
        ; after the fread() call, EAX will contain the number of chars we've read 
        ; eax = fread(text, 1, len, file_descriptor)
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword text        
        call [fread]
        add esp, 4*4
        
        mov esi, text 
        mov ecx, eax
        xor edx, edx
        
        check_digits:
            lodsb
            cmp al, '0'
            jb not_digit
            cmp al, '9'                     
            ja not_digit

            ; Check if digit is even
            sub al, '0'              
            and al, 1                        
            jz not_digit                    
            inc edx
        loop check_digits
        jmp final1
            
        not_digit:
            loop check_digits
        
        final1:
            push dword edx
            push dword result_text
            call [printf]
            add esp, 4 * 2
        
        final2:
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
