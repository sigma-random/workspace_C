#
#   gcc -o write_1 write_1.s
#


.section .data
msg:
    .string "hello world!\x0a"
    .equ LEN,13

.section .text

.global main

main:
    movl $4,   %eax     #write
    movl $1,   %ebx
    movl $msg, %ecx 
    movl $LEN, %edx
    int  $0x80

    movl $0,   %ebx
    movl $1,   %eax     #exit
    int  $0x80

    
