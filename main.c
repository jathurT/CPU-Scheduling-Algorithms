#include "process.h"
#include "scheduler.h"

// Main function
int main() {
  // Initialize process data as per assignment
  Process original_processes[5] = {
    {1, 1, 6, 3, 0, 0, 0, 0, -1},  // Added -1 for response_time
    {2, 3, 8, 1, 0, 0, 0, 0, -1},
    {3, 5, 2, 5, 0, 0, 0, 0, -1},
    {4, 7, 4, 2, 0, 0, 0, 0, -1},
    {5, 9, 5, 4, 0, 0, 0, 0, -1}
  };

  int n = 5; // Number of processes
  Process processes[5];

  printf("\n\n-------------------------------------------------------\n");
  printf("CPU Scheduling Algorithms Simulation\n");
  printf("-------------------------------------------------------\n\n");

  // 1. FCFS Scheduling
  printf("\n1. First Come First Serve (FCFS) Scheduling\n");
  printf("==============================================\n");
  copy_processes(original_processes, processes, n);
  fcfs_scheduling(processes, n);
  print_process_table(processes, n);
  print_average_times(processes, n);

  // 2. SJF Non-preemptive Scheduling
  printf("\n2. Shortest Job First (SJF) Scheduling - Non-preemptive\n");
  printf("==============================================\n");
  copy_processes(original_processes, processes, n);
  sjf_scheduling(processes, n);
  print_process_table(processes, n);
  print_average_times(processes, n);

  // 3. SJF Preemptive Scheduling (SRTF)
  printf("\n3. Shortest Remaining Time First (SRTF) Scheduling - Preemptive\n");
  printf("==============================================\n");
  copy_processes(original_processes, processes, n);
  srtf_scheduling(processes, n);
  print_process_table(processes, n);
  print_average_times(processes, n);

  // 4. Round Robin Scheduling
  printf("\n4. Round Robin (RR) Scheduling (Time Quantum = 4)\n");
  printf("==============================================\n");
  copy_processes(original_processes, processes, n);
  round_robin_scheduling(processes, n, 4);
  print_process_table(processes, n);
  print_average_times(processes, n);

  // 5. Priority Non-preemptive Scheduling
  printf("\n5. Priority Scheduling - Non-preemptive\n");
  printf("==============================================\n");
  copy_processes(original_processes, processes, n);
  priority_scheduling(processes, n);
  print_process_table(processes, n);
  print_average_times(processes, n);

  // 6. Priority Preemptive Scheduling
  printf("\n6. Priority Scheduling - Preemptive\n");
  printf("==============================================\n");
  copy_processes(original_processes, processes, n);
  preemptive_priority_scheduling(processes, n);
  print_process_table(processes, n);
  print_average_times(processes, n);

  // 7. Comparison of all algorithms
  printf("\n-------------------------------------------------------\n");
  printf("Comparison of Average Waiting Times:\n");
  printf("-------------------------------------------------------\n");

  // Re-run algorithms to get average waiting times
  float avg_waiting_times[6];
  float avg_response_times[6];  // Added for response time comparison
  char *algo_names[6] = {
    "FCFS",
    "SJF (Non-preemptive)",
    "SRTF (Preemptive)",
    "Round Robin",
    "Priority (Non-preemptive)",
    "Priority (Preemptive)"
  };

  // FCFS
  copy_processes(original_processes, processes, n);
  fcfs_scheduling(processes, n);
  avg_waiting_times[0] = 0;
  avg_response_times[0] = 0;
  for (int i = 0; i < n; i++) {
    avg_waiting_times[0] += processes[i].waiting_time;
    avg_response_times[0] += processes[i].response_time;
  }
  avg_waiting_times[0] /= n;
  avg_response_times[0] /= n;

  // SJF Non-preemptive
  copy_processes(original_processes, processes, n);
  sjf_scheduling(processes, n);
  avg_waiting_times[1] = 0;
  avg_response_times[1] = 0;
  for (int i = 0; i < n; i++) {
    avg_waiting_times[1] += processes[i].waiting_time;
    avg_response_times[1] += processes[i].response_time;
  }
  avg_waiting_times[1] /= n;
  avg_response_times[1] /= n;

  // SRTF Preemptive
  copy_processes(original_processes, processes, n);
  srtf_scheduling(processes, n);
  avg_waiting_times[2] = 0;
  avg_response_times[2] = 0;
  for (int i = 0; i < n; i++) {
    avg_waiting_times[2] += processes[i].waiting_time;
    avg_response_times[2] += processes[i].response_time;
  }
  avg_waiting_times[2] /= n;
  avg_response_times[2] /= n;

  // Round Robin
  copy_processes(original_processes, processes, n);
  round_robin_scheduling(processes, n, 4);
  avg_waiting_times[3] = 0;
  avg_response_times[3] = 0;
  for (int i = 0; i < n; i++) {
    avg_waiting_times[3] += processes[i].waiting_time;
    avg_response_times[3] += processes[i].response_time;
  }
  avg_waiting_times[3] /= n;
  avg_response_times[3] /= n;

  // Priority Non-preemptive
  copy_processes(original_processes, processes, n);
  priority_scheduling(processes, n);
  avg_waiting_times[4] = 0;
  avg_response_times[4] = 0;
  for (int i = 0; i < n; i++) {
    avg_waiting_times[4] += processes[i].waiting_time;
    avg_response_times[4] += processes[i].response_time;
  }
  avg_waiting_times[4] /= n;
  avg_response_times[4] /= n;

  // Priority Preemptive
  copy_processes(original_processes, processes, n);
  preemptive_priority_scheduling(processes, n);
  avg_waiting_times[5] = 0;
  avg_response_times[5] = 0;
  for (int i = 0; i < n; i++) {
    avg_waiting_times[5] += processes[i].waiting_time;
    avg_response_times[5] += processes[i].response_time;
  }
  avg_waiting_times[5] /= n;
  avg_response_times[5] /= n;

  // Print all average waiting times
  printf("Algorithm\t\t\tAvg Waiting Time\tAvg Response Time\n");
  printf("---------------------------------------------------------------\n");
  for (int i = 0; i < 6; i++) {
    printf("%-25s\t%.2f\t\t%.2f\n", algo_names[i], avg_waiting_times[i], avg_response_times[i]);
  }

  // Find the best algorithm based on waiting time
  float min_avg = avg_waiting_times[0];
  int best_index = 0;

  for (int i = 1; i < 6; i++) {
    if (avg_waiting_times[i] < min_avg) {
      min_avg = avg_waiting_times[i];
      best_index = i;
    }
  }

  printf("\nBest algorithm based on average waiting time: %s (%.2f)\n", algo_names[best_index], min_avg);

  // Find the best algorithm based on response time
  min_avg = avg_response_times[0];
  best_index = 0;

  for (int i = 1; i < 6; i++) {
    if (avg_response_times[i] < min_avg) {
      min_avg = avg_response_times[i];
      best_index = i;
    }
  }

  printf("Best algorithm based on average response time: %s (%.2f)\n", algo_names[best_index], min_avg);

  printf("-------------------------------------------------------\n");

  return 0;
}