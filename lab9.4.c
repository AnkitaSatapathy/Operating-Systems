#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 2  // Maximum number of threads (2 for half-array sums)

int arr[100];  // Array to store user input (adjustable size)
int size;      // Size of the array (obtained from user)

// Shared variables (protected by a mutex)
int sum1 = 0, sum2 = 0;  
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex for thread safety

// Function to be executed by each thread
void *calculate_sum(void *arg) {
    int thread_id = *(int *)arg;
    int start_index, end_index;

    // Calculate thread-specific indices based on array size and thread ID
    if (thread_id == 0) {
        start_index = 0;
        end_index = size / 2 - 1;
        printf()
    } else {
        start_index = size / 2;
        end_index = size - 1;
    }

    int local_sum = 0;
    for (int i = start_index; i <= end_index; i++) {
        local_sum += arr[i];
    }

    // Acquire mutex before accessing shared variables
    pthread_mutex_lock(&mutex);
    if (thread_id == 0) {
        sum1 = local_sum;
    } else {
        sum2 = local_sum;
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    printf("Enter the size of the array (maximum 100): ");
    scanf("%d", &size);

    if (size > 100) {
        printf("Error: Array size cannot exceed 100.\n");
        return 1; // Exit with an error code
    }

    printf("Enter %d elements for the array:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    pthread_t threads[MAX_THREADS];
    int thread_ids[MAX_THREADS];  // Array to store thread IDs (for clarity)

    // Create threads
    for (int i = 0; i < MAX_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, calculate_sum, &thread_ids[i]) != 0) {
            perror("pthread_create failed");
            return 1; // Exit with an error code
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < MAX_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join failed");
            return 1; // Exit with an error code
        }
    }

    // Calculate total sum using the thread-safe sums
    int total_sum = sum1 + sum2;

    printf("The sum of all elements in the array is: %d\n", total_sum);

    pthread_mutex_destroy(&mutex);  // Destroy the mutex

    return 0;
}