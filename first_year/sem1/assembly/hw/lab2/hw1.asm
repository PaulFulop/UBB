bits 32
global start

extern exit ; we inform the assembler that the exit symbol is foreign; it exists even if we won't be defining it
import exit msvcrt.dll  ; we specify the external library that defines the symbol

; our variables are declared here (the segment is called data) 
segment data use32 class=data

; the program code will be part of a segment called code
segment code use32 class=code
start:
;5-6 = -1
mov AL, 5
sub AL, 6


    ; call exit(0) ), 0 represents status code: SUCCESS
    push dword 0 ; saves on stack the parameter of the function exit
    call [exit] ; function exit is called in order to end the execution of the program