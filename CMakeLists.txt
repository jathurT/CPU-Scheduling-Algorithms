cmake_minimum_required(VERSION 3.30)
project(Ass1 C)

set(CMAKE_C_STANDARD 11)

add_executable(cpu_scheduler
        main.c
        process.c
        fcfs.c
        sjf_non_preemptive.c
        sjf_preemptive.c
        roundrobin.c
        priority_non_preemptive.c
        priority_preemptive.c)