#include <stdio.h>
#include <pthread.h>

int value;
pthread_mutex_t l;
//name of the lock is l
void *demo()
{
    printf("Hello\n");
    int i;
    for(i=0;i<10000;i++)
    {
        //critical section
        pthread_mutex_lock(&l);
        //used to lock the ctirical section
        value++;
        pthread_mutex_unlock(&l);
        //used to unlock the cs
    }
}

void main()
{
    pthread_t th1, th2;
    pthread_mutex_init(&l,NULL);
    pthread_create(&th1, NULL, demo, NULL);
    pthread_create(&th2, NULL, demo, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    printf("Final result = %d\n",value);
}