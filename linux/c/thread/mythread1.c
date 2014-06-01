#include "mythread.h"

#define delay 0.7


int g1 = 0;
int g2 = 0;

void * task1(int* count)
{
    while(*count < 10)
    {
        printf("thread1: count = %d\n",*count);
        (*count)++;
        sleep(delay);
    }
    pthread_exit(NULL);
}

void * task2(int* count)
{
    while(*count < 10)
    {
        printf("thread2: count = %d\n",*count);
        (*count)++;
        sleep(delay);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t  t1, t2;
    if( 0 != pthread_create(&t1, NULL, (void*)task1, (void*)&g1))
    {
        perror("thread1 create!");
    }
    if( 0 != pthread_create(&t2, NULL, (void*)task2, (void*)&g2))
    {
        perror("thread2 create!");
    }
    printf("thread1_id = %p    thread2_id = %p \n\n",t1,t2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
//    getchar();
    return 0;
}
