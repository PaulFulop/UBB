bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fprintf             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    text db "abcdefghi jklmn", 0
    new_text times 100 db 0
    access_mode db "w", 0
    file_descriptor dd -1
    file_name db "ex_13_file.txt", 0
    format db "%s", 0

; our code starts here
segment code use32 class=code
    convert_to_str:
        mov eax, [esp + 4]
        cmp eax, 9
        jle return
        
        cld
        mov ebx, 10
        convert:
            xor edx, edx 
            div ebx
            
            push eax
            mov al, dl
            add al, "0"
            stosb
            pop eax
            cmp eax, 9
            jle return
        jmp convert
        
        return:
            add al, "0"
            stosb
            ret
    
    start:
        mov esi, text
        mov edi, new_text
        
        cld
        replace_letters:
            lodsb
            cmp al, 0
            je final
            mov ebx, esi
            dec ebx
            sub ebx, text
            test ebx, 1
            jz replace
            stosb
        jmp replace_letters
        
        
        replace:
            push ebx
            call convert_to_str
        jmp replace_letters
        
        final:
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je skip
        
        push dword new_text
        push dword format
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 3
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        skip:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
