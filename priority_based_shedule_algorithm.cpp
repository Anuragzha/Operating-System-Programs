#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;       // Process ID
    int arrival;   // Arrival Time
    int burst;     // Burst Time
    int priority;  // Priority (Lower value means higher priority)
    int waiting;   // Waiting Time
    int turnaround; // Turnaround Time
};

// Function to sort processes by priority (If same priority, sort by arrival time)
void sortByPriority(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority || 
               (proc[i].priority == proc[j].priority && proc[i].arrival > proc[j].arrival)) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate waiting and turnaround times
void findTimes(struct Process proc[], int n) {
    int total_waiting = 0, total_turnaround = 0;
    int time = 0;

    printf("\nProcess\tPriority\tArrival\tBurst\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++) {
        proc[i].waiting = (time > proc[i].arrival) ? time - proc[i].arrival : 0;
        time += proc[i].burst;
        proc[i].turnaround = proc[i].waiting + proc[i].burst;

        total_waiting += proc[i].waiting;
        total_turnaround += proc[i].turnaround;

        printf("%d\t%d\t\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].priority, proc[i].arrival, proc[i].burst, proc[i].waiting, proc[i].turnaround);
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_waiting / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_turnaround / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    printf("Enter Process ID, Arrival Time, Burst Time, and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d %d", &proc[i].pid, &proc[i].arrival, &proc[i].burst, &proc[i].priority);
    }

    // Sort processes by priority
    sortByPriority(proc, n);

    // Compute and display scheduling results
    findTimes(proc, n);

    return 0;
}
