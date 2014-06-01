#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>


int main(int argc, char **argv)
{

    pid_t pid,ppid;
    int status;
    printf("I'm child process, pid: %d  ppid: %d\n",getpid(),getppid());
    if((pid = fork()) < 0)
    {
        perror("fork error!\n");
    }
    else if(pid == 0)   //child process
    {
        ppid = getppid();
        pid = getpid();
        chdir("/tmp");
        setsid();   //becaom session leader
        umask(0);
        printf("I'm child process, pid: %d  ppid: %d\n",pid,ppid);
        exit(0);
    }else
    {
        if(waitpid(pid,&status,0)<0)
        {
            printf("waitpid error!\n");
        }
        printf("parent process starts to sleep!\n");
        sleep(50);
    }
    return 0;
}
