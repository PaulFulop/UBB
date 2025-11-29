; The following program should read a number and print the message together with the number on the screen.
bits 32
global start        

; declaring extern functions used in the program
extern exit, printf, scanf            
import exit msvcrt.dll     
import printf msvcrt.dll     ; indicating to the assembler that the printf fct can be found in the msvcrt.dll library
import scanf msvcrt.dll      ; similar for scanf
                          
segment  data use32 class=data
    a dd 0
    b dd 0
    quotient dd 0
    remainder dd 0
    format db "%d %d", 0
    message1 db "Read a and b: ", 0
    message2 db "a / b = %d with remainder %d", 0
        
segment  code use32 class=code
    start:
        push dword message1
        call [printf]
        add esp, 4
        
        push dword b
        push dword a
        push dword format
        call [scanf]
        add esp, 4 * 3
        
        mov eax, [a]
        mov ebx, [b]
        cdq
        idiv ebx
        
        push edx
        push eax
        push dword message2
        call [printf]
        add esp, 4 * 3
        
        ; exit(0)
        push  dword 0     ; push the parameter for exit on the stack
        call  [exit]       ; call exit