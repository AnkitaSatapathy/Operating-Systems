#include <stdio.h>
#include <pthread.h>


void *demo()
{
    printf("Hello\n");
}

void main()
{
    pthread_t th1, th2;
    pthread_create(&th1, NULL, demo, NULL);
    pthread_create(&th2, NULL, demo, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
}