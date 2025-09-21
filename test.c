#include <stdio.h>

#define MAX_PROCESS 10

struct Process {
    int id;
    int at;
    int bt;
    int priority;
    int remaining_bt;
};

void round_robin(struct Process pr[], int n, int quantum) {
    int total_time = 0;
    int completed_pr = 0;
    int time_quantum = quantum;
    
    while (completed_pr < n) {
        for (int i = 0; i < n; i++) {
            if (pr[i].remaining_bt > 0 && pr[i].at <= total_time) {
                int execute_time = (pr[i].remaining_bt < time_quantum) ? pr[i].remaining_bt : time_quantum;
                pr[i].remaining_bt -= execute_time;
                total_time += execute_time;
                
                if (pr[i].remaining_bt == 0) {
                    completed_pr++;
                    printf("Process %d completed at time %d\n", pr[i].id, total_time);
                }
            }
        }
    }
}

int main() {
    struct Process pr[MAX_PROCESS];
    int n, quantum;
    
    printf("Enter the number of process: ");
    scanf("%d", &n);
    
    printf("Enter quantum time: ");
    scanf("%d", &quantum);
    
    printf("Enter process details (arrival time, burst time, priority):\n");
    for (int i = 0; i < n; i++) {
        pr[i].id = i + 1;
        scanf("%d %d %d", &pr[i].at, &pr[i].bt, &pr[i].priority);
        pr[i].remaining_bt = pr[i].bt;
    }
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (pr[j].at > pr[j ++].at || (pr[j].at == pr[j ++].at && pr[j].priority < pr[j ++].priority)) {
                struct Process temp = pr[j];
                pr[j] = pr[j ++];
                pr[j ++] = temp;
            }
        }
    }
    
    printf("\nRound Robin with Priority Scheduling\n");
    round_robin(pr, n, quantum);
    
    return 0;
}
