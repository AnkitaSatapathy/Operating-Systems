#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a process
typedef struct Process {
    int pid;            // Process ID
    int arrival_time;   // Arrival Time
    int burst_time;     // Burst Time
    struct Process* next; // Pointer to next process in the linked list
} Process;

// Function to create a new process
Process* createProcess(int pid, int arrival_time, int burst_time) {
    Process* newProcess = (Process*)malloc(sizeof(Process));
    if (newProcess == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newProcess->pid = pid;
    newProcess->arrival_time = arrival_time;
    newProcess->burst_time = burst_time;
    newProcess->next = NULL;
    return newProcess;
}

// Function to insert a process at the end of the linked list
void insertProcess(Process** head, Process* newProcess) {
    if (*head == NULL) {
        *head = newProcess;
        return;
    }
    Process* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newProcess;
}

// Function to find the process with the shortest burst time
Process* findShortestJob(Process* head, int currentTime) {
    Process* shortestJob = NULL;
    int shortestBurst = INT_MAX;
    while (head != NULL) {
        if (head->arrival_time <= currentTime && head->burst_time < shortestBurst) {
            shortestBurst = head->burst_time;
            shortestJob = head;
        }
        head = head->next;
    }
    return shortestJob;
}

// Function to remove a process from the linked list
void removeProcess(Process** head, Process* processToRemove) {
    if (*head == NULL)
        return;
    if (*head == processToRemove) {
        *head = (*head)->next;
        free(processToRemove);
        return;
    }
    Process* temp = *head;
    while (temp->next != NULL && temp->next != processToRemove) {
        temp = temp->next;
    }
    if (temp->next == NULL)
        return;
    temp->next = processToRemove->next;
    free(processToRemove);
}

// Function to calculate the completion time, turnaround time, and waiting time
void calculateTimes(Process* head, int* completionTime, int* turnaroundTime, int* waitingTime) {
    int currentTime = 0;
    while (head != NULL) {
        Process* shortestJob = findShortestJob(head, currentTime);
        *completionTime += currentTime + shortestJob->burst_time;
        *turnaroundTime += (*completionTime - shortestJob->arrival_time);
        *waitingTime += (currentTime - shortestJob->arrival_time);
        currentTime += shortestJob->burst_time;
        removeProcess(&head, shortestJob);
    }
}

// Function to calculate the average waiting time
float calculateAverageWaitingTime(Process* head, int n) {
    int completionTime = 0;
    int turnaroundTime = 0;
    int waitingTime = 0;
    calculateTimes(head, &completionTime, &turnaroundTime, &waitingTime);
    return (float)waitingTime / n;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Process* head = NULL;
    
    // Input the processes
    for (int i = 0; i < n; i++) {
        int pid, arrival_time, burst_time;
        printf("Enter details for process %d:\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &pid);
        printf("Arrival Time: ");
        scanf("%d", &arrival_time);
        printf("Burst Time: ");
        scanf("%d", &burst_time);
        
        Process* newProcess = createProcess(pid, arrival_time, burst_time);
        insertProcess(&head, newProcess);
    }
    
    // Calculate and print process table
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    int completionTime = 0;
    int turnaroundTime = 0;
    int waitingTime = 0;
    Process* temp = head;
    while (temp != NULL) {
        printf("%d\t\t%d\t\t%d", temp->pid, temp->arrival_time, temp->burst_time);
        completionTime += temp->burst_time;
        turnaroundTime += (completionTime - temp->arrival_time);
        waitingTime += (completionTime - temp->arrival_time - temp->burst_time);
        printf("\t\t%d\t\t%d\t\t%d\n", completionTime, completionTime - temp->arrival_time, completionTime - temp->arrival_time - temp->burst_time);
        temp = temp->next;
    }
    
    float avgWaitingTime = calculateAverageWaitingTime(head, n);
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    
    return 0;
}
