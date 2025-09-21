#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define ARRAY_SIZE 10
int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int result[2];
void *add_from_beginning(void *arg) {
    int i;
    result[0] = 0;
    for (i = 0; i < ARRAY_SIZE / 2; ++i) {
        result[0] += arr[i];
    }
    return NULL;
}
void *add_from_end(void *arg) {
    int i;
    result[1] = 0;
    for (i = ARRAY_SIZE / 2; i < ARRAY_SIZE; ++i) {
        result[1] += arr[i];
    }
    return NULL;
}
int main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, add_from_beginning, NULL);
    pthread_create(&thread2, NULL, add_from_end, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    int total_sum = result[0] + result[1];
    printf("Total sum: %d\n", total_sum);
    return 0;
}
