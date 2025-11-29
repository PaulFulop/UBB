bits 32                         
segment code use32 public code
global build_array

extern printf
import printf msvcrt.dll

segment data use32 class=data
    array db "Array: "
    format db "%d, ", 0
    new_arr times 100 dw 0
    copy db 0

build_array:
    mov ecx, [esp + 8]
    mov esi, [esp + 4]
    mov bl, 2
    mov edi, new_arr
    add esi, ecx
    sub esi, 1
    
    std
    loop1:
        lodsb
        sub al, '0'
        mul bl
        cld
        stosw   
        std
    loop loop1
        
    mov ecx, [esp + 8]
    mov esi, new_arr
    cld
    loop2:
        mov [copy], ecx
        lodsw
        xor edx, edx
        mov dx, ax
        push dword edx
        push format
        call [printf]
        add esp, 8
        mov ecx, [copy]
    loop loop2
    
    ret 