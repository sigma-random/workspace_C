#include "mythread.h"

#define delay 1


int g = 100;

void * task1(int* count)
{
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("thread1: count = %d\n",*count);
        (*count)--;
        sleep(delay);
    }
    pthread_exit(NULL);
}

void * task2(int* count)
{
    int i;
    for(i = 0; i < 10; i++)
    {
        sleep(delay);
        printf("thread2: count = %d\n",*count);
        (*count)++;
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t  t1, t2;
    if( 0 != pthread_create(&t1, NULL, (void*)task1, (void*)&g))
    {
        perror("thread1 create!");
    }
    if( 0 != pthread_create(&t2, NULL, (void*)task2, (void*)&g))
    {
        perror("thread2 create!");
    }
    printf("thread1_id = %p    thread2_id = %p \n\n",t1,t2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
//    getchar();
    return 0;
}
