
; nasm -f elf wrote.asm & ld -o write write.o 
;
;write to stdout 


[SECTION .text]
global _start
    
_start:
    jmp short enter
    starter:
    xor eax,eax
    xor ebx,ebx
    xor edx,edx
    mov al,4
    mov bl,1
    pop ecx
    mov dl,10
    int 0x80
    xor eax,eax
    mov al,1
    xor ebx,ebx
    int 0x80
    enter:
        call starter
        db 'asdf1234',0xa
