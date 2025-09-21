#include <stdio.h>
struct Process {
    int pid;           
    int arrival_time;   
    int burst_time;     
    int remaining_time; 
    int completion_time; 
    int waiting_time;   
    int turnaround_time; 
};
void sjf_preemptive(struct Process processes[], int n) {
    int total_time = 0;
    int completed = 0;
    int min_burst_time;
    int shortest_index = -1;
    while (completed < n) {
        min_burst_time = __INT_MAX__;
        shortest_index = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= total_time && processes[i].remaining_time < min_burst_time 
                && processes[i].remaining_time > 0) {
                min_burst_time = processes[i].remaining_time;
                shortest_index = i;
            }
        }
        if (shortest_index == -1) {
            total_time++;
            continue;
        }
        processes[shortest_index].remaining_time--;
        total_time++;
        if (processes[shortest_index].remaining_time == 0) {
            completed++;
            processes[shortest_index].completion_time = total_time;
            processes[shortest_index].turnaround_time = processes[shortest_index].completion_time 
                                                        - processes[shortest_index].arrival_time;
            processes[shortest_index].waiting_time = processes[shortest_index].turnaround_time 
                                                        - processes[shortest_index].burst_time;
        }
    }
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}
int main() {
    int n; 
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n]; 
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        processes[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }
    sjf_preemptive(processes, n);
    return 0;
}
