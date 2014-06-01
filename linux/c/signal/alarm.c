#include<stdio.h>
#include<signal.h>

static void SignalHandler(int * SIG_NUM)
{
    if(SIG_NUM == 14)
    {
        printf("This is alarm aignal handler!\n\n");
    }
    else if(SIG_NUM == SIGINT)
    {
        printf("catch SIGINT\n\n");
    }
    else
    {
        printf("catch signal:%d\n\n",SIG_NUM);
    }

    
}


int main()
{
    signal(SIGALRM,(__sighandler_t)SignalHandler);
    signal(SIGINT,(__sighandler_t)SignalHandler);
    alarm(30);
    for(;;)
    {
        pause();
    }
    return 0;

}
