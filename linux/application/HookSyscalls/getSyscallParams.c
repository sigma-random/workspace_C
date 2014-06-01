#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/user.h>


#undef __i386__
#ifndef __i386__
#define __i386__
#define EBX 0
#define ECX 1
#define EDX 2
#define ESI 3
#define EDI 4
#define EBP 5
#define EAX 6
#define DS 7
#define ES 8
#define FS 9
#define GS 10
#define ORIG_EAX 11
#define EIP 12
#define CS  13
#define EFL 14
#define UESP 15
#define SS   16
#define FRAME_SIZE 17
#endif /* __i386__ */


typedef struct user_regs_struct REGS;

REGS regs;


int getSyscallNum()//for parent process
{
    int status;
    pid_t pid;
    long orig_eax;

    while(1)
    {
        /* wait for child process status change signal */
        if(-1 == (pid = waitpid(0,&status,__WALL)))
        {
            perror("waitpid error");
            return -1;
        }
        /* child process exit */
        if(WIFEXITED(status))
        {
            printf("\n\ndetect child process exit!\n");
            break;
        }
        /* child process stopped */
        if(WIFSTOPPED(status))
        {
            printf("parent recv stopped signal from child process pid = %d\n",pid);
            //if(-1 == (orig_eax = ptrace(PTRACE_PEEKUSER, pid, 4*ORIG_EAX, NULL)))
           // {
           //     perror("PTRACE_PEEKUSER error!");
           //     return -1;
           // }
            if(-1 == ptrace(PTRACE_GETREGS, pid,NULL, &regs))
            {
                perror("PTRACE_PEEKGETREGS error!");
                return -1;
            }
            printf("\nthe child process made a syscall %d\n",regs.orig_eax);
            printf("\npress any key to resume child process:");
            getchar();
            if(-1 == ptrace(PTRACE_CONT, pid, NULL, NULL))
            //if(-1 == ptrace(PTRACE_SYSCALL, pid, NULL, NULL)) //will capture each syscall
            {
                perror("PTRACE_CONT error!");
                return -1;
            }
            printf("finished to resume child process!\n\n\n");
        }   
    }
    return 0;
}


int do_something()//for child process
{

    if(-1 == ptrace(PTRACE_TRACEME, 0, 0, 0))
    {
        perror("PTRACE_TRACEME error");
        return -1;
    }
    /* this will raise SIGTRAP signal*/
    execl("/bin/ls","-l","/",NULL);       // after a successful execve, SIGTRAP signal will send to parent process
    
    /* why here never be executed */
    while(1)
        printf("\n\n################finished...!################\n");
    return 0;
    
}

int main() 
{
    pid_t pid;
    if(-1 == (pid = fork()))
    {
        perror("fork error!");
        return -1;
    }
    if( 0 == pid)   //child process
    {
        do_something();
        exit(0);
    }
    else            //parent process
    {
        getSyscallNum();
    }
    return 0;
}
