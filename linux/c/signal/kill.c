#include<stdio.h>
#include<signal.h>


    

int main(int argc, char** argv)
{
    pid_t pid = atoi(argv[1]);
    int sigNum = atoi(argv[2]);
    kill(pid,sigNum);
    printf("send signal %d to PID:%d\n\n",sigNum,pid);
    pause();
    return 0;

}
