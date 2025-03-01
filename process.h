#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a process
typedef struct {
  int id; // Process ID
  int arrival_time; // Arrival time
  int burst_time; // Burst time (execution time required)
  int priority; // Priority (lower number = higher priority)
  int waiting_time; // Waiting time
  int turnaround_time; // Turnaround time
  int remaining_time; // Remaining time (for RR algorithm)
  int completion_time; // Completion time
  int response_time; // Response time (time from arrival to first CPU execution)
} Process;

// Common function prototypes
void print_gantt_chart(int process_order[], int start_times[], int completion_times[], int n);

void print_process_table(Process processes[], int n);

void print_average_times(Process processes[], int n);

void sort_by_arrival_time(Process processes[], int n);

void copy_processes(Process source[], Process destination[], int n);

#endif // PROCESS_H