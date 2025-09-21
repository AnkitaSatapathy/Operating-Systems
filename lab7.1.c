#include <stdio.h>
#include <unistd.h> 

void processInfo(int pid) {
    printf("Child ID: %d, Parent ID: %d\n", pid, getppid());
}
int main() {
    // Single Child Process
    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("fork failed");
        return 1;
    } else if (pid1 == 0) {
        // Child process
        processInfo(getpid());
    } else {
        // Parent process
        processInfo(getpid());
        // Wait for child to finish (optional)
        // wait(NULL);
    }
    // Binary Tree
    pid_t pid2 = fork();

    if (pid2 < 0) {
        perror("fork failed");
        return 1;
    } else if (pid2 == 0) {
        // Left child
        processInfo(getpid());
        // Can further fork to create sub-processes
    } else {
        // Parent process
        processInfo(getpid());
        pid_t pid3 = fork();

        if (pid3 < 0) {
            perror("fork failed");
            return 1;
        } else if (pid3 == 0) {
            // Right child
            processInfo(getpid());
            // Can further fork to create sub-processes
        } else {
            processInfo(getpid());
        pid_t pid4 = fork();

        if (pid4 < 0) {
            perror("fork failed");
            return 1;
        } else if (pid4 == 0) {
            // Right child
            processInfo(getpid());
            // Can further fork to create sub-processes
        } else {
            // Parent process (original)
            processInfo(getpid());
            // Wait for children (optional)
            // wait(NULL);
            // wait(NULL);
        }
        }
    }

    return 0;
}