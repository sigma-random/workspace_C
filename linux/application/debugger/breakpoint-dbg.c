#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/user.h>



/*
 *
 *
 *  breakpoint by eip'increasement offbyone
 *  
 *  for testing breakpoint at 0x4000840, you should make configuration as below firstly!!
 *  
 *  1. ulimit -s unlimited
 *  2. sysctrl -w kernel.randomize_va_space=0
 *
 */


#define procmsg         printf
#define MAX_CODE_LINE   10

typedef struct user_regs_struct REGS;
typedef unsigned int UINT;

int run_target(char *app_name) 
{
    procmsg("target started. will run '%s' \n",app_name);
    /* Allow tracing of this process*/
    if( ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) 
    {
        perror("ptrace");
        return -1;
    }
    /* this will send SIGTRAP signal */
    execl(app_name, app_name,NULL);
    procmsg("[child] finished execl!\n");
    return 0;
}

inline static  void printRegs(REGS *p_regs) 
{
    procmsg("|-----------------------------------------------------------------------------------|\n");
    procmsg("|  eip=0x%08x  ebp=0x%08x  esp=0x%08x  esi=0x%08x  edi=0x%08x\n",p_regs->eip,p_regs->ebp,p_regs->esp,p_regs->esi,p_regs->edi);
    procmsg("|  eax=0x%08x  ebx=0x%08x  ecx=0x%08x  edx=0x%08x\n",p_regs->eax,p_regs->ebx,p_regs->ecx,p_regs->edx);
    procmsg("|   cs=0x%08x   ds=0x%08x   es=0x%08x   ss=0x%08x\n",p_regs->xcs,p_regs->xds,p_regs->xes,p_regs->xss);
    procmsg("|   gs=0x%08x   fs=0x%08x\n",p_regs->xgs,p_regs->xfs,p_regs->eflags);
    procmsg("|                                                               eflags=0x%08x\n",p_regs->eflags);
    procmsg("|-----------------------------------------------------------------------------------|\n");
    //procmsg("|                                                                                   |\n");

}

static void parseinput()
{
 
    procmsg("dbg>$ ");
    getchar();

}

UINT  set_breakpoint(pid_t pid,REGS* pregs, UINT* addr)
{
    UINT  opcode;
    UINT  old_code;

    procmsg("[*] child process set breakpoint at 0x%08x\n",addr);
    if( -1 == (opcode = ptrace(PTRACE_PEEKTEXT, pid, addr, 0)))
    {
        perror("ptrace peekdata");
        return -1;
    }
    //procmsg("opcode=0x%08x\n",opcode);
    old_code = opcode;
    opcode = opcode & 0xFFFFFF00 | 0xCC;
    //procmsg("alter opcode=0x%08x\n",opcode);

    if( -1 == ptrace(PTRACE_POKETEXT, pid, addr,(void*)opcode))
    {
        perror("ptrace pokedata");
        return -1;
    }
   
    /* make child process continue to run*/
    if(ptrace(PTRACE_CONT, pid, 0 ,0) < 0) 
    {
        perror("ptrace PTRACE_CONT");
        return -1;
    }
    return old_code;
}

int  remove_breakpoint(pid_t pid,REGS* pregs, UINT* addr, UINT value)
{
    UINT opcode;
     
    procmsg("[*] child process remove breakpoint at 0x%08x\n",addr);
    //procmsg("addr=0x%08x\n",addr);      
    pregs->eip -= 1;
    //procmsg("eip=0x%08x\n",pregs->eip);      

    if( -1 == ptrace(PTRACE_POKEDATA, pid, pregs->eip,(void*)value))
    {
        perror("ptrace peekdata");
        return -1;
    }

    if( -1 == ptrace(PTRACE_SETREGS, pid,0, pregs))
    {
        perror("ptrace set regs");
        return -1;
    }


    /* make child process continue to run*/
    if(ptrace(PTRACE_CONT, pid, 0 ,0) < 0) 
    {
        perror("ptrace PTRACE_CONT");
        return -1;
    }
        
    return 0;
}

int run_debugger(pid_t pid)
{
    int status;
    REGS regs;
    UINT old_opcode;
    UINT addr = 0x40000840; 
    
    procmsg("debugger start...\n");

    if(0 > (pid = waitpid(pid, &status, __WALL)))
    {
        perror("waitpid");
        return -1;
    }
    
    /* set breakpoint */
    if(WIFSTOPPED(status)) 
    {
        memset(&regs, 0, sizeof(REGS));
        if( -1 == ptrace(PTRACE_GETREGS, pid, 0, &regs))
        {
            perror("ptrace get regs");
            return -1;
        }
        printRegs(&regs);

        procmsg("[*] child process has stopped by PTRACE_TRACEME!\n\n\n");
        if( -1 == (old_opcode = set_breakpoint(pid, &regs, (UINT*)addr)))
        {
            procmsg("#######################0ops#####################\n");
            return -1;
        }
        if(0 > (pid = waitpid(pid, &status, __WALL))) 
        {
            perror("waitpid");
            return -1;
        }
        
        if( -1 == ptrace(PTRACE_GETREGS, pid, 0, &regs))
        {
            perror("ptrace get regs");
            return -1;
        }
        printRegs(&regs);
    }
    
    /* delete breakpoint */
    if(WIFSTOPPED(status)) 
    {
        procmsg("press any key to continue:");
        getchar();
        remove_breakpoint(pid, &regs, (UINT*)addr, old_opcode);
        /*wait child process to stop on its next instruction */
        if(0 > (pid = waitpid(pid, &status, 0))) 
        {
            perror("waitpid");
            return -1;
        }
    }
    return 0;
}


int main(int argc, char **argv) 
{

    pid_t pid;

    if(argc < 2) {

        fprintf(stderr, "usage: %s program   [breakpoint]\n",argv[0]);
        exit(-1);
    }
    if( 0 > (pid = fork())) {
        fprintf(stderr, "fork error!\n");
        return -1;
    }
    if( pid == 0) {   //child process
        run_target(argv[1]);
        return 0;
    }
    run_debugger(pid);
    return 0;
}

