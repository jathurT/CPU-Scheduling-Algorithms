# CPU Scheduling Algorithms Simulation

This project simulates the behavior of various CPU scheduling algorithms to evaluate their performance. It includes implementations of several classical scheduling algorithms such as:

- First Come First Serve (FCFS)
- Shortest Job First (SJF) - Non-preemptive and Preemptive (SRTF)
- Priority Scheduling - Non-preemptive and Preemptive
- Round Robin (RR)

## Overview

This simulation is designed to model and compare the performance of different CPU scheduling algorithms using a set of processes. The process data includes:

- **Arrival Time**: The time at which the process arrives.
- **Burst Time**: The amount of time required by the process for execution.
- **Priority**: The priority of the process (lower numbers indicate higher priority).
- **Waiting Time**: Time a process spends waiting in the ready queue.
- **Turnaround Time**: Time taken from arrival to completion.
- **Completion Time**: Time when the process finishes execution.
- **Response Time**: Time from arrival to the first execution.

## Files

The following files are part of the simulation:

- **process.h**: Header file defining the `Process` structure and function prototypes for process handling.
- **process.c**: Implements functions related to process handling, including sorting, copying, and printing process details.
- **scheduler.h**: Header file defining function prototypes for all scheduling algorithms.
- **fcfs.c**: Implementation of the First Come First Serve (FCFS) Scheduling algorithm.
- **sjf_non_preemptive.c**: Implementation of the Shortest Job First (SJF) Scheduling algorithm (Non-preemptive).
- **sjf_preemptive.c**: Implementation of the Shortest Remaining Time First (SRTF) Scheduling algorithm (Preemptive version of SJF).
- **priority_non_preemptive.c**: Implementation of the Priority Scheduling algorithm (Non-preemptive).
- **priority_preemptive.c**: Implementation of the Preemptive Priority Scheduling algorithm.
- **roundrobin.c**: Implementation of the Round Robin (RR) Scheduling algorithm.
- **main.c**: The main program that initializes processes, runs scheduling algorithms, and prints results.

## Compilation

To compile the program, use the following command:

```bash
gcc main.c fcfs.c sjf_non_preemptive.c sjf_preemptive.c priority_non_preemptive.c priority_preemptive.c roundrobin.c process.c -o scheduler_simulation
