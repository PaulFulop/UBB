bits 32                         
segment code use32 public code
global convert_base2

extern printf
import printf msvcrt.dll

segment data use32 class=data
    bits_arr times 33 db 0
    format2 db "%s, ", 0
    
convert_base2:
    mov edx, [esp + 4]
    mov ecx, 32
    lea ebx, [bits_arr + 31]
    
    convert_loop:
        mov eax, edx
        and eax, 1
        add al, '0'
        mov [ebx], al
        dec ebx
        shr edx, 1
    loop convert_loop
    
    mov byte [bits_arr + 32], 0
    
    push dword bits_arr
    push dword format2
    call [printf]
    add esp, 8
    ret