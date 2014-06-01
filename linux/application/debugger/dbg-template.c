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
    /* each process only be allowed set PTARCE_TARCEME once!*/
    if( ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) 
    {
        perror("ptrace");
        return -1;
    }
    procmsg("[child] start to run %s!\n",app_name);
    /* call execl will send SIGTRAP signal */
    execl(app_name, app_name,NULL);
    procmsg("[child] finished execl!\n");
    return 0;
}


int run_debugger(pid_t pid) 
{
    
    int status;
    procmsg("debugger start...\n");
    /* capture SIGTARP signal */
    if( 0 > (pid = waitpid(pid, &status, 0)))
    {
        perror("waitpid");
        return -1;
    }
    while(1)
    {
        if(WIFEXITED(status))
        {
            printf("[+] child process exit!\n");
            break;
        }
        if(WIFSTOPPED(status)) 
        {
            printf("[+] child process send signal %d \n",WSTOPSIG(status));
    
            /* resume child process to run */
            if(-1 == ptrace(PTRACE_CONT, pid, 0, 0))
            {
                perror("PTRACE_CONT");
                return -1;
            }

        }
        /* capture SIGEXIT signal */
        if( 0 > (pid = waitpid(pid, &status, 0)))
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
    procmsg("[parent] press any to quit!\n");
    getchar();
    return 0;
}

