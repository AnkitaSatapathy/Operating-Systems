//using semaphores
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int value;
sem_t S;
//name of the lock is l
void *demo()
{
    printf("Hello\n");
    int i;
    for(i=0;i<10000;i++)
    {
        //critical section
        sem_wait (&S);
        //used to lock the ctirical section
        value++;
        sem_post (&S);
        //used to unlock the cs
    }
}

void main()
{
    pthread_t th1, th2;
    sem_init(&S,0,1);
    pthread_create(&th1, NULL, demo, NULL);
    pthread_create(&th2, NULL, demo, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    printf("Final result = %d\n",value);
}