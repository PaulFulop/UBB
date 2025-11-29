bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit  
extern scanf
extern printf             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 0
    b dd 0
    format db "%x %x", 0
    msg1 db "YES", 0
    msg2 db "NO", 0
    
; our code starts here
segment code use32 class=code
    ;Read one byte and one word from the keyboard. Print on the screen "YES" if the bits of the byte read are found consecutively among the bits of the word and "NO" otherwise. Example: a = 10 = 0000 1010b
    ;b = 256 = 0000 0001 0000 0000b
    ;The value printed on the screen will be NO.
    ;a = 0Ah = 0000 1010b
    ;b = 6151h = 0110 0001 0101 0001b
    ;The value printed on the screen will be YES (you can find the bits on positions 5-12).
    start:
        push dword b
        push dword a
        push format
        call [scanf]
        add esp, 4 * 3
        
        xor eax, eax
        mov al, [a]
        mov ebx, [b]
        mov edx, ebx
        
        mov ecx, 25
        find_substr:
            cmp al, bl
            je printYes
            shr ebx, 1
        loop find_substr
      
        printNo:
           push dword msg2 
           call [printf]
           add esp, 4 * 1
           jmp End
        
        printYes:
           push dword msg1 
           call [printf]
           add esp, 4 * 1
           jmp End
        
        End:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
