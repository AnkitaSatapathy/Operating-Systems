#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int num_children = 3; // Number of child processes to create (adjust as needed)

    // Create child processes
    for (int i = 0; i < num_children; i++) {
        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (child_pid == 0) {
            // Child process code
            printf("Child process %d started (PID: %d)\n", i + 1, getpid());
            // Simulate work (e.g., sleep for some time)
            sleep(1); // Adjust sleep time as needed
            printf("Child process %d finished\n", i + 1);
            exit(0);
        } else {
            // Parent process code
            printf("Parent process created child process %d (PID: %d)\n", i + 1, child_pid);
        }
    }
    printf("\n\n\n\n\n");
    // Wait for all child processes to finish
    for (int i = 0; i < num_children; i++) {
        wait(NULL); // Wait for any child process to finish
    }

    printf("Parent process finished waiting for all child processes\n");
    return 0;
}