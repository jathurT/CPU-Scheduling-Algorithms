#include "process.h"

// Shortest Job First (SJF) Scheduling Algorithm (Non-preemptive)
void sjf_scheduling(Process processes[], int n) {
    sort_by_arrival_time(processes, n);

    int current_time = 0;
    int completed = 0;
    int process_order[100];
    int start_times[100];
    int completion_times[100];
    int chart_index = 0;
    bool is_completed[10] = {false};

    while (completed != n) {
        int shortest_job_index = -1;
        int shortest_burst = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !is_completed[i]) {
                if (processes[i].burst_time < shortest_burst) {
                    shortest_burst = processes[i].burst_time;
                    shortest_job_index = i;
                }
            }
        }

        if (shortest_job_index == -1) {
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
            if (processes[shortest_job_index].response_time == -1) {
                processes[shortest_job_index].response_time = current_time - processes[shortest_job_index].arrival_time;
            }

            // Execute the shortest job
            process_order[chart_index] = processes[shortest_job_index].id;
            start_times[chart_index] = current_time;
            current_time += processes[shortest_job_index].burst_time;
            completion_times[chart_index] = current_time;
            chart_index++;

            // Update process metrics
            processes[shortest_job_index].completion_time = current_time;
            processes[shortest_job_index].turnaround_time = processes[shortest_job_index].completion_time - processes[shortest_job_index].arrival_time;
            processes[shortest_job_index].waiting_time = processes[shortest_job_index].turnaround_time - processes[shortest_job_index].burst_time;
            is_completed[shortest_job_index] = true;
            completed++;
        }
    }

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    print_gantt_chart(process_order, start_times, completion_times, chart_index);
}