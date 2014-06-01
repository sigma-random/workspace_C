#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>

#define procmsg printf

int run_target(char *app_name) 
{
    procmsg("target started. will run '%s' \n",app_name);
    /* Allow tracing of this process*/
    if( ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) 
    {
        perror("ptrace");
        return -1;
    }
    /* call execl will send SIGTRAP signal */
    execl(app_name, app_name,NULL);
    procmsg("[child] finished execl!\n");
    return 0;
}


int run_debugger(pid_t pid) 
{
    
    int status;
    int counter = 0;

    procmsg("debugger start...\n");
    if(0 > (pid = waitpid(pid, &status, 0)))
    {
        perror("waitpid");
        return -1;
    }
    //while(WIFSTOPPED(status)) 
    while(1) 
    {
        if(WIFEXITED(status))
        {
            procmsg("\n[+] the child process has  executed %u instructions\n",counter++);
            printf("\n[+] detect rocess %d exit\n",pid);
            break;
        }
        if(WIFSTOPPED(status))
        {
            counter ++;
            /** Make the child process execute another instruction*/
            if(ptrace(PTRACE_SINGLESTEP, pid, 0 ,0) < 0) 
            {
                perror("ptrace PTRACE_SINGLESTEP");
                return -1;
            }
            procmsg("[+] child process execute No.%u instruction!\n",counter);
            /*wait child process to stop on its next instruction */
            if(0 > (pid = waitpid(pid, &status, 0))) 
            {
                perror("waitpid");
                return -1;
            }
        }
    }
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

