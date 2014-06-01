#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>


#define THREAD_SIZE 10



void* work(void* data)
{
    
    pthread_t tid;
    tid = pthread_self();
    pthread_detach(tid); //detach thread
    fprintf(stderr,"[%d] thread 0x%08x start...\n",*(int*)data,tid);
    sleep(3);
    fprintf(stderr,"[%d] thread 0x%08x exit...\n",*(int *)data,tid);
    pthread_exit(0);
}

int main()
{
    int i;
    pthread_t pt[THREAD_SIZE];
    int args[THREAD_SIZE];

    for(i = 0; i < THREAD_SIZE; i++)
    {
        args[i] = i;
        pthread_create(&pt[i],NULL,work,&args[i]);
    }
    getchar();
    return 0;
}
