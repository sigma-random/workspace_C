#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>

static void sig_handler(int signum)
{
    int status = 0;
    switch(signum)
    {
        case SIGCHLD:
                printf("detect child process SIGCHLD signal!\n");
                while(waitpid(-1, &status, WNOHANG));
                //while(waitpid(-1, &status, 0));
                break;
        default:
                break;
    }
}

int main(int argc, char **argv)
{

    pid_t pid,ppid;

    signal(SIGCHLD, sig_handler);    /*using signal handler to catch SIGCHLD which realese before child process exiting*/
    
    printf("I'm child process, pid: %d  ppid: %d\n",getpid(),getppid());
    if((pid = fork()) < 0)
    {
        perror("fork error!\n");
    }
    else if(pid == 0)   //child process
    {
        ppid = getppid();
        pid = getpid();
        printf("I'm child process, pid: %d  ppid: %d\n",pid,ppid);
        printf("I'm zombie now\n");
        exit(0);
   
    }else
    {
        sleep(50);
    }
    return 0;
}
