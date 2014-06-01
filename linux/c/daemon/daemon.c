#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>


int main(int argc, char **argv)
{

    pid_t pid,ppid;
    if((pid = fork()) < 0)
    {
        perror("fork error!\n");
    }
    if(pid != 0)   //parent process
    {
        exit(EXIT_SUCCESS);
    }
    ppid = getppid();
    pid = getpid();
    chdir("/tmp");
    setsid();   //becaom session leader
    umask(0);
    printf("I'm a daemon now, pid: %d  ppid: %d\n",pid,ppid); 
    getchar();
    return 0;
}
