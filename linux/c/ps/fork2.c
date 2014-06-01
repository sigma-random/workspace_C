#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>


int main(int argc, char **argv)
{
    pid_t pid;
    int status;
    printf("I'm parent process, pid: %d  ppid: %d\n",getpid(),getppid());
    if((pid = fork()) < 0)
    {
        perror("fork error!\n");
    }
    else if(pid == 0)   //child process
    {
        while(getppid() != 1)
        {
            printf("I'm child process, pid: %d  ppid: %d\n",getpid(),getppid());
            sleep(1);
        }
        printf("I'm child process, pid: %d  ppid: %d\n",getpid(),getppid());
        sleep(2);
    }else
    {
        sleep(1);
        printf("parent process starts to sleep!\n");
        printf("child process will belong to init process which pid is 1!\n");
    }
    return 0;
}
