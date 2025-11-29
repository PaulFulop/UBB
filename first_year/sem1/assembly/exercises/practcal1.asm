bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf, fopen, fclose, fprintf             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    text1 db "Insert the number n here: ", 0
    text2 db "Insert words below: ", 10, 13, 0 ;10 means newline, 13 means carriage return
    format1 db "%d", 0
    format2 db "%s", 0
    access_mode db "a", 0
    file_name db "practical1.txt", 0
    file_descriptor dd -1
    wrd times 100 db 0
    n dd 0

; our code starts here
segment code use32 class=code
    start:
        push dword text1
        call [printf]
        add esp, 4
        
        push dword n
        push dword format1
        call [scanf]
        add esp, 4 * 2
        
        push dword text2
        call [printf]
        add esp, 4
        
        read_words:
            xor al, al
            mov ecx, 100
            mov edi, wrd
            jmp clear_word
            continue1:
            push dword wrd
            push dword format2
            call [scanf]
            add esp, 4 * 2 
            
            mov esi, wrd
            xor ecx, ecx
            jmp count_word_len
            continue:
            mov bl, [wrd]
            cmp bl, "#"
            je final
            
            mov dl, [wrd + ecx - 1]
            cmp bl, dl
            je verify_valid_word
         jmp read_words
         
         clear_word:
            stosb
            dec ecx
            cmp ecx, 0
            je continue1
            jmp clear_word
            
         
         count_word_len:
            lodsb
            cmp al, 0
            je continue
            inc ecx
            jmp count_word_len
         
         verify_valid_word:
            mov edx, [n]
            cmp ecx, edx
            jae add_word
            jmp read_words
        
         add_word:
            mov byte [wrd + ecx], 10
            push dword access_mode
            push dword file_name
            call [fopen]
            add esp, 4 * 2
            
            mov [file_descriptor], eax
            cmp eax, 0
            je final
            
            push dword wrd
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 2
            
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
            
            jmp read_words
            
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
