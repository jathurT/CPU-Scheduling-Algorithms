#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

// Function prototypes for scheduling algorithms
void fcfs_scheduling(Process processes[], int n);
void sjf_scheduling(Process processes[], int n);
void round_robin_scheduling(Process processes[], int n, int time_quantum);
void priority_scheduling(Process processes[], int n);
void preemptive_priority_scheduling(Process processes[], int n);
void srtf_scheduling(Process processes[], int n);

#endif // SCHEDULER_H