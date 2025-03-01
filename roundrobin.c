#include "process.h"

// Round Robin (RR) Scheduling Algorithm
void round_robin_scheduling(Process processes[], int n, int time_quantum) {
    sort_by_arrival_time(processes, n);

    // Create a copy of processes for manipulation
    Process temp_processes[10];
    copy_processes(processes, temp_processes, n);

    int current_time = 0;
    int completed = 0;
    int process_order[100];
    int start_times[100];
    int completion_times[100];
    int chart_index = 0;

    // Array to track if process has started execution (for response time)
    bool has_started[10] = {false};

    // Ready queue
    int queue[100];
    int front = 0, rear = 0;

    // Add first process to queue if it has arrived
    if (temp_processes[0].arrival_time <= current_time) {
        queue[rear++] = 0;  // Add process index to queue
    }

    while (completed != n) {
        if (front == rear) {
            // Queue is empty, CPU is idle
            process_order[chart_index] = 0; // 0 indicates CPU idle
            start_times[chart_index] = current_time;

            // Find next arriving process
            int next_arrival_time = 9999;
            int next_process_index = -1;
            for (int i = 0; i < n; i++) {
                if (temp_processes[i].remaining_time > 0 && temp_processes[i].arrival_time > current_time) {
                    if (temp_processes[i].arrival_time < next_arrival_time) {
                        next_arrival_time = temp_processes[i].arrival_time;
                        next_process_index = i;
                    }
                }
            }

            current_time = next_arrival_time;
            completion_times[chart_index] = current_time;
            chart_index++;

            // Add the process to queue
            queue[rear++] = next_process_index;
        } else {
            // Get process from front of queue
            int current_process = queue[front++];

            // If this is the first time this process gets CPU, calculate response time
            if (!has_started[current_process]) {
                processes[current_process].response_time = current_time - processes[current_process].arrival_time;
                has_started[current_process] = true;
            }

            // Execute process for time quantum or remaining time, whichever is smaller
            int execution_time = (temp_processes[current_process].remaining_time < time_quantum) ?
                                temp_processes[current_process].remaining_time : time_quantum;

            process_order[chart_index] = temp_processes[current_process].id;
            start_times[chart_index] = current_time;
            current_time += execution_time;
            completion_times[chart_index] = current_time;
            chart_index++;

            // Update remaining time
            temp_processes[current_process].remaining_time -= execution_time;

            // Check for new arrivals during this time quantum
            for (int i = 0; i < n; i++) {
                if (temp_processes[i].remaining_time > 0 &&
                    temp_processes[i].arrival_time > start_times[chart_index-1] &&
                    temp_processes[i].arrival_time <= current_time) {
                    // Add to queue if not already in queue
                    bool in_queue = false;
                    for (int j = front; j < rear; j++) {
                        if (queue[j] == i) {
                            in_queue = true;
                            break;
                        }
                    }
                    if (!in_queue) {
                        queue[rear++] = i;
                    }
                }
            }

            // If process is not completed, add it back to queue
            if (temp_processes[current_process].remaining_time > 0) {
                queue[rear++] = current_process;
            } else {
                // Process is completed
                temp_processes[current_process].completion_time = current_time;
                // Update the original process array
                processes[current_process].completion_time = temp_processes[current_process].completion_time;
                processes[current_process].turnaround_time = processes[current_process].completion_time - processes[current_process].arrival_time;
                processes[current_process].waiting_time = processes[current_process].turnaround_time - processes[current_process].burst_time;
                completed++;
            }
        }
    }

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    print_gantt_chart(process_order, start_times, completion_times, chart_index);
}