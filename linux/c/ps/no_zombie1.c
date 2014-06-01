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
        printf("I'm child process, pid: %d  ppid: %d\n",pid,ppid);
        printf("I'm zombie now\n");
        exit(0);
   
    }else
    {
        //waitpid(-1,&status,WNOHANG);  /* will make child process a zombie*/
        waitpid(-1,&status,0);        /* wait for child's exiting,and collect child resourcees*/
        sleep(50);
    }
    return 0;
}
