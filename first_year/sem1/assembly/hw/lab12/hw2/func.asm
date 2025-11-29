bits 32                         
global _build_str

segment data public data use32
    p_string times 100 db 0
    n_string times 100 db 0
    
segment code public code use32
_build_str:
    ;build stack frame
    push ebp
    mov ebp, esp
    pushad
    
    mov esi, [ebp + 8] ;address to the start of the string
    mov ecx, dword [ebp + 12] ; length
    mov edx, dword [ebp + 16] ;sign
    
    cld
    test edx, edx
    jnz for_negatives
    
    mov edi, p_string
    build_for_positives:
        lodsb
        cmp al, '-'
        je skip_negative_number
        cmp al, ' '
        je skip
        stosb 
        skip:
    loop build_for_positives
    popad
    mov eax, p_string
    jmp ending
    
    for_negatives:
    
    mov edi, n_string
    
    build_for_negatives: 
        lodsb
        cmp al, '-'
        je add_negative_number
    loop build_for_negatives
    popad
    mov eax, n_string
    jmp ending
    
    skip_negative_number:
        cmp al, ' '
        je skip
        lodsb
    loop skip_negative_number
    popad
    mov eax, p_string
    jmp ending
    
    add_negative_number:
        stosb
        lodsb
        cmp al, ' '
        je build_for_negatives
    loop add_negative_number
    popad
    mov eax, n_string
    ending:

    ;destroy stack frame
    mov esp, ebp
    pop ebp
    ret