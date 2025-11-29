bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    format db "%s %d", 0
    text db "Read the word and the number here: ", 0
    wrd times 50 db 0
    new_wrd times 100 db 0
    n dd 0
    

; our code starts here
segment code use32 class=code
    start:
        cld
        push dword text
        call [printf]
        add esp, 4
        
        push dword n
        push dword wrd
        push dword format
        call [scanf]
        add esp, 4 * 3
        
        mov esi, wrd
        mov edi, new_wrd
        
        mov eax, [n]
        test eax, 1
        jz even_number
        
        odd_number:
            lodsb
            cmp al, 0
            je final
            stosb
            
            cmp al, "a"
            je add_suffix
            cmp al, "e"
            je add_suffix
            cmp al, "i"
            je add_suffix
            cmp al, "o"
            je add_suffix
            cmp al, "u"
            je add_suffix

            cmp al, "A"
            je add_suffix
            cmp al, "E"
            je add_suffix
            cmp al, "I"
            je add_suffix
            cmp al, "O"
            je add_suffix
            cmp al, "U"
            je add_suffix
            
            jmp odd_number
        
        add_suffix:
            mov bl, al
            mov al, "p"
            stosb
            mov al, bl
            stosb
            jmp odd_number
            
        
        even_number:
            lodsb
            cmp al, 0
            je final
            add al, 20
            stosb
        jmp even_number
        
        final:
        
        push dword new_wrd
        call [printf]
        add esp, 4
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
