#include "process.h"

// Preemptive Priority Scheduling Algorithm
void preemptive_priority_scheduling(Process processes[], int n) {
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
    int prev_process = -1;

    // Array to track if a process has started execution for response time
    bool has_started[10] = {false};

    while (completed != n) {
        int highest_priority_index = -1;
        int highest_priority = 9999; // Lower number = higher priority

        // Find process with highest priority among arrived processes
        for (int i = 0; i < n; i++) {
            if (temp_processes[i].arrival_time <= current_time && temp_processes[i].remaining_time > 0) {
                if (temp_processes[i].priority < highest_priority) {
                    highest_priority = temp_processes[i].priority;
                    highest_priority_index = i;
                }
            }
        }

        if (highest_priority_index == -1) {
            // No process is available, CPU is idle
            if (prev_process != 0) { // Only add idle state if previous state wasn't idle
                process_order[chart_index] = 0; // 0 indicates CPU idle
                start_times[chart_index] = current_time;
                prev_process = 0;

                // Find next arriving process
                int next_arrival_time = 9999;
                for (int i = 0; i < n; i++) {
                    if (temp_processes[i].remaining_time > 0 && temp_processes[i].arrival_time > current_time) {
                        if (temp_processes[i].arrival_time < next_arrival_time) {
                            next_arrival_time = temp_processes[i].arrival_time;
                        }
                    }
                }

                current_time = next_arrival_time;
                completion_times[chart_index] = current_time;
                chart_index++;
            }
        } else {
            // Check if this is the first time this process is getting CPU
            if (!has_started[highest_priority_index]) {
                processes[highest_priority_index].response_time = current_time - processes[highest_priority_index].arrival_time;
                has_started[highest_priority_index] = true;
            }

            // If the current process is different from the previous one, add to chart
            if (prev_process != temp_processes[highest_priority_index].id) {
                if (prev_process != -1) {
                    completion_times[chart_index - 1] = current_time;
                }
                process_order[chart_index] = temp_processes[highest_priority_index].id;
                start_times[chart_index] = current_time;
                prev_process = temp_processes[highest_priority_index].id;
                chart_index++;
            }

            // Execute the process for 1 time unit
            current_time++;
            temp_processes[highest_priority_index].remaining_time--;

            // Check if process is completed
            if (temp_processes[highest_priority_index].remaining_time == 0) {
                completion_times[chart_index - 1] = current_time;

                // Update process metrics
                processes[highest_priority_index].completion_time = current_time;
                processes[highest_priority_index].turnaround_time =
                    processes[highest_priority_index].completion_time - processes[highest_priority_index].arrival_time;
                processes[highest_priority_index].waiting_time =
                    processes[highest_priority_index].turnaround_time - processes[highest_priority_index].burst_time;

                completed++;
            }
        }
    }

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    print_gantt_chart(process_order, start_times, completion_times, chart_index);
}