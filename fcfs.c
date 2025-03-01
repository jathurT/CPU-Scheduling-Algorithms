#include "process.h"

// First Come First Serve (FCFS) Scheduling Algorithm
void fcfs_scheduling(Process processes[], int n) {
  sort_by_arrival_time(processes, n);

  int current_time = 0;
  int process_order[100];  // To store process execution order
  int start_times[100];    // Start times of each process execution
  int completion_times[100]; // Completion times of each process execution
  int chart_index = 0;

  // For each process
  for (int i = 0; i < n; i++) {
    // If current time is less than arrival time, CPU is idle
    if (current_time < processes[i].arrival_time) {
      process_order[chart_index] = 0; // 0 indicates CPU idle
      start_times[chart_index] = current_time;
      current_time = processes[i].arrival_time;
      completion_times[chart_index] = current_time;
      chart_index++;
    }

    // Calculate response time when process first gets CPU
    processes[i].response_time = current_time - processes[i].arrival_time;

    // Execute current process
    process_order[chart_index] = processes[i].id;
    start_times[chart_index] = current_time;
    current_time += processes[i].burst_time;
    completion_times[chart_index] = current_time;
    chart_index++;

    // Update process metrics
    processes[i].completion_time = current_time;
    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
  }

  // Print Gantt chart
  printf("\nGantt Chart:\n");
  print_gantt_chart(process_order, start_times, completion_times, chart_index);
}