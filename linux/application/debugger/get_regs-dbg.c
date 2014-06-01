#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/user.h>

#define procmsg printf


typedef struct user_regs_struct REGS;


int run_target(char *app_name) 
{
    procmsg("target started. will run '%s' \n",app_name);
    /* Allow tracing of this process*/
    if( ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) 
    {
        perror("ptrace");
        return -1;
    }
    /*call execl will send SIGTRAP signal */
    execl(app_name, app_name,NULL);
    procmsg("[child] finished execl!\n");
    return 0;
}





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
    //procmsg("|                                                                                   |\n");
    return 0;
}

static void parseinput()
{
 
    procmsg("dbg>$ ");
    getchar();

}

int run_debugger(pid_t pid) 
{
    
    int status;
    unsigned long  counter = 0;
    REGS regs;
    unsigned int opcode;
    
    memset(&regs, 0, sizeof(REGS));
    procmsg("debugger start...\n");

    if(0 > (pid = waitpid(pid, &status, 0)))
    {
        perror("waitpid");
        return -1;
    }
    
    while(1) 
    {
        
        if(WIFEXITED(status)) 
        {
            printf("\n[+] detect process %d exit\n",pid);
            break;
        }

        if(WIFSTOPPED(status)) 
        {
            parseinput();
            counter ++;
        
            readRegs(pid,&regs);

            if( -1 ==  (opcode = ptrace(PTRACE_PEEKDATA, pid, regs.eip, 0)))
            {
                perror("ptrace peekdata");
                return -1;
            }
            procmsg("| opcode=0x%08x\n|\n|\n\n",opcode);
        
            //procmsg("[+] child process execute No.%u instruction!\n",counter);
            /** Make the child process execute another instruction*/
            if(ptrace(PTRACE_SINGLESTEP, pid, 0 ,0) < 0) 
            {
                perror("ptrace PTRACE_SINGLESTEP");
                return -1;
            }
            /*wait child process to stop on its next instruction */
            if(0 > (pid = waitpid(pid, &status, 0))) 
            {
                perror("waitpid");
                return -1;
            }
        }
    }
    procmsg("the child process has  executed %u instructions\n",counter++);
    return 0;
}


int main(int argc, char **argv) 
{

    pid_t pid;

    if(argc != 2) {

        fprintf(stderr, "usage: %s program\n",argv[0]);
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

