bits 32                         
global _convert_base2

segment data public data use32
    binaryString db "00000000000000000000000000000000", 0

segment code public code use32
_convert_base2:
    ;build stack frame
    push ebp
    mov ebp, esp
    pushad ;put all the registers on the stack

    mov edx, dword [ebp + 8]
    mov ecx, 32
    lea ebx, [binaryString]
    add ebx, 31
    
    convert_loop:
        mov eax, edx
        and eax, 1
        add al, '0'
        mov byte [ebx], al
        dec ebx
        shr edx, 1
    loop convert_loop
    
    popad ;get all the previous values of the registers from the stack
    mov eax, binaryString
    
    ;destroy stack frame
    mov esp, ebp
    pop ebp
    
    ret