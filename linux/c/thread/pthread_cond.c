#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>


#define THREAD_NUM 10
#define MAX_NUM  10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;


int sum = 0;

void *do_wait(void* data)
{
    pthread_detach(pthread_self());
    printf("wait_thread start do_wait()\n");
    pthread_mutex_lock(&mutex);
    while(sum <= MAX_NUM )
    {
        fprintf(stderr,"main_thread , sum = %d\n",sum);
        pthread_cond_wait(&cond,&mutex);
    }
    pthread_mutex_unlock(&mutex);
    printf("wait_thread is over\n");
    pthread_exit(0);
}


void *do_count(void* data )
{
    int i = *(int*)data;

    pthread_detach(pthread_self());
    pthread_mutex_lock(&mutex);
    printf("counter thread %d start..\n",i);
    sum += i;
    if(sum > MAX_NUM)
    {
        pthread_cond_signal(&cond);
    }
    printf("counter thread %d : sum = %d\n",i,sum);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);

}


int main()
{
    int i = 0;
    pthread_t thread[THREAD_NUM];
    int args[THREAD_NUM];
        
    pthread_create(&thread[THREAD_NUM-1],NULL,do_wait,NULL);
    for(; i < THREAD_NUM - 1; i++)
    {
        args[i] = i;
        pthread_create(&thread[i],NULL,do_count,(void*)(&args[i]));
    }
    printf("********** hold on! ********\n\n");
    sleep(5);
    printf("sum is %d\n",sum);

    pthread_mutex_destroy(&mutex);        
    pthread_cond_destroy(&cond);        
    return 0;

}

