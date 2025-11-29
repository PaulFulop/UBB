bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 2
    b db 2
    c db 5
    d db 3
    e dd 4
    x dq 4

; our code starts here
segment code use32 class=code
    start:
        ;(a*2+b/2+e)/(c-d)+x/a = (4 + 1 + 4) / 2 + 2 = 4 + 2 = 6, r = 1
        mov edx, 0
        mov ax, 2
        mov dx, [a]
        mul dx ;dx:ax = 2 * a
        mov cx, ax ;dx:cx = 2 * a
        
        mov al, [b]
        mov ah, 0 ;ax = b
        mov bl, 2
        div bl ;al = ax / 2 = b / 2, ah = ax % 2
        mov bl, al
        
        mov ax, cx
        add al, bl
        adc ah, 0 ;dx:ax = 2 * a + b / 2
        
        add ax, [e] ;lower partbx ;ax = (a*2+b/2+e)/(c-d) = 4, dx = (a*2+b/2+e) % (c - d) = 1
        
        mov ebx, 0
        mov bx, ax 
        mov eax, [x]
        mov edx, [x + 4]
        mov ecx, 0
        mov cx, [a]
        div ecx ;eax = x/a, edx = x % a, eax = 2, edx = 0
        
        add eax, ebx; eax = (a*2+b/2+e)/(c-d)+x/a = 6
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
