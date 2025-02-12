//Round robin scheduling algorithm:
#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;       // Process ID
    int arrival;   // Arrival Time
    int burst;     // Burst Time
    int remaining; // Remaining Time (for execution)
    int waiting;   // Waiting Time
    int turnaround; // Turnaround Time
};

// Function to perform Round Robin Scheduling
void roundRobin(struct Process proc[], int n, int quantum) {
    int time = 0, completed = 0;
    int total_waiting = 0, total_turnaround = 0;

    printf("\nGantt Chart:\n");
    while (completed < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining > 0) {
                printf("| P%d (%d-%d) ", proc[i].pid, time, time + (proc[i].remaining > quantum ? quantum : proc[i].remaining));

                if (proc[i].remaining > quantum) {
                    time += quantum;
                    proc[i].remaining -= quantum;
                } else {
                    time += proc[i].remaining;
                    proc[i].waiting = time - proc[i].arrival - proc[i].burst;
                    proc[i].turnaround = time - proc[i].arrival;
                    total_waiting += proc[i].waiting;
                    total_turnaround += proc[i].turnaround;
                    proc[i].remaining = 0;
                    completed++;
                }
                executed = 1;
            }
        }
        
        // If no process is executed, increase time to next available process
        if (!executed) {
            time++;
        }
    }
    printf("|\n");

    // Print process details
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].arrival, proc[i].burst, proc[i].waiting, proc[i].turnaround);
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_waiting / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_turnaround / n);
}

int main() {
    int n, quantum;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process proc[n];

    printf("Enter Process ID, Arrival Time, and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].pid, &proc[i].arrival, &proc[i].burst);
        proc[i].remaining = proc[i].burst; // Initially, remaining time = burst time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    roundRobin(proc, n, quantum);

    return 0;
}
