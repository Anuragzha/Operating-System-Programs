//SJF:
#include <stdio.h>
 
// Structure to represent a process
struct Process {
   int pid;      // Process ID
   int arrival;  // Arrival Time
   int burst;    // Burst Time
   int waiting;  // Waiting Time
   int turnaround; // Turnaround Time
   int completed; // Completion status
};
 
// Function to sort processes by Burst Time (SJF)
void sortByBurstTime(struct Process proc[], int n) {
   for (int i = 0; i < n - 1; i++) {
       for (int j = i + 1; j < n; j++) {
           if (proc[i].burst > proc[j].burst) {
               struct Process temp = proc[i];
               proc[i] = proc[j];
               proc[j] = temp;
           }
       }
   }
}
 
// Function to calculate waiting time and turnaround time
void findTimes(struct Process proc[], int n) {
   int total_waiting = 0, total_turnaround = 0;
   int time = 0;
 
   printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
 
   for (int i = 0; i < n; i++) {
       proc[i].waiting = (time > proc[i].arrival) ? time - proc[i].arrival : 0;
       time += proc[i].burst;
       proc[i].turnaround = proc[i].waiting + proc[i].burst;
 
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
       proc[i].completed = 0;
   }
 
   // Sort processes by burst time for SJF
   sortByBurstTime(proc, n);
 
   findTimes(proc, n);
 
   return 0;
}
