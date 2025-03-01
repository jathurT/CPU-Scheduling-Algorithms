#include "process.h"

// Priority Scheduling Algorithm (Non-preemptive)
void priority_scheduling(Process processes[], int n) {
    sort_by_arrival_time(processes, n);

    int current_time = 0;
    int completed = 0;
    int process_order[100];
    int start_times[100];
    int completion_times[100];
    int chart_index = 0;
    bool is_completed[10] = {false};

    while (completed != n) {
        int highest_priority_index = -1;
        int highest_priority = 9999; // Lower number = higher priority

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !is_completed[i]) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    highest_priority_index = i;
                }
            }
        }

        if (highest_priority_index == -1) {
            // No process is available, CPU is idle
            process_order[chart_index] = 0; // 0 indicates CPU idle
            start_times[chart_index] = current_time;

            // Find next arriving process
            int next_arrival_time = 9999;
            for (int i = 0; i < n; i++) {
                if (!is_completed[i] && processes[i].arrival_time > current_time) {
                    if (processes[i].arrival_time < next_arrival_time) {
                        next_arrival_time = processes[i].arrival_time;
                    }
                }
            }

            current_time = next_arrival_time;
            completion_times[chart_index] = current_time;
            chart_index++;
        } else {
            // Calculate response time if this is the first time process is executed
            if (processes[highest_priority_index].response_time == -1) {
                processes[highest_priority_index].response_time = current_time - processes[highest_priority_index].arrival_time;
            }

            // Execute the highest priority process
            process_order[chart_index] = processes[highest_priority_index].id;
            start_times[chart_index] = current_time;
            current_time += processes[highest_priority_index].burst_time;
            completion_times[chart_index] = current_time;
            chart_index++;

            // Update process metrics
            processes[highest_priority_index].completion_time = current_time;
            processes[highest_priority_index].turnaround_time = processes[highest_priority_index].completion_time - processes[highest_priority_index].arrival_time;
            processes[highest_priority_index].waiting_time = processes[highest_priority_index].turnaround_time - processes[highest_priority_index].burst_time;
            is_completed[highest_priority_index] = true;
            completed++;
        }
    }

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    print_gantt_chart(process_order, start_times, completion_times, chart_index);
}