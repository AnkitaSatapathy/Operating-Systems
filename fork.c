//CREATE PROCESSES USING FORK SYSTEM CALL//

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
void create_process_tree(int level, int max_levels) {
    if (level >= max_levels) {
        return;
    }
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
    } else if (pid == 0) {
        printf("Child process: PID=%d, Parent PID=%d\n", getpid(), getppid());
        create_process_tree(level + 1, max_levels); 
    } else {
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), pid);
        wait(NULL);
    }
}
int main() {
    int max_levels = 3; 
    printf("Creating process tree with %d levels...\n", max_levels);
    create_process_tree(0, max_levels);
    return 0;
}
