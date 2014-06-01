#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/signal.h>
#include <sys/user.h>


#define procmsg printf
typedef struct user_regs_struct REGS;


int readRegs(pid_t pid, REGS *p_regs) 
{
        if( -1 == ptrace(PTRACE_GETREGS, pid, 0, p_regs))
        {   
                perror("ptrace getregs");
                return -1; 
        }   
        procmsg("|-----------------------------------------------------------------------------------|\n");
        procmsg("|  eip=0x%08x  ebp=0x%08x  esp=0x%08x  esi=0x%08x  edi=0x%08x\n",p_regs->eip,p_regs->ebp,p_regs->esp,p_regs->esi,p_regs->edi);
        procmsg("|  eax=0x%08x  ebx=0x%08x  ecx=0x%08x  edx=0x%08x\n",p_regs->eax,p_regs->ebx,p_regs->ecx,p_regs->edx);
        procmsg("|   cs=0x%08x   ds=0x%08x   es=0x%08x   ss=0x%08x\n",p_regs->xcs,p_regs->xds,p_regs->xes,p_regs->xss);
        procmsg("|   gs=0x%08x   fs=0x%08x\n",p_regs->xgs,p_regs->xfs,p_regs->eflags);
        procmsg("|                                                               eflags=0x%08x\n",p_regs->eflags);
        procmsg("|-----------------------------------------------------------------------------------|\n");

        return 0;     
}

int attach_pid(pid_t pid)
{
     
    if(pid <= 1)
    {
        printf("pid error\n");
        return -1;
    }
    /* if target process has been PTRACE_TARCEME , attach will fail */
    if(-1 == ptrace(PTRACE_ATTACH, pid, 0, 0))
    {
        perror("ptrace PTRACE_ATTACH");
        return -1;
    }
    return 0;
}

int detach_pid(pid_t pid)
{
     
    if(pid <= 1)
    {
        printf("pid error\n");
        return -1;
    }

    if(-1 == ptrace(PTRACE_DETACH, pid, 0, 0))
    {
        perror("ptrace PTRACE_DETACH");
        return -1;
    }
    return 0;
}

int run_debugger(pid_t pid) 
{
    pid_t r_pid;
    int status;
    REGS regs;
    procmsg("[+] debugger start...\n");
    printf("[+] start to attach process pid %d\n",pid);
    /* attach process */
    if( -1 == attach_pid(pid)) 
    {
        printf("[-] fail to attach process pid %d\n",pid);
        return -1;
    }
    printf("[+] success to attach process pid %d\n",pid);
    
    if(-1 == (r_pid = waitpid(pid,&status,__WALL))){
        perror("waitpid error");
        return -1;
    }
    if(WIFSTOPPED(status)) 
    { 
        printf("[+] ****** attaching to  process pid %d\n",r_pid);
    
        /* read tracee regs info */
        readRegs(pid, &regs);
        
        printf("press any key to detach:");
        getchar();
    
        printf("[+] start to detach process pid %d\n",pid);
        /* detach process */
        if( -1 == detach_pid(pid)) 
        {
            printf("[-] fail to detach process pid %d\n",pid);
            return -1;
        }
        printf("[+] success to detach process pid %d\n",pid);
    }

    return 0;
}


int main(int argc, char **argv) 
{

    pid_t pid;

    if(argc != 2) {

        fprintf(stderr, "usage: %s pid\n",argv[0]);
        exit(-1);
    }
    pid = atoi(argv[1]);
    run_debugger(pid);
    return 0;
}

