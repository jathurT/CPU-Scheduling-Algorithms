#include "process.h"

// Copy process data from source to destination
void copy_processes(Process source[], Process destination[], int n) {
  for (int i = 0; i < n; i++) {
    destination[i] = source[i];
    destination[i].waiting_time = 0;
    destination[i].turnaround_time = 0;
    destination[i].remaining_time = source[i].burst_time;
    destination[i].completion_time = 0;
    destination[i].response_time = -1; // Initialize response time to -1 (not started)
  }
}

// Sort processes by arrival time
void sort_by_arrival_time(Process processes[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (processes[j].arrival_time > processes[j + 1].arrival_time) {
        Process temp = processes[j];
        processes[j] = processes[j + 1];
        processes[j + 1] = temp;
      }
    }
  }
}

// Print process table with details
void print_process_table(Process processes[], int n) {
  printf("\nProcess\tArrival\tBurst\tPriority\tCompletion\tResponse\tWaiting\tTurnaround\n");
  printf("---------------------------------------------------------------------------------\n");
  for (int i = 0; i < n; i++) {
    printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\t%d\n",
           processes[i].id, processes[i].arrival_time,
           processes[i].burst_time, processes[i].priority,
           processes[i].completion_time, processes[i].response_time,
           processes[i].waiting_time, processes[i].turnaround_time);
  }
  printf("---------------------------------------------------------------------------------\n");
}

// Print average waiting and turnaround times
void print_average_times(Process processes[], int n) {
  float avg_waiting = 0, avg_turnaround = 0, avg_response = 0;
  for (int i = 0; i < n; i++) {
    avg_waiting += processes[i].waiting_time;
    avg_turnaround += processes[i].turnaround_time;
    avg_response += processes[i].response_time;
  }
  avg_waiting /= n;
  avg_turnaround /= n;
  avg_response /= n;

  printf("\nAverage Waiting Time: %.2f\n", avg_waiting);
  printf("Average Turnaround Time: %.2f\n", avg_turnaround);
  printf("Average Response Time: %.2f\n", avg_response);
}

// Print Gantt chart for visualization
void print_gantt_chart(int process_order[], int start_times[], int completion_times[], int n) {
  // Print top border
  printf(" ");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < completion_times[i] - start_times[i]; j++) {
      printf("-");
    }
    printf(" ");
  }
  printf("\n|");

  // Print process IDs
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < completion_times[i] - start_times[i] - 1; j++) {
      printf(" ");
    }
    if (process_order[i] == 0) {
      printf("I"); // I for idle
    } else {
      printf("P%d", process_order[i]);
    }
    for (int j = 0; j < completion_times[i] - start_times[i] - 1; j++) {
      printf(" ");
    }
    printf("|");
  }
  printf("\n ");

  // Print bottom border
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < completion_times[i] - start_times[i]; j++) {
      printf("-");
    }
    printf(" ");
  }
  printf("\n");

  // Print timeline
  printf("%d", start_times[0]);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < completion_times[i] - start_times[i]; j++) {
      printf(" ");
    }
    printf("%d", completion_times[i]);
  }
  printf("\n");
}
