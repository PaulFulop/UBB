bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    sir dd 1234A678h, 12785634h, 1A4D3C26h
    len equ ($ - sir) / 4
    string times 100 dw 0
    format db "%d", 0

; our code starts here
segment code use32 class=code
    start:
        mov ecx, len
        mov esi, sir
        mov edi, string
        cld
        
        build_new_string:
            lodsd
            
            mov ebx, eax
            shr ebx, 24
            mov dl, ah
            mov dh, bl
            
            mov ax, dx
            stosw
        loop build_new_string
       
        xor edx, edx
        mov ecx, len
        mov esi, string
        count_ones:
            lodsw
            
            push ecx
            mov ecx, 16
            count:
               test ax, 1
               jnz increment
               shr ax, 1
           loop count
           pop ecx
       loop count_ones
       jmp final
       
        increment:
            inc edx
            shr ax, 1
            loop count
        
        final:
        push edx
        push dword format
        call [printf]
        add esp, 8
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
