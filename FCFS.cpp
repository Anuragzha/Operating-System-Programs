#include <stdio.h>
// Structure to represent a process
struct Process {
   int pid;      // Process ID
   int arrival;  // Arrival Time
   int burst;    // Burst Time
   int waiting;  // Waiting Time
   int turnaround; // Turnaround Time
};
 
void findWaitingTime(struct Process proc[], int n) {
   proc[0].waiting = 0;  // First process has no waiting time
 
   for (int i = 1; i < n; i++) {
       proc[i].waiting = proc[i - 1].waiting + proc[i - 1].burst;
   }
}
 
void findTurnaroundTime(struct Process proc[], int n) {
   for (int i = 0; i < n; i++) {
       proc[i].turnaround = proc[i].waiting + proc[i].burst;
   }
}
 
void findAverageTime(struct Process proc[], int n) {
   int total_waiting = 0, total_turnaround = 0;
 
   findWaitingTime(proc, n);
   findTurnaroundTime(proc, n);
 
   printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
   for (int i = 0; i < n; i++) {
       total_waiting += proc[i].waiting;
       total_turnaround += proc[i].turnaround;
       printf("%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].arrival, proc[i].burst, proc[i].waiting, proc[i].turnaround);
   }
 
   printf("\nAverage Waiting Time = %.2f", (float)total_waiting / n);
   printf("\nAverage Turnaround Time = %.2f\n", (float)total_turnaround / n);
}
 
int main() {
   int n;
   printf("Enter number of processes: ");
   scanf("%d", &n);
 
   struct Process proc[n];
 
   printf("Enter Process ID, Arrival Time, and Burst Time for each process:\n");
   for (int i = 0; i < n; i++) {
       printf("Process %d: ", i + 1);
       scanf("%d %d %d", &proc[i].pid, &proc[i].arrival, &proc[i].burst);
   }
 
   findAverageTime(proc, n);
 
   return 0;
}
